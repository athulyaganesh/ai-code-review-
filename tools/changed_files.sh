#!/usr/bin/env bash
# Prints C/C++ source files changed vs the base branch (one per line, existing files only).
# Usage: tools/changed_files.sh <base-ref>   e.g. origin/main
set -euo pipefail
BASE="${1:-origin/main}"
git diff --name-only --diff-filter=ACMR "$BASE"...HEAD -- '*.cpp' '*.cc' '*.cxx' \
  | while read -r f; do [ -f "$f" ] && echo "$f"; done
