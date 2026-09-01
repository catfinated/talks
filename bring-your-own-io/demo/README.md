# Live demo — pre-built variations

Seven standalone programs for the demo slide.

## Build

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target demos -j
./run_all.sh build
```

**Pin the stdexec commit before the talk.** `CMakeLists.txt` currently uses
`GIT_TAG main`. Replace it with a specific SHA so the thing you rehearse against is
the thing you present, then rebuild and re-rehearse — in that order.

## The variations

| # | File | Shows | Expected output |
|---|---|---|---|
| 0 | `00_base.cpp` | The base pipeline — scheduler, `schedule`, `then`, `sync_wait`, structured binding | `Hello world! Have an int.` / `Result: 55` |
| 1 | `01_thread_count.cpp` | Pool size is a configuration, not a property of the pipeline | `running on <tid>` / `Result: 55` |
| 2 | `02_second_then.cpp` | Chaining in pipe form; each step returns a new sender | `Hello world! Have an int.` / `Result: 110` |
| 3 | `03_error_recovery.cpp` | `just_error` → `upon_error` moves the completion back to the value channel | `recovered from: Input/output error` / `Result: -1` |
| 4 | `04_when_all.cpp` | Fan-out; two branches concatenate to `set_value(int, int)` | `13 + 29 = 42` |
| 5 | `05_two_pools.cpp` | **The important one.** `continues_on` hands a value between schedulers | `produced on <tid-A>` / `consumed on <tid-B>` / `Result: 55` |
| 6 | `06_async_scope.cpp` | `spawn` into a scope, carry on, then join with `on_empty()` | `carrying on, 0 done so far` / five `task N finished` / `all joined, 5 done` |

## Running them

**Hard timebox: 8 minutes.** Seven will not fit and are not meant to — the point of having
them all built is that whichever question comes up, you can run the answer. If there's
time for only one after the base, run **#5** — it rehearses the scheduler hand-off the rest of
the talk depends on.

Points worth making, in order of value:

- **#5:** two different thread ids is the whole demonstration. Say: *replace `pool_b`
  with an io_uring scheduler and nothing above or below that line changes.*
- **#3:** the point is that `.value()` **succeeds**. `upon_error` moved the completion
  onto the value channel, so `sync_wait` doesn't throw. `03` has a commented-out line
  showing the unrecovered version if you want to demonstrate the throw first.
- **#1:** a single-threaded pool is a legitimate configuration, not a degenerate one.
- **#4:** lands on 42. Use it.
- **#6:** the best output of the seven. `carrying on, 0 done` prints *before* any task
  finishes, then the join reports 5 — spawn-and-continue-but-still-provable. Task 0
  lands last because of the staggered sleeps, which shows they genuinely overlapped.
  The `++done` with no return value quietly demonstrates that `spawn` takes senders
  completing with no values.

## Notes

- Older stdexec examples spell `continues_on` as `transfer`. It survives as a
  deprecated alias, so a copy-pasted snippet using it will still compile.
