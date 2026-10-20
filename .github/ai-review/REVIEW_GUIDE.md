# AI Review Guide

Loaded from the default branch before every review, so a PR can't change these rules.

## What this repo is
Pricing and label logic for a retail deli scale: PLU lookup, tare, price per pound,
label text. C++14, CMake. Money is integer cents; weight is integer milli-pounds.
The code deliberately follows an older style (C strings, `NULL`, `#define` constants,
C-style casts) like a long-lived legacy codebase. `units.cpp` dates back to 2009.

## Check on every PR
Not every PR has a bug. "No major issues found" is a valid result. Do not invent problems.

1. **Does the logic match the intent?** Compare the code to the PR title/description.
   Flag mismatches, missed cases, inverted or incomplete conditions, wrong unit conversions.
2. **Crashes and undefined behavior:** null/dangling pointer dereference, use-after-free,
   double delete, `new[]`/`delete` mismatch, buffer overflow (`strcpy`, `sprintf`, fixed arrays),
   out-of-bounds and off-by-one, divide by zero, integer overflow, signed/unsigned mix-ups,
   uninitialized variables, ignored return codes.
3. **Resource leaks:** memory, file handles, locks.

## Classify every finding
- **Bug / Must fix** - incorrect behavior, crash, UB, leak, wrong weight/price/rounding.
- **Risk** - likely problem under realistic conditions.
- **Suggestion (legacy modernization)** - optional only. Never call these bugs:
  `NULL` -> `nullptr`, C-style casts -> `static_cast`, `#define` -> `constexpr`,
  raw arrays -> `std::array`, `char*` -> `std::string`, manual loops -> range-for.

## Legacy code ground rules
- Comment only on lines changed in this PR and directly affected code.
- Match the file's existing style. Don't ask for refactors of untouched code,
  C++ standard bumps, new libraries or rewrites.
- Skip formatting-only nits. Prefer small, low-risk fixes.

## Dead and old code
This repo has old code on purpose: unused functions, `#if 0` blocks, commented-out code,
legacy APIs "kept for old firmware".
- Do NOT flag dead or old code the PR did not touch.
- If the PR touches a legacy function, review only the changed lines for real bugs.
- If the PR adds new dead code (unused function/variable/include), mention it as a Suggestion.
- Never recommend deleting legacy APIs: they may be used by other builds.

## Static analysis (CI output, changed code only)
- **Compiler warnings, clang-tidy `bugprone-*` / `clang-analyzer-*`, Clang Static Analyzer:**
  likely Bug or Risk. Explain the real impact in plain terms and how to fix it.
- **clang-tidy `modernize-*` / `performance-*`:** Suggestions only.
- **include-what-you-use:** Suggestions only (unused or missing includes).
- **clang-format:** not your job. Never comment on formatting.
- Don't repeat every warning. Group duplicates, skip false positives in context, and
  mention a real bug even if no tool caught it.

## Watch closely in this repo
- Weight units (lb / milli-lb / g / kg) and conversions; tare; zero or negative weights.
- Money: integer cents, round half-up, no floating point for prices.
- Label text: field lengths, buffer sizes, null termination.
- Unknown PLUs must be handled, never dereferenced.
