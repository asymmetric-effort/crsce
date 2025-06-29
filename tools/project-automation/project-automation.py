#!/usr/bin/env python3
"""
project-automation.py
(c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

Sync a GitHub Project with a PROJECT.yaml definition.

Reads PROJECT.yaml, then uses the `/usr/local/bin/gh` CLI to:
  - create or find the Project
  - create any missing custom fields
  - create or update Issues
  - add Issues to the Project and set field values
"""

import sys
import json
import yaml
import subprocess
from pathlib import Path

GITHUB_CLI = "gh"


def run(cmd: list[str]) -> str:
    """
        Run a shell command, raise on error, and return its stdout.

        :param cmd: list[str]
        :return: str
    """
    print(f"run() starting (cmd:{cmd})")
    result = subprocess.run(cmd, check=True, stdout=subprocess.PIPE, text=True)
    return result.stdout.strip()


def load_project_definition(path: Path) -> dict:
    """
        Load and parse PROJECT.yaml.

        :param path: Path
        :return dict
    """
    print(f"load_project_definition() path={path}")
    with path.open() as f:
        return yaml.safe_load(f)


def find_or_create_project(meta: dict) -> str:
    """
        Find an existing project by title, or create it.
        Returns the GraphQL project ID.

        :param meta: dict
        :return str
    """
    print(f"find_or_create_project(): {meta}")
    owner = meta["owner"]
    title = meta["title"]
    listing = run([
        GITHUB_CLI, "project", "list",
        "--owner", owner,
        "--format", "json"
    ])
    projects = yaml.safe_load(listing)
    raw = run([
        GITHUB_CLI, "project", "list", "--owner", owner, "--format", "json"
    ])
    try:
        projects = json.loads(raw)
    except json.JSONDecodeError:
        projects = [json.loads(line) for line in raw.splitlines() if line.strip()]

    print(f"projects: {projects}")
    for obj in projects:
        print(f"  title={title} of {obj}")
        if obj.get("title") == title:
            return obj["id"]

    # create new
    out = run([
        GITHUB_CLI, "project", "create",
        "--owner", owner,
        "--title", title,
        "--description", meta.get("description", ""),
        "--public" if meta.get("public", False)
        else "--format", "json"
    ])
    result = yaml.safe_load(out)["id"]
    print(f"find_or_create_project() done. result:{result}")
    return result


def ensure_fields(proj_id: str, fields: list[dict]) -> None:
    """
        Create any missing custom fields on the project.

        :param proj_id: str
        :param fields: list[dict]
        :return None
    """
    print(f"ensure_results() proj_id:{proj_id}, fields:{fields}")
    for fld in fields:
        name, typ = fld["name"], fld["type"]
        # ignore errors if already exists
        subprocess.run(
            [
                GITHUB_CLI, "project", "field-create", proj_id,
                "--name", name, "--type", typ
            ],
            check=False
        )
    print("ensure_fields() done")


def sync_issues(proj_id: str, meta: dict, issues: list[dict]) -> None:
    """
        For each issue spec:
          - create Issue (if needed)
          - add it to the Project
          - set any field-values

          :param proj_id: str
          :param meta: dict
          :param issues: list[dict]
          :return None
    """
    print("sync_issues() start. proj_id:{proj_id}, meta:{meta}, issues:{issues}")
    owner = meta["owner"]
    repo = run([GITHUB_CLI, "repo", "view", "--json", "name", "--jq", ".name"])
    for spec in issues:
        # create the GitHub Issue
        issue_out = run([
            GITHUB_CLI, "issue", "create",
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
            GITHUB_CLI, "project", "item", "add", proj_id,
            "--issue", f"{owner}/{repo}#{num}",
            "--format", "json"
        ])
        item_id = yaml.safe_load(item_out)["id"]

        # set custom fields
        for field, val in spec.get("fields", {}).items():
            run([
                GITHUB_CLI, "project", "field-value", "set", item_id,
                "--field", field,
                "--value", val
            ])


def main() -> int:
    """
        main function

        :return: int (exit code)
    """
    try:
        project_def = load_project_definition(Path("PROJECT.yaml"))
        print("main(): load_project_definition() returned")
        meta = project_def["project"]
        print(f"main(): meta={meta}")
        fields = project_def.get("fields", [])
        print(f"main(): fields={fields}")
        issues = project_def.get("issues", [])
        print(f"main(): issues={issues}")
        proj_id = find_or_create_project(meta)
        print(f"main(): proj_id={proj_id}")
        ensure_fields(proj_id, fields)
        print("main(): ensure_fields() returned")
        sync_issues(proj_id, meta, issues)
        print(f"Synced project {meta['title']} (ID={proj_id})")
        return 0
    except Exception as e:
        print(f"Error: {e}")
        return 1


if __name__ == "__main__":
    sys.exit(main())
