#include <iostream>

#include <stdexec/execution.hpp>
#include "exec/static_thread_pool.hpp"

using namespace stdexec;
using stdexec::sync_wait;

int main()
{
    exec::static_thread_pool ctx{8};
    scheduler auto sch = ctx.get_scheduler();

    sender auto a = schedule(sch) | then([] { return 13; });
    sender auto b = schedule(sch) | then([] { return 29; });

    // sync_wait receiver called with set_value(int, int)
    auto [x, y] = sync_wait(when_all(std::move(a), std::move(b))).value();
    std::cout << x << " + " << y << " = " << x + y << "\n";
}
