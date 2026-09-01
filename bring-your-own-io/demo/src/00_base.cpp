// 00 — the base example. Trimmed from stdexec/examples/hello_world.cpp
#include <iostream>

#include <stdexec/execution.hpp>
#include "exec/static_thread_pool.hpp"

using namespace stdexec;
using stdexec::sync_wait;

int main()
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
    std::cout << "Result: " << i << "\n";
}
