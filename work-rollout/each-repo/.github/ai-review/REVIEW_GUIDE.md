# AI Review Guide: <REPO NAME>

The AI reviewer reads this before every review in this repo, on top of the
shared rules (logic vs. intent, crashes/null pointers, leaks, legacy-code
etiquette) that live in the central workflow. Keep this file short and specific.
Changes take effect once merged to the default branch.

## What this repo is
<!-- 2-3 lines. e.g. "Backend service that syncs PLU/price data between stores and scales." -->

## Tech stack
<!-- language(s), framework, C++ standard / compiler, target OS/hardware -->

## Known legacy areas
<!-- folders/modules that are old patchwork: modernization ideas there are Suggestions only -->
- e.g. `src/legacy/` – pre-C++11 code; don't flag raw pointers here as bugs unless they leak or crash

## Watch closely in this repo
<!-- the things that actually break in production for this codebase -->
- Weight units (lb/kg/oz/g), tare, zero/negative weights
- Money: rounding mode, integer cents vs floating point
- Label/barcode field lengths and formatting
- Serial/network I/O: timeouts, retries, error handling

## Our conventions
<!-- naming, error-handling pattern, logging, threading model -->

## Ignore
<!-- extra paths/patterns that are noise in this repo -->
