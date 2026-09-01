// 02 — chain another then().
#include <iostream>

#include <stdexec/execution.hpp>
#include "exec/static_thread_pool.hpp"

using namespace stdexec;
using stdexec::sync_wait;

int main()
{
    exec::static_thread_pool ctx{8};
    scheduler auto sch = ctx.get_scheduler();

    sender auto work = schedule(sch)
        | then([] {
              std::cout << "Hello world! Have an int.\n";
              return 13;
          })
        | then([](int v) { return v + 42; })
        | then([](int v) { return v * 2; });

    // nothing has run yet at this point
    auto [i] = sync_wait(std::move(work)).value();
    std::cout << "Result: " << i << "\n"; 
}
