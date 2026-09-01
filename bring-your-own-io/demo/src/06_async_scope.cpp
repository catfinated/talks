// 06 — spawn work into a scope, then prove it all finished.
#include <atomic>
#include <iostream>
#include <thread>

#include <stdexec/execution.hpp>
#include "exec/async_scope.hpp"
#include "exec/static_thread_pool.hpp"

using namespace stdexec;
using stdexec::sync_wait;

int main()
{
    exec::static_thread_pool ctx{4};
    scheduler auto sch = ctx.get_scheduler();

    exec::async_scope scope;
    std::atomic<int> done{0};

    for (int i = 0; i < 5; ++i) {
        scope.spawn(starts_on(sch, just() | then([&done, i] {
            std::this_thread::sleep_for(std::chrono::milliseconds(50 * i));
            std::cout << "task " << i << " finished\n";
            ++done;                       // spawn takes senders with NO value
        })));
    }

    std::cout << "carrying on, " << done.load() << " done so far\n";

    sync_wait(scope.on_empty());          // the join point
    std::cout << "all joined, " << done.load() << " done\n";
}
