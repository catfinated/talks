// 03 — introduce an error, then recover from it.
#include <iostream>
#include <system_error>

#include <stdexec/execution.hpp>
#include "exec/static_thread_pool.hpp"

using namespace stdexec;
using stdexec::sync_wait;

int main()
{
    // Uncomment to show set_error propogates 
    // sync_wait(just_error(std::make_error_code(std::errc::io_error)));

    sender auto failing =
        just_error(std::make_error_code(std::errc::io_error))
        | upon_error([](std::error_code ec) {
              std::cout << "recovered from: " << ec.message() << "\n";
              return -1; // upon_error moves the completion back onto the value channel
          });
    
    auto [j] = sync_wait(std::move(failing)).value();
    std::cout << "Result: " << j << "\n";   // -1
}
