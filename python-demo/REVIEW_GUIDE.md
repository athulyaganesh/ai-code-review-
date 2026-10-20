# AI Review Guide

The AI reviewer reads this before every review. It is loaded from the default
branch, so a PR can't change the reviewer's rules. Edit and merge to update it.

## What this repo is
Demo of pricing logic for a retail deli scale: PLU lookup, tare, $/lb pricing,
label sync to a back office. Python 3, Decimal for money, pytest for tests.

## Check on every PR
Not every PR has a bug. "No major issues found" is a valid result. Do not invent problems.

1. **Does the logic match the intent?** Compare the code to the PR title/description.
   Flag mismatches, missed cases, inverted or incomplete conditions.
2. **Crashes and undefined behavior:** None/null dereference, unchecked lookups,
   out-of-bounds and off-by-one, divide by zero, overflow, uninitialized state,
   swallowed exceptions or ignored error codes.
3. **Resource leaks:** files, sockets, connections, locks; missing timeouts on I/O.

## Classify every finding
- **Bug / Must fix** - incorrect behavior, crash, leak, security issue, wrong weight/price/rounding.
- **Risk** - likely problem under realistic conditions.
- **Suggestion (modernization)** - optional style or modernization only. Never call these bugs.

## Ground rules
- Comment only on lines changed in this PR and directly affected code.
- Match the file's existing style. No requests to refactor untouched code or rewrite modules.
- Skip formatting-only nits. Prefer small, low-risk suggestions.

## Watch closely in this repo
- Weight units (lb / kg / oz) and conversions; tare; zero or negative weights.
- Money: Decimal not float, ROUND_HALF_UP to the cent.
- Unknown PLUs must raise a clear error, not crash.
- Back-office calls: HTTPS, credentials from environment/secrets, timeouts, errors surfaced.
