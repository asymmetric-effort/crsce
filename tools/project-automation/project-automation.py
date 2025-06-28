#!/usr/bin/env python3
"""
project-automation.py
(c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

Sync a GitHub Project with a PROJECT.yaml definition.

Reads PROJECT.yaml, then uses the `gh` CLI to:
  - create or find the Project
  - create any missing custom fields
  - create or update Issues
  - add Issues to the Project and set field values
"""

import subprocess
import sys
from pathlib import Path
import yaml
def run(cmd: list[str]) -> str:
    """
    Run a shell command, raise on error, and return its stdout.
    """
    result = subprocess.run(cmd, check=True, stdout=subprocess.PIPE, text=True)
    return result.stdout.strip()


def load_project_definition(path: Path) -> dict:
    """
    Load and parse PROJECT.yaml.
    """
    with path.open() as f:
        return yaml.safe_load(f)


def find_or_create_project(meta: dict) -> str:
    """
    Find an existing project by title, or create it.
    Returns the GraphQL project ID.
    """
    owner = meta["owner"]
    title = meta["title"]

    # try to find
    listing = run(["gh", "project", "list", "--owner", owner,
                   "--json", "id,title"])
    for obj in yaml.safe_load(listing):
        if obj["title"] == title:
            return obj["id"]

    # create new
    out = run([
        "gh", "project", "create",
        "--owner", owner,
        "--title", title,
        "--description", meta.get("description", ""),
        "--public" if meta.get("public", False)
        else "--format", "json"
    ])
    return yaml.safe_load(out)["id"]


def ensure_fields(proj_id: str, fields: list[dict]) -> None:
    """
    Create any missing custom fields on the project.
    """
    for fld in fields:
        name, typ = fld["name"], fld["type"]
        # ignore errors if already exists
        subprocess.run(
            [
                "gh", "project", "field-create", proj_id,
                "--name", name, "--type", typ
            ],
            check=False
        )


def sync_issues(proj_id: str, meta: dict, issues: list[dict]) -> None:
    """
    For each issue spec:
      - create Issue (if needed)
      - add it to the Project
      - set any field-values
    """
    owner = meta["owner"]
    repo = run(["gh", "repo", "view", "--json", "name", "--jq", ".name"])
    for spec in issues:
        # create the GitHub Issue
        issue_out = run([
            "gh", "issue", "create",
            "--repo", f"{owner}/{repo}",
            "--title", spec["title"],
            "--body", spec.get("body", ""),
            "--label", ",".join(spec.get("labels", [])),
            "--assignee", spec.get("assignee", ""),
            "--format", "json"
        ])
        num = yaml.safe_load(issue_out)["number"]

        # add to project
        item_out = run([
            "gh", "project", "item", "add", proj_id,
            "--issue", f"{owner}/{repo}#{num}",
            "--format", "json"
        ])
        item_id = yaml.safe_load(item_out)["id"]

        # set custom fields
        for field, val in spec.get("fields", {}).items():
            run([
                "gh", "project", "field-value", "set", item_id,
                "--field", field,
                "--value", val
            ])


def main():
    project_def = load_project_definition(Path("PROJECT.yaml"))
    meta = project_def["project"]
    fields = project_def.get("fields", [])
    issues = project_def.get("issues", [])

    proj_id = find_or_create_project(meta)
    ensure_fields(proj_id, fields)
    sync_issues(proj_id, meta, issues)
    print(f"Synced project {meta['title']} (ID={proj_id})")


if __name__ == "__main__":
    try:
        main()
    except subprocess.CalledProcessError as e:
        print(f"ERROR: Command `{e.cmd}` failed (exit {e.returncode})",
              file=sys.stderr)

        sys.exit(e.returncode)
