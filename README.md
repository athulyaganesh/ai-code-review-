# AI Code Review Demo (PR-Agent + free Gemini)

Every pull request in this repo gets an automatic AI review: a PR description,
a review with findings, and line-level code suggestions. Cost: $0 (GitHub
Actions free minutes + Gemini API free tier).

## What happens on a PR

- **Auto on open:** `/describe` (writes the PR summary), `/review` (bugs,
  security, effort estimate), `/improve` (inline code suggestions).
- **On demand:** comment on the PR with any of:
  - `/ask how does tare get validated?` – ask questions about the change
  - `/review` – re-run the review after new commits
  - `/improve` – fresh code suggestions
  - `/help` – list all commands

## Setup (one time)

1. Get a free API key at <https://aistudio.google.com/> → **Get API key**.
2. Repo **Settings → Secrets and variables → Actions → New repository secret**
   - Name: `GEMINI_API_KEY`, Value: your key
3. Merge `.github/workflows/pr_agent.yml` and `.pr_agent.toml` to `main`.
4. Open any PR. The `github-actions` bot comments within ~1–2 minutes.

To change the model or review focus, edit `.pr_agent.toml`.

## Files

- `.github/workflows/pr_agent.yml` – the GitHub Action
- `.pr_agent.toml` – model choice and domain-specific review instructions
- `scale/pricing.py` – sample deli-scale pricing code
- `tests/` – pytest tests

## Notes for a work rollout

- Gemini's **free tier may use submitted data to improve Google's models**.
  Fine for this demo; for proprietary code use a paid key with no-training
  terms, an enterprise endpoint (Azure OpenAI, Bedrock, Vertex), or a
  self-hosted model on a self-hosted runner.
- PR-Agent is open source (Apache-2.0) and runs entirely inside your own
  GitHub Actions; code goes only to the LLM provider you configure.
- Works the same on GitLab (CI job or webhook) and Bitbucket.
