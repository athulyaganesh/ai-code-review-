# AI Code Review Demo for Legacy C++ (PR-Agent + Clang tools)

A small legacy-style C++ codebase (deli scale pricing and labels, with old and dead code
from "2009") that shows a full PR quality pipeline:

**build -> unit tests -> clang-format / clang-tidy / Static Analyzer / IWYU -> AI review**

All static checks run on **changed code only**, so legacy code doesn't drown the PR in
warnings. Only the build and unit tests decide pass/fail; everything else is advisory.

## What this demonstrates

- **Layered checks.** Deterministic tools catch what they're good at (uninitialized
  variables, buffer overflows, undefined behavior, include hygiene, formatting); the AI
  reviewer reads their output plus the diff, explains real impact, catches logic errors no
  tool can see (wrong unit conversion, inverted conditions), and drops noise.
- **Legacy-aware.** Dead code, `#if 0` blocks and old APIs on `main` are never flagged
  unless a PR touches them. Old-style C++ is labeled "Suggestion", never "Bug".
- **Domain-tuned.** A review guide focuses the AI on weights, money rounding, label
  buffers and PLU handling.
- **Cost-controlled and safe.** No re-review on every push, token caps, ignore paths,
  pinned action version, least-privilege permissions, rules read from `main`.

## The pipeline

| Stage | Tool | Scope | Blocks merge? |
|---|---|---|---|
| Build | clang++ `-Wall -Wextra` | whole project | yes |
| Unit tests | CTest | whole project | yes |
| Formatting | clang-format (`git clang-format --diff`) | changed lines | no |
| Linting | clang-tidy (`clang-tidy-diff.py`) | changed lines | no |
| Deep bug hunting | Clang Static Analyzer (`tools/analyze_changed.py`) | changed files | no |
| Header hygiene | include-what-you-use | changed files | no |
| AI review | PR-Agent | diff + all the output above | no |

Each run also writes a "Static checks" summary to the GitHub Actions job page.

## AI commands (comment on a PR)

`/review` re-run review · `/improve` code suggestions · `/describe` summary · `/ask <question>`

## Run locally

```bash
cmake -S . -B build -DCMAKE_CXX_COMPILER=clang++
cmake --build build
ctest --test-dir build --output-on-failure
git clang-format --diff main                        # formatting of your changes
clang-tidy -p build src/label.cpp                   # lint one file
python3 tools/analyze_changed.py build src/*.cpp    # static analyzer
```

## Files

- `src/`, `include/scale/`: pricing, PLU table, units (legacy), labels
- `tests/`: unit tests (tiny built-in checker, no framework needed)
- `.clang-tidy`, `.clang-format`: tool configs (bug-finding checks first)
- `tools/`: changed-file helper and Static Analyzer runner
- `.github/workflows/ci.yml`: the pipeline
- `.github/ai-review/REVIEW_GUIDE.md`: what the AI reviewer focuses on
- `.pr_agent.toml`: model and cost settings

## Data & security

- Sample code only. PR-Agent is open source (MIT) and runs in GitHub Actions; code goes
  only to the configured model provider.
- This demo uses Gemini's free tier, which may use submitted data for training: fine for
  sample code only. For company code, use only the IT-approved Enterprise setup.

## Earlier Python demo

The first version of this demo (Python, same idea) is kept in `python-demo/` for reference.
It is not wired into CI anymore. `work-rollout/` holds templates for rolling this out
across several repos.
