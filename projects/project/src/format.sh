#!/bin/bash
script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
target_dir="$script_dir"

find "$target_dir" -type f \( -name "*.cc" \) -exec clang-format --style="{IndentWidth: 4, UseTab: Always}" -style=Microsoft -i {} \;
find "$target_dir" -type f \( -name "*.h" \) -exec clang-format --style="{IndentWidth: 4, UseTab: Always}" -style=Microsoft -i {} \;

echo "Formatting completed."
