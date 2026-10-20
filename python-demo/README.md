# AI Code Review Demo (PR-Agent)

Every pull request gets an automatic AI review after the unit tests run:
a PR summary, a review with findings, and line-level code suggestions.
It is advisory only: it never blocks a merge, and a human still approves.

## How it works

1. A PR is opened (or marked ready for review).
2. Unit tests run.
3. The AI review job runs after them, even if they failed. It reads:
   - the review guide `.github/ai-review/REVIEW_GUIDE.md` (from `main`, so a PR can't change it)
   - the PR diff
   - the last part of the test output
4. It posts three comments: **/describe** (summary), **/review** (findings), **/improve** (suggestions).

The guide tells it to check whether the logic matches what the PR says it does,
look for crashes, null/None errors and leaks, label findings as Bug / Risk /
Suggestion, and accept "no major issues" as a valid answer.

## Commands (comment on a PR)

| Command | What it does |
|---|---|
| `/review` | Re-run the review (e.g. after new commits) |
| `/improve` | Fresh code suggestions |
| `/describe` | Regenerate the PR summary |
| `/ask <question>` | Ask about the change |

## Cost controls

- No re-review on every push: runs on open / reopen / ready. Comment `/review` to re-run.
- Skips draft PRs and bot events; cancels stale runs when new commits land.
- Cheaper model for descriptions and `/ask` (Haiku when on Claude).
- Each call capped at 32K input tokens; oversized diffs are clipped.
- `[ignore]` keeps vendored, generated and binary files out of the prompt.
- At most 6 findings; low-value suggestions hidden.

Small, focused PRs get better reviews and cost less. Large PRs get clipped and reviewed worse.

## Setup

1. Add a repo secret: **Settings -> Secrets and variables -> Actions**.
   - Demo: `GEMINI_API_KEY` from <https://aistudio.google.com/>
   - Claude: `ANTHROPIC_KEY` from the Claude Console, then switch the model lines in `.pr_agent.toml`
     and the key line in the workflow.
2. Open a PR.

## Files

- `.github/workflows/pr_agent.yml` - tests, then AI review
- `.github/ai-review/REVIEW_GUIDE.md` - what the reviewer should focus on
- `.pr_agent.toml` - model and cost settings
- `scale/`, `tests/` - sample deli-scale pricing code and tests
- `work-rollout/` - templates for rolling this out across several work repos

## Data & security

- PR-Agent is open source (**MIT license**) and runs inside our own GitHub Actions.
  No Qodo service is in the loop; code goes only to the model provider configured.
- Gemini's free tier may use submitted data to improve Google's models: fine for this demo only.
  For proprietary code use the Claude API: inputs/outputs aren't used for training by default
  and are deleted within 30 days (zero-data-retention available on request).
- The action is pinned to a fixed PR-Agent release, not `@main`.
- The job has read access to code and can only post PR comments.

## What this demonstrates

- **AI code review in CI.** Every pull request gets an automatic first-pass review
  (summary, findings, line-level suggestions) using open-source PR-Agent and an LLM.
- **Pipeline integration.** Unit tests run first; the reviewer reads the test output and
  points to the likely cause of failures. It is advisory and never blocks a merge.
- **Domain-tuned review.** A review guide steers the model toward what matters here:
  whether the logic matches the PR's stated intent, crashes and None errors, weight-unit
  and money-rounding mistakes. It labels findings Bug / Risk / Suggestion and treats
  "no issues" as a valid result.
- **Cost control by design.** Event filtering (no re-review on every push, no drafts or
  bots), a cheaper model for summaries, token caps, ignore paths and finding limits.
- **Security hardening.** Pinned action version, least-privilege permissions, secrets in
  GitHub Actions, and review rules read from `main` so a PR can't rewrite them.
- **Evaluation.** Tested against PRs with planted bugs (wrong unit conversion, inverted
  checks, off-by-one, hardcoded credentials, float money math) to measure what the
  reviewer catches and misses.
- **Portability.** Model and git host are swappable (Claude, Gemini, Bedrock/Azure;
  GitHub, GitLab, Azure DevOps), and a central reusable workflow serves many repos.
