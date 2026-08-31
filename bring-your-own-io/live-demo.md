# Live demo — script and variations

Compiler Explorer · library: **stdexec** · based on `stdexec/examples/hello_world.cpp`

**Load only the first half** of `hello_world.cpp` into the Godbolt buffer — up to and
including the first `sync_wait`. The rest of the upstream file uses `get_scheduler()`,
the `run_loop` scheduler, and a `when_all` over environment queries, all of which lean on
the receiver environment. That isn't introduced until the operation-state slide.

**Hard timebox: 8 minutes.** You will not get through all five. If there's time for only
one, do **#5** — it rehearses the scheduler hand-off the rest of the talk depends on.

All spellings verified against a recent `NVIDIA/stdexec` checkout.

---

## Base — what's in the buffer

```cpp
#include <iostream>
#include <stdexec/execution.hpp>
#include "exec/static_thread_pool.hpp"

using namespace stdexec;
using stdexec::sync_wait;

auto main() -> int
{
  exec::static_thread_pool ctx{8};
  scheduler auto sch = ctx.get_scheduler();

  sender auto begin = schedule(sch);
  sender auto hi_again = then(begin, [] {
      std::cout << "Hello world! Have an int.\n";
      return 13;
  });
  sender auto add_42 = then(hi_again, [](int arg) { return arg + 42; });

  auto [i] = sync_wait(std::move(add_42)).value();
  std::cout << "Result: " << i << std::endl;
}
```

Talking point: the scheduler is constructed once and passed in. Swap
`static_thread_pool` for any other scheduler and the pipeline logic is unchanged.

---

## 1 — Change the thread count

The count alone shows nothing observable, so print the thread id.

```cpp
#include <thread>
// ...
exec::static_thread_pool ctx{1};          // try 1, then 8

sender auto work = schedule(sch)
  | then([] {
        std::cout << "running on " << std::this_thread::get_id() << "\n";
        return 13;
    });
```

One thread → same id every run. Eight → varies between runs.

Worth saying: a single-threaded pool is a legitimate configuration, not a degenerate one.

---

## 2 — Chain a second `then`

```cpp
sender auto add_42  = then(hi_again, [](int arg) { return arg + 42; });
sender auto doubled = then(add_42,  [](int arg) { return arg * 2; });

auto [i] = sync_wait(std::move(doubled)).value();   // 110
```

Or in pipe form, which reads better on a projector:

```cpp
sender auto work = schedule(sch)
  | then([] { return 13; })
  | then([](int v) { return v + 42; })
  | then([](int v) { return v * 2; });
```

---

## 3 — Introduce an error, recover from it

```cpp
#include <system_error>
// ...
sender auto failing =
    just_error(std::make_error_code(std::errc::io_error))
  | upon_error([](std::error_code ec) {
        std::cout << "recovered from: " << ec.message() << "\n";
        return -1;                     // error channel → value channel
    });

auto [j] = sync_wait(std::move(failing)).value();
std::cout << "Result: " << j << "\n";   // -1
```

The point is that `.value()` succeeds. `upon_error` moved the completion back onto the
value channel, so `sync_wait` doesn't throw.

`just_error` accepts any error type — `std::exception_ptr` works too if you'd rather show
the throwing path.

---

## 4 — `when_all` over two parallel branches

```cpp
sender auto a = schedule(sch) | then([] { return 13; });
sender auto b = schedule(sch) | then([] { return 29; });

auto [x, y] = sync_wait(when_all(std::move(a), std::move(b))).value();
std::cout << x << " + " << y << " = " << x + y << "\n";
```

Two branches, one value each, so the join completes `set_value(int, int)` and the
structured binding unpacks both. That's the concatenation rule from the fan-out slide,
running live.

---

## 5 — Two pools, hand the value across with `continues_on`

**Do this one if there's only time for one.**

```cpp
#include <thread>
// ...
exec::static_thread_pool pool_a{2};
exec::static_thread_pool pool_b{2};

sender auto work =
    schedule(pool_a.get_scheduler())
  | then([] {
        std::cout << "produced on " << std::this_thread::get_id() << "\n";
        return 13;
    })
  | continues_on(pool_b.get_scheduler())
  | then([](int v) {
        std::cout << "consumed on " << std::this_thread::get_id() << "\n";
        return v + 42;
    });

auto [r] = sync_wait(std::move(work)).value();
std::cout << "Result: " << r << "\n";   // 55
```

Two different thread ids in the output is the entire demonstration.

**The line to say over it:** replace `pool_b` with an io_uring scheduler and nothing above
or below that line changes.

---

## Notes

- Older stdexec examples spell #5 as `transfer`. It survives as a deprecated alias, so a
  copy-pasted snippet using it will still compile.
- If someone has seen the full upstream `hello_world.cpp` and asks about the tail: it
  queries the environment that `sync_wait` provides, and environments come up later in the
  talk.
- **Fallback ladder:** run the pre-loaded example → if compiles are slow, narrate the
  expected output → if Godbolt is unresponsive, skip ahead; the concepts are already
  established. Don't live-edit beyond these five.
