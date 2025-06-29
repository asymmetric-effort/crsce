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
from sys import exception

import yaml
import subprocess
from pathlib import Path

GITHUB = "/usr/bin/gh"


def run(cmd: list[str]) -> str:
    """
        Run a shell command, raise on error, and return its stdout.

        :param cmd: list[str]
        :return: str
    """
    print(f"run() starting (cmd:{cmd})")
    result = subprocess.run(cmd, check=True, stdout=subprocess.PIPE, text=True).stdout.strip()
    print(f"run() result: {result}")
    return result


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
    repo = run([GITHUB, "repo", "view", "--json", "name", "--jq", ".name"])
    for spec in issues:
        # create the GitHub Issue
        issue_out = run([
            GITHUB, "issue", "create",
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
            GITHUB, "project", "item", "add", proj_id,
            "--issue", f"{owner}/{repo}#{num}",
            "--format", "json"
        ])
        item_id = yaml.safe_load(item_out)["id"]

        # set custom fields
        for field, val in spec.get("fields", {}).items():
            run([
                GITHUB, "project", "field-value", "set", item_id,
                "--field", field,
                "--value", val
            ])


def main() -> int:
    """
        main function

        :return: int (exit code)
    """
    default_manifest = {
        "project": {
            "id": "not_set",
            "owner": "not_set",
            "title": "not_set",
            "description": "not_set",
            "public": False
        },
        "fields": [{}],
        "issues": [{}],
        "title": [{}]
    }

    def extract_value(source: dict, name: str, default_value: any = None, raise_on_default: bool = False) -> any:
        value = source.get(name, default_value)
        if raise_on_default and value == default_value:
            raise ValueError(f"{name} is missing value")
        return value

    try:
        project_manifest = Path("PROJECT.yaml")
        print(f"load_project_definition() path={project_manifest}")
        manifest: dict
        with project_manifest.open() as f:
            manifest = yaml.safe_load(f)
        print(f"yaml loaded {len(manifest)}")

        project = extract_value(manifest, "project", default_manifest["project"], False)
        proj_id = extract_value(project, "id", "", True)
        owner = extract_value(project, "owner", "", True)
        title = extract_value(project, "title", "", True)

        fields = extract_value(manifest, "fields", default_manifest["fields"], False)
        issues = extract_value(manifest, "issues", default_manifest["issues"], False)

        for field in fields:
            field_name=field.get("name","")
            field_type=field.get("type","")
            if field_name=="" or field_type=="":
                raise ValueError("field name or type is empty")
            result = subprocess.run(
                [GITHUB, "project", "field-create", proj_id, "--name", field_name, "--type", field_type],
                check=True,
                stdout=subprocess.PIPE, text=True
            ).stdout.strip()
            print(f"result:{result}")


            print(f"Sync project {title} (ID={proj_id})")
            sync_issues(proj_id, project, issues)
            print(f"Synced project {title} (ID={proj_id})")

        return 0
    except Exception as e:
        print(f"Error: {e}")
        return 1


if __name__ == "__main__":
    sys.exit(main())
