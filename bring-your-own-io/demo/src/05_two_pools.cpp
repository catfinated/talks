// 05 — two pools, hand the value across with continues_on.
#include <iostream>
#include <thread>

#include <stdexec/execution.hpp>
#include "exec/static_thread_pool.hpp"

using namespace stdexec;
using stdexec::sync_wait;

int main()
{
    exec::static_thread_pool pool_a{2};
    exec::static_thread_pool pool_b{2};

    sender auto work =
        schedule(pool_a.get_scheduler())
        | then([] {
              std::cout << "produced on " << std::this_thread::get_id() << "\n";
              return 13;
          })
        | continues_on(pool_b.get_scheduler())     // <-- the hand-off
        | then([](int v) {
              std::cout << "consumed on " << std::this_thread::get_id() << "\n";
              return v + 42;
          });

    auto [r] = sync_wait(std::move(work)).value();
    std::cout << "Result: " << r << "\n";          // 55
}
