#!/usr/bin/env python3

## Language spellchecker script (run in CI).
##
## It takes the patch between two git references (two commits) submits it to OpenAI spelling correction.
## Then the corrected patch is applied to a new branch submitted via a Github PR (see associated Github Action workflows).
## To reduce the number of tokens sent to the API, only markdown files (.md) are submitted and fixed.

import os
import subprocess
import tempfile
import argparse

from pygit2 import init_repository, Patch
from pygit2.enums import CheckoutStrategy

from openai import OpenAI

class Git():
    
    def __init__(self, repo_path: str, source_ref: str, target_ref: str, fix_branch: str) -> None:
        self._repo_path = repo_path
        self._repo = init_repository(repo_path)

        self._source_commit, _ = self._repo.resolve_refish(source_ref)
        self._target_commit, _ = self._repo.resolve_refish(target_ref)
        
        fixed_branch_ref = fix_branch
        if fixed_branch_ref in self._repo.branches:
            self._repo.branches.delete(fixed_branch_ref)
 
        self._fixed_branch = self._repo.branches.local.create(fixed_branch_ref, self._target_commit)

    def get_diff_patch(self, extensions=["md"]) -> str | None:
        diff = self._repo.diff(self._source_commit, self._target_commit)

        if type(diff) is Patch:
            return None

        filtered_patches = [
            patch for patch in diff
            if any(patch.delta.new_file.path.endswith(f".{e}") for e in extensions)
        ]

        if not filtered_patches:
            return None

        return ''.join(patch.text for patch in filtered_patches)

    def apply_patch(self, patch_content):
        with tempfile.NamedTemporaryFile(mode='a', delete=False, encoding='utf-8') as tmp:
            tmp.write(patch_content)
            tmp.write("\n\n")
        
        subprocess.run(["git", "apply", "--3way", tmp.name], cwd=self._repo_path, check=False)
        subprocess.run(["git", "checkout", "--theirs", "--", "."], check=True)

    def _checkout_branch(self, branch_name: str, force: bool = False):
        self._repo.set_head(f"refs/heads/{branch_name}")
        self._repo.checkout(f"refs/heads/{branch_name}", strategy=CheckoutStrategy.FORCE if force else CheckoutStrategy.SAFE)

    def commit(self):
        initial_head = self._repo.head
        
        self._checkout_branch(self._fixed_branch.branch_name)

        self._repo.index.add_all()
        self._repo.index.write()
        tree = self._repo.index.write_tree()

        author = self._repo.default_signature

        try:
            parents = [self._repo.revparse_single("HEAD").id]
        except KeyError:
            parents = []

        self._repo.create_commit(
            "HEAD",
            author,
            author,
            "fix: spelling correction",
            tree,
            parents # type: ignore
        )
        
        self._repo.state_cleanup()

        self._checkout_branch(initial_head.shorthand, True)

class OpenAiPatchFixer():

    def __init__(self) -> None:
        pass
        self._client = OpenAI()

    def fix_patch(self, patch_content: str) -> str:
        openai_request: list = [
            {
                "role": "user",
                "content": [
                    {
                        "type": "input_text",
                        "text": 
                        """
                            You're a spellchecker specialising in Markdown files (`.md`).
                            I'm going to provide you with a Git patch. 
                            Your role is to correct the spelling mistakes in the git patch.
                            You have to adapt to the original language.
                            Please note that you must not modify the structure of the patch and you must not add any lines (only correct the errors in the words).
                            Answer by providing only the patch so that it can be saved directly to a file (without using escape characters).
                            Be careful not to touch the structure of the patch: the characters at the end of the file in particular.
                        """
                    },
                    {
                        "type": "input_text",
                        "text": patch_content
                    }
                ]
            }
        ]

        response = self._client.responses.create(model="gpt-4.1", input=openai_request)
        return response.output_text
        

if __name__ == "__main__":
    parser=argparse.ArgumentParser(description="")
    parser.add_argument("from_ref", type=str)
    parser.add_argument("to_ref", type=str)
    parser.add_argument("fix_branch", type=str)

    args = parser.parse_args()
    
    git = Git(os.path.join("."), args.from_ref, args.to_ref, args.fix_branch)

    patch = git.get_diff_patch()

    if patch == None or patch.strip() == "":
        exit()

    patch_fixer = OpenAiPatchFixer()

    fixed_patch = patch_fixer.fix_patch(patch)

    git.apply_patch(fixed_patch)

    git.commit()

    print(fixed_patch)