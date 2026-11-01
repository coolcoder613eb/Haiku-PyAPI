#!/usr/bin/env python3
#
# run_all.py — run every test_*.py in this dir, aggregate the JSON
# lines, print a pass/fail/error table, exit nonzero if anything is red.
#
import glob
import json
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
SUITES = sorted(os.path.basename(p)[:-3]
                for p in glob.glob(HERE + "/test_*.py"))

rows = []
for i, suite in enumerate(SUITES, 1):
    # progress on stderr (not the stdout report): the run takes a while,
    # especially test_constants (it builds one emitter per module).
    print("[%d/%d] %s" % (i, len(SUITES), suite), file=sys.stderr, flush=True)
    # One fresh SUBPROCESS per suite, not import-and-call in this process —
    # that isolation is the point (see common.py "Runtime awareness"): each
    # suite imports binding modules that draw on the process-global TSS key
    # pool, and a failed import poisons the process, so a subprocess gives
    # every suite a clean pool and contains its crash/poisoning; cwd="/" keeps
    # a local Be/ from shadowing the farm; and only a subprocess can be reaped
    # on timeout (an in-process timeout can't kill a running fn). The JSON lines
    # on its stdout are how that isolated child reports back to us.
    try:
        p = subprocess.run([sys.executable, os.path.join(HERE, suite + ".py")],
                           cwd="/", capture_output=True, text=True, timeout=900)
    except subprocess.TimeoutExpired as te:
        # A hanging suite must not sink the whole aggregate: record it and
        # move on (other agents own their suites; we only need totals).
        rows.append({"test": suite + ":CRASH",
                     "status": "ERROR",
                     "detail": "timed out after 900s"})
        continue
    n_json = 0
    for line in (p.stdout or "").splitlines():
        if line.startswith("JSON "):
            d = json.loads(line[5:])
            d.pop("suite", None)
            rows.append(d)
            n_json += 1
    if n_json == 0:
        # a real crash: the suite produced no rows (died at import/setup), so
        # there's nothing else to report for it — surface the last line. (A
        # suite that ran but had FAIL/ERROR rows is not a crash.)
        tail = (p.stderr or p.stdout or "").strip().splitlines()
        rows.append({"test": suite + ":CRASH",
                     "status": "ERROR",
                     "detail": (tail[-1][:200] if tail else
                                "no JSON output (rc=%d)" % p.returncode)})

by = {}
for r in rows:
    by.setdefault(r["status"], []).append(r)
for status in ("PASS", "FAIL", "ERROR", "ABSENT", "SKIP"):
    for r in by.get(status, []):
        print("%-6s %-52s %s" % (status, r["test"][:52], r.get("detail", "")))
print("==== %d pass, %d fail, %d error, %d absent, %d skip ====" %
      (len(by.get("PASS", [])), len(by.get("FAIL", [])),
       len(by.get("ERROR", [])), len(by.get("ABSENT", [])),
       len(by.get("SKIP", []))))
sys.exit(1 if (by.get("FAIL") or by.get("ERROR")) else 0)
