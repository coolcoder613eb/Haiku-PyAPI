# bindtests/ — implementation

The [README](README.md) covers what this suite is and how to run it; this is
how it works.

## Version note

Written and validated against Haiku R1 beta6. The constants sweep is
**environment-adaptive** — its oracle is the C++ compiler building against
*this* environment's headers, so it pins no values and needs no regeneration
(it works on any Haiku). The behavior rows do pin beta6-specific behavior —
4cc `type_code`s (`B_INT32_TYPE='LONG'`), POSIX `O_*` open modes, removed APIs
(pinned ABSENT so they are not rebound as ghosts), `ssize_t` attr-I/O returns,
the kernel query/index rules — and would need rework on another Haiku version.

The bindings this PR adds the suite to predate beta6 (upstream is beta5-era).
Run on **beta6**, they fail wherever the beta5→beta6 headers/API diverged (and
on other binding gaps), so a **red baseline against them is expected** — the
[baseline report](README.md#baseline-report) is that run.

The framework (`common.py` / `child_constants.py` / `run_all.py` /
`selectmods.py`) is version-agnostic.

## Requirements

The suite runs **where the bindings were built**. What you need in place:

- **The built `.so` farm** (`BE_PKG_DIR`). `jam -s python_version=3.14` at the
  repo root builds the bindings into `build/python3.14_release/`; the standard
  layout symlinks that at `/boot/home/prefixrun/Be`. **jam builds the bindings,
  not the suite** — the suite's own artifacts (`scratch/`, and the sweep's
  generated emitters under `scratch/emitters/`) are created at run time, no
  manual step.
- **The repo checkout** (`PYAPI_REPO`, default the suite's `../..`) — the
  constants sweep reads the bindings source + root Jamfile from it.
- **A C++ toolchain + the system develop headers** (`BINDTESTS_CXX` = `g++`,
  `BINDTESTS_SYSTEM_HDRS` = the installed `/system/develop/headers`) — the
  sweep compiles a per-module emitter against them.

The **behavior rows** need only the `.so` farm; the **constants sweep**
additionally needs the checkout + toolchain + headers. There is no separate
generation host and nothing to regenerate — a new `m.attr` constant is swept on
the next run. Defaults assume the standard layout; otherwise set the env vars
(or a local `.env`) — full options under [Configuration](#configuration).

The full sweep is **Haiku-bound** — the Python side imports the built `.so`s
and the emitters link the Haiku libs.

**If it isn't set up:** a module's `.so` missing from the farm (not built) →
its rows report `ABSENT` and the rest of the suite still runs (one unbuilt
module doesn't take it down); but the constants sweep's own deps (the checkout
/ headers / toolchain) missing → it dies during setup before any `constants:*`
row (a `:CRASH` row, e.g. `FileNotFoundError` listing the headers dir).

## The constants sweep

The bindings expose Haiku's C constants as Python module attributes
(`m.attr("B_CREATE_FILE") = B_CREATE_FILE;`). The sweep checks that each such
attribute, at runtime, is the **same value, of the same type**, as the C
expression the source binds it from.

**Why the compiler is the oracle.** C++ and Python each evaluate the constant
in their own environment, and the results are diffed: the binding's own
expression is compiled against this environment's headers and compared to what
the built module actually exposes. The compiler — not a Python-side header
parser — is the source of truth, and there is nothing to regenerate by hand.

**How it works**, per binding module:

1. **Extract** — preprocess the binding's `.cpp` with `g++ -E -P` so
   `#if` / macros / comments resolve *exactly as at the binding's build*, and
   pull out every `m.attr("NAME") = <expr>;`. Only constant-shaped exprs (no
   function call) are swept — `py::cast(…)` or a ctor binds an object, not a
   constant. Scanning is scoped to the Jamfile's `SEARCH_SOURCE` dirs, so
   stale backups (e.g. `bindings/support/old/`) are not swept.
2. **C++ side** — generate a small emitter program that `#include`s the same
   headers and links the same libs as the module, and prints
   `(NAME, typeclass, value)` for each constant. Build + run it → the values
   the *headers* give.
3. **Python side** (`child_constants.py`) — import the built module and read
   the same names → the values the *binding* exposes.
4. **Diff** — one row per module, `constants:<Module>`: PASS if every name
   matches in **both typeclass and value**.

**typeclass is compared, not just the value**: a C `int` (**T**) vs a Python
`str` (**S**) is a mismatch — this is how the sweep catches the *string-form
4cc* defect (source binds `"CLCH"` where C has the `int` `'CLCH'`, so a
`what == B_CLIPBOARD_CHANGED` could never match). The classes: **T** integral
(bool; pybind enums compare via `int()`), **S** str, **F** float, **C**
composite (pointer / struct — value not comparable, e.g. `be_roster`).

**What it catches:** a `.so` that doesn't match its source (a stale or wrong
build); a type drift (int↔str, the 4cc class); a name the headers no longer
define (the emitter fails to compile → the row FAILs, not a silent skip).

**What is intentionally not checked:** whether a *hardcoded literal* in the
source matches the header — the oracle is the source's own expression, not an
independent spec. A binding that hardcoded `B_CREATE_FILE = 8` (the
classic-era value; beta6's is `O_CREAT = 0x200`) would pass the sweep as long
as the `.so` matches the source. The behavior rows remain the place for
spec-level pins.

## Files

| File | Role |
|---|---|
| `test_constants.py` | the constants sweep (above): extract → emit → diff, one `constants:<Module>` row per module. |
| `child_constants.py` | the sweep's Python side: dump each module's `(typeclass, value)` at runtime — one "chunk" child for the whole import-closure when the TSS pool fits, else fault-isolated solo→closure children per module (see Runtime awareness). |
| `test_storage.py` `test_message.py` `test_support.py` `test_interface.py` `test_appmedia.py` | per-kit behavior rows: return conventions, tuple shapes, beta6 removals pinned ABSENT, the BQuery kernel grammar + index rules, headless-safe class smokes. |
| `common.py` | loader (`.so` farm + selectmods closure), TSS pool measurement + import strategy, `check`/`fail`/`skip`/`absent`/`report` JSON-line protocol, scratch dir, env/`.env` config. |
| `run_all.py` | runs every `test_*.py` in a fresh subprocess each (cwd=/ so no local `Be` package can shadow the farm), aggregates the JSON lines, exits nonzero on any FAIL/ERROR. |
| `selectmods.py` | static analysis of the bindings: the module dependency graph + stock import order, behind `common.closure()`; `--budget` checks a set against the TSS pool. |
| `.env.example` | template for a local `.env` — copy + edit for a non-standard layout (see Configuration). |

## Runtime awareness: the TSS-key import wall

The suite is subprocess-based because of two process-level walls
(documented in `common.py`):

1. **TSS pool**: each imported pybind11 v3 module consumes ~4 CPython TSS
   (pthread) keys; the pool is process-wide (~507 usable on Haiku CPython
   3.14, ~1024 on Linux). Past the pool the next import aborts the process.
2. **Import poisoning**: a *failed* import leaves partial C++ registrations
   behind, so that process can never cleanly re-import the module — import
   faults need a fresh process.

`common.import_strategy()` **measures the pool at runtime** (create-until-
fail, release all — no platform name-checks) and picks:

- `single` — the whole union closure fits the pool with margin → one child
  process imports everything (fast; e.g. Linux, or a future Haiku build
  with the deferred lazy-TSS pybind11 patch, which this adapts to
  automatically);
- `per-module` — one fault-isolated child per module, solo→closure retry
  (current Haiku behavior).

Every suite prints `strategy: ...` on its run; a `single`-mode child that
fails at module X falls back to per-module for X and the rest.

## Configuration

The suite is self-contained and relocatable: every path is env-overridable
(defaults match the standard layout — run it from the repo checkout in the
build environment). To customize, copy `.env.example` to `.env` and/or set
real env vars; precedence is dotenv-standard — **real environment variables
always win over `.env`** (stdlib-only loader; no pip in the build env).

| Variable | Default | Meaning |
|---|---|---|
| `BE_PKG_DIR` | `/boot/home/prefixrun/Be` (else `/boot/home/Be`) | the `.so` farm the tests import (a symlink to the shared build dir) |
| `PYAPI_REPO` | the repo root — two levels up, since the suite sits in `<repo>/tests/bindtests` | checkout providing the bindings source + root Jamfile |
| `PYAPI_BINDINGS` | `/boot/home/Haiku-PyAPI/bindings` | bindings source tree (selectmods' static dep analysis) |
| `BINDTESTS_SYSTEM_HDRS` | `/system/develop/headers` | the headers the emitters compile against (a haiku checkout's `headers/` on a Linux box) |
| `BINDTESTS_CXX` | `g++` | compiler for the emitters |
| `PYAPI_STOCK_INIT` | `$PYAPI_BINDINGS/__init__.py` | the stock import-order file (selectmods) |
| `PYAPI_BUDGET` | `/boot/home/budget.py` | TSS budget checker for `selectmods.py --budget` (skipped if absent) |
| `PYAPI_SELECTMODS_DIR` | `/boot/home` | fallback dir for `selectmods.py` |
| `BINDTESTS_SCRATCH` | `<suite>/scratch` | scratch dir for test-created files (+ the emitters) |
| `BINDTESTS_ENV` | — | alternate `.env` location |

Paths appearing *inside* test assertions (e.g. `BUrl("file:///boot/home")`)
are test DATA, not plumbing — `/boot/home` is universal on Haiku.

## Return conventions the behavior rows pin (so fixes don't regress)

A C++ method with a trailing **out-pointer** (`off_t*`, `char*`, `BString*`,
`stat*`, …) — which a raw pybind binding would null-deref on `None` or silently
drop (a throwaway buffer) — is re-bound to **return a tuple instead: the
out-value(s) first, the status/byte-count last.** The storage attr-I/O API is
the detailed case:

- `ReadAttr(…) → (value, bytes_read)`, `ReadAttrString(name) → (str, status)`,
  `GetAttrInfo(name) → (info, status)` (`info = {type, size}`),
  `GetNextAttrName() → (name, status)`; the `BStatable` getters
  `GetOwner` / `GetPermissions` / `GetModificationTime` / `GetNodeRef` →
  `(value, status)`.
- `ReadAttr` yields the value **typed**: ints→int, floats→float, bool→bool,
  strings→str, raw/other→bytes.
- `WriteAttr` / `Read` return the `ssize_t` **byte count** (negative = error),
  not a status.
- **One documented exception:** `GetSize() → (status, size)` — status *first*,
  pinned by its row's comment (unlike the getters above).

Other beta6 API shapes the rows pin:

- `type_code` is a 4cc (`B_INT32_TYPE='LONG'`); open modes are POSIX `O_*`
  (`B_CREATE_FILE=0x200`).
- BQuery: `SetPredicate` (C-style grammar) works; the Push* stack is broken on
  the beta6 kernel — a *known-broken* row (the QueryStack grammar is upstream
  Haiku kit code, not something to "fix" in the bindings).
- An attribute predicate matches NOTHING without its volume index (kernel
  rule); `Index::Update` no-ops same-value rewrites → remove-then-write to
  populate.

## Baseline report

`baseline-<base>.txt` (`baseline-99940f7.txt`) is a full `run_all.py` output
pinned to a base commit + beta6 hrev — the base bindings `99940f7`, run on
beta6 `hrev59866+79`. Read as the suite's report on that base:

- `PASS` = equivalent to the C API;
- `FAIL` = built but the value/behavior is wrong;
- `ERROR` = the base lacks the standard API (calling it raises);
- `ABSENT` = the module's `.so` isn't built;
- `SKIP` = can't run here (no screen).

The red rows are the base's gaps — the beta5-era base vs the beta6 API, plus
binding gaps — **not suite failures; a red baseline is expected.**

The object-repr memory addresses are normalized to `object at 0x…` (they vary 
every run but carry no signal) — so a same-env re-run should match 
the baseline row-for-row, byte-for-byte. A mismatch therefore means a 
different base commit / beta6 hrev / arch, **or a real change in the suite 
or the bindings** — rule out the environment first, then chase a same-env 
mismatch as a signal, not flakiness.

## Paired regression tests

Recommended shape (that is being used):

1. **Name the row** `<kit>:<Class>.<method>` so it maps to the fix and is easy
   to find. (Constants need no row — the sweep covers every `m.attr`
   automatically.)
2. **Pin the exact standard shape** — the tuple layout, the return convention
   (`ssize_t` bytes vs `status`, `(value, status)` order), int-vs-str for
   4ccs. The row should encode *the* correct behavior, not merely "doesn't
   crash".
3. **Have it fail before the fix** — exercise the actual bug (the no-arg form
   of an out-param method, the single-arg constructor, the constant's type).
   A row that already passes pins nothing.
4. **Keep it headless-safe** — a few assertions; guard live-resource needs
   (BApplication, screen, audio) with `try: ... except BaseException:
   common.skip(...)` so the row skips, rather than fails, without a GUI.
5. **Pin a new defect class even if you don't fix it yet** — a named row that
   records the behavior keeps it visible. E.g. `query:pushstack-known-broken`
   pins an upstream QueryStack grammar mismatch so a future change is noticed;
   `storage:BPath.single-arg-setto` pins the `py::arg("leaf")=NULL`-default
   defect class.

New rows go in the kit file (`test_storage.py`, `test_message.py`,
`test_support.py`, `test_interface.py`, `test_appmedia.py`); `run_all.py`
picks up any `test_*.py` automatically.

Worked example (one row, end to end):

```python
def t_entry_getsize():
    # STANDARD: GetSize() with no args -> (status, size). The pre-fix raw
    # binding was BStatable::GetSize(off_t*) — None null-deref'd, int TypeErrored.
    e = BEntry(P)
    r = e.GetSize()
    assert isinstance(r, tuple) and r[0] == B_OK and r[1] > 0, repr(r)
common.check("storage:entry-getsizeshape", t_entry_getsize)
```
