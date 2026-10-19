# AI PR Review rollout (PR-Agent + Claude)

One central setup, reused by every repo. Pilot repos: **enterprise**, **gtscaleui**, **scaleservice**.

## How it fits together

```
central repo: ai-code-review
  .github/workflows/pr-review.yml   <- model, cost limits, shared review rules (edit once)

each product repo (enterprise, gtscaleui, scaleservice)
  .github/workflows/ci.yml          <- existing build/tests + ~15 lines that call the shared workflow
  .github/ai-review/REVIEW_GUIDE.md <- what this repo is, legacy areas, what to watch
```

Flow on a PR: build -> unit tests -> AI review (summary, review, suggestions).
The AI review never blocks a merge; a human still approves.

## Setup (one time)

1. **Central repo.** Create `ai-code-review` in the org. Add `central-repo/.github/workflows/pr-review.yml`.
   Then **Settings -> Actions -> General -> Access**: allow access from repositories in the organization.
   Tag a release (`git tag v1 && git push --tags`) so repos call a fixed version.
2. **API key.** Get a Claude Console **API** key (not chat seats) from IT. Ideally its own
   workspace with a monthly spend limit. Store it as an **organization secret** `ANTHROPIC_KEY`,
   shared only with the pilot repos.
3. **Each pilot repo.**
   - Merge the marked parts of `each-repo/.github/workflows/ci.yml` into its existing CI
     (replace `YOUR-ORG` and the build job id).
   - Copy `each-repo/.github/ai-review/REVIEW_GUIDE.md` and fill it in for that repo.
   - Do **not** make the AI review a required status check (yet).

To add another repo later: step 3 only.
To change model, cost caps or shared rules: edit the central workflow, tag `v2`, bump the `@v1` ref.

## Cost controls (all on by default)

- No re-review on every push: runs when a PR is opened, reopened or marked ready.
  Comment `/review` to re-run after changes.
- Skips draft PRs and bot events; cancels stale runs when new commits land.
- Cheaper Haiku model for descriptions and `/ask`; Sonnet for review and suggestions.
- Each call capped at 32K input tokens; oversized diffs are clipped.
- Vendor code, generated files, project files, lockfiles and binaries are never sent.
- Fewer, higher-quality findings (max 6 findings; low-score suggestions hidden).
- Monthly spend limit set in the Claude Console.

Small, focused PRs get better reviews and cost less. Large PRs are clipped and reviewed worse.

## Commands in a PR comment

| Command | What it does |
|---|---|
| `/review` | Re-run the review |
| `/improve` | Fresh code suggestions |
| `/describe` | Regenerate the PR summary |
| `/ask <question>` | Ask about the change |

## Data & security

- PR-Agent is open source (MIT license) and runs inside our own GitHub Actions runners.
  There is no Qodo service in the loop; code goes only to the model provider we configure.
- Anthropic API: inputs/outputs are not used for model training by default and are deleted
  within 30 days. Zero-data-retention agreements are available on request.
  Don't submit thumbs-up/down feedback with code in it (feedback is kept longer).
- Action is pinned to a fixed PR-Agent release, not `@main`.
- The review guide is read from the default branch, so a PR can't change the reviewer's rules.
- The job only has read access to code and write access to PR comments.
