// 01 — change the thread count. 
#include <iostream>
#include <thread>

#include <stdexec/execution.hpp>
#include "exec/static_thread_pool.hpp"

using namespace stdexec;
using stdexec::sync_wait;

int main()
{
    exec::static_thread_pool ctx{1};     // <-- try 1, then 8
    scheduler auto sch = ctx.get_scheduler();

    sender auto work = schedule(sch)
        | then([] {
              std::cout << "running on " << std::this_thread::get_id() << "\n";
              return 13;
          })
        | then([](int v) { return v + 42; });

    auto [i] = sync_wait(std::move(work)).value();
    std::cout << "Result: " << i << "\n";
}
