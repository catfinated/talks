# Live demo — pre-built variations

Seven standalone programs for the demo slide.

## Build

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target demos -j
./run_all.sh build
```

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

## Notes

- Older stdexec examples spell `continues_on` as `transfer`. It survives as a
  deprecated alias, so a copy-pasted snippet using it will still compile.
