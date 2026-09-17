cmake_minimum_required(VERSION 3.25)
project(byoio_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# Pin to a known-good commit so the thing you rehearse against is the thing
# you present. Update the tag, rebuild, re-rehearse — in that order.
FetchContent_Declare(
  stdexec
  GIT_REPOSITORY https://github.com/NVIDIA/stdexec.git
  # NVIDIA/stdexec main @ 2026-09-16 (PR #2259). Pinned 17 Sep 2026.
  GIT_TAG        abcdee3d1cef5bd1ff5d22d5cb11c9364e58cf67
)
set(STDEXEC_BUILD_TESTS   OFF CACHE BOOL "" FORCE)
set(STDEXEC_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(stdexec)

# One target per variation. A compile error in one does not block the others.
set(BYOIO_DEMOS
  00_base
  01_thread_count
  02_second_then
  03_error_recovery
  04_when_all
  05_two_pools
  06_async_scope
)

foreach(demo IN LISTS BYOIO_DEMOS)
  add_executable(${demo} src/${demo}.cpp)
  target_link_libraries(${demo} PRIVATE STDEXEC::stdexec)
endforeach()

add_custom_target(demos DEPENDS ${BYOIO_DEMOS})
