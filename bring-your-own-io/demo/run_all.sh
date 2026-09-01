#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR="${1:-build}"
mkdir -p "$BUILD_DIR"
cmake --build "$BUILD_DIR" --target demos -j"$(nproc 2>/dev/null || echo 4)"

for demo in 00_base 01_thread_count 02_second_then \
            03_error_recovery 04_when_all 05_two_pools 06_async_scope; do
    printf '\n\033[1;36m===== %s =====\033[0m\n' "$demo"
    "$BUILD_DIR/$demo"
done
