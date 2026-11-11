# bindtests/ — Haiku-PyAPI functional-equivalence test suite

Test-driven standard for the bindings: **the C API, as compiled in this
environment, is the spec** — every bound constant and every tested method
must behave like the C it wraps. Two kinds of rows:

- **the constants sweep** (`test_constants.py`) — every `m.attr` constant,
  checked automatically, one row per module;
- **behavior rows** (per-kit `test_*.py`) — hand-written, pinning return
  conventions and beta6-specific behavior.

Red rows mark where a binding falls short of that standard. More details can
be found in [IMPLEMENTATION.md](IMPLEMENTATION.md).

## Requirements

The suite runs where the bindings were built. What you need, in place:

- the built bindings (the `.so` module files) — `/boot/home/prefixrun/Be`
- the repo checkout — two levels up from the suite (`<repo>/tests/bindtests`)
- Python 3.14 (interpreter + its develop headers)
- a C++ toolchain (`g++`) + the system develop headers — `/system/develop/headers`

The Python, toolchain, and develop headers are part of a standard Haiku R1
beta6 install — there's no separate install step. The paths above are
defaults; override them via a local `.env` file
([Configuration](IMPLEMENTATION.md#configuration)).

## Quick start

```sh
cd <repo>/tests/bindtests
python3 run_all.py          # every test_*.py
```

`run_all.py` prints a `[i/N] <suite>` progress marker (on stderr) as each
suite starts, then a one-line-per-row results table, and exits nonzero on any
FAIL or ERROR. A single suite runs the same way: `python3 test_storage.py`.

## Baseline report

`baseline-<base>.txt` (`baseline-99940f7.txt` here) is a sample output from a
full `run_all.py` against the base bindings `99940f7` on beta6
`hrev59866+79`. Running the suite the same way should give matching output.

## Paired regression tests

This suite started as a way to *find* binding defects, but its lasting value
is *keeping them found*: a row that pins a fixed behavior is what stops the
bug from silently returning. So when you fix a binding, we'd strongly
encourage you to **ship the fix with the row that pins it** — and over time
we hope those pinned rows make the discovery half redundant, leaving a
regression net you can trust.

## Implementation details

[IMPLEMENTATION.md](IMPLEMENTATION.md) goes deeper on: the beta6
[version note](IMPLEMENTATION.md#version-note), the
[requirements](IMPLEMENTATION.md#requirements) and why each is needed, how the
[constants sweep](IMPLEMENTATION.md#the-constants-sweep) works (the compiler as
oracle), the [file-by-file layout](IMPLEMENTATION.md#files), the
[TSS-key import wall](IMPLEMENTATION.md#runtime-awareness-the-tss-key-import-wall)
the subprocess design works around,
[configuration](IMPLEMENTATION.md#configuration), the [return
conventions](IMPLEMENTATION.md#return-conventions-the-behavior-rows-pin-so-fixes-dont-regress)
the behavior rows pin, how to read the
[baseline report](IMPLEMENTATION.md#baseline-report), and the
[regression-row shape + worked example](IMPLEMENTATION.md#paired-regression-tests).
