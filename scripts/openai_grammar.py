import os
import subprocess
import tempfile
import argparse
import datetime

from pygit2 import init_repository, Signature
from pygit2.enums import MergeFavor, MergeFlag

from openai import OpenAI

def apply_patch(repo_path, patch_content):
    with tempfile.NamedTemporaryFile(mode='a', delete=False, encoding='utf-8') as tmp:
        tmp.write(patch_content)
        tmp.write("\n\n")
    
    subprocess.run(["git", "apply", "--3way", tmp.name], cwd=repo_path, check=False)
    subprocess.run(["git", "checkout", "--theirs", "--", "."], check=True)

if __name__ == "__main__":
    parser=argparse.ArgumentParser(description="")
    parser.add_argument("from_ref", type=str)
    parser.add_argument("to_ref", type=str)
    parser.add_argument("--dry-run", action='store_true', default=False)

    args = parser.parse_args()

    from_ref = args.from_ref
    to_ref = args.to_ref
    dry_run = args.dry_run
    
    repo_path = os.path.join(".")
    repo = init_repository(repo_path)

    fixed_branch = f"{to_ref}-fixed"

    from_ref_branch = repo.lookup_branch(from_ref)
    from_ref_commit = from_ref_branch.peel()

    to_ref_branch = repo.lookup_branch(to_ref)
    to_ref_commit = to_ref_branch.peel()

    # Move to source branch
    repo.set_head(f"refs/heads/{from_ref}")
    repo.checkout_tree(from_ref_commit)

    # Create branch to received the fix
    if fixed_branch in repo.branches:
        repo.branches.delete(fixed_branch) # In case of the branch already exists

    repo.branches.local.create(fixed_branch, from_ref_commit)

    # Get the patch we want to apply
    diff = repo.diff(from_ref, to_ref)
    patch = diff.patch

    if patch == None or patch.strip() == "":
        print("No change")
        exit()

    openai_request = [
            {
                "role": "user",
                "content": [
                    {
                        "type": "input_text",
                        "text": 
                        """
                            Tu es un correcteur orthographique spécialisé dans les fichiers Markdown (`.md`).
                            Je vais te fournir un patch Git. 
                            Ton role est de corriger les fautes de francais dans le patch git. 
                            Attention tu ne dois pas modifier la structure du patch et tu ne dois pas ajouter de ligne (corrige uniquement les fautes dans les mots).
                            Répond en fournissant uniquement le patch pour qu'il soit directement enregistrable dans un fichier (sans utiliser de caractères d'échappements).
                            Fait attention de ne pas toucher la structure du patch : les caractères en fin de fichier notamment.
                        """
                    },
                    {
                        "type": "input_text",
                        "text": patch
                    }
                ]
            }
        ]

    client = OpenAI()

    response = client.responses.create(model="gpt-4.1", input=openai_request)

    if dry_run == False:
        # Apply patch and write commit on fixed branch
        repo.set_head(f"refs/heads/{fixed_branch}")

        apply_patch(repo_path, response.output_text)

        repo.index.add_all()

        repo.index.write()

        tree = repo.index.write_tree()

        author = Signature("Thomas Le Goff", "thomaslegoff56@laposte.net", int(datetime.datetime.now().timestamp()), 0)

        try:
            parents = [repo.revparse_single("HEAD").id]
        except KeyError:
            parents = []

        commit_oid = repo.create_commit(
            "HEAD",
            author,
            author,
            "fix: spelling correction",
            tree,
            parents
        )

        # git merge -s ours base --no-edit
        repo.merge(to_ref_commit.id, favor=MergeFavor.OURS)

        tree = repo.index.write_tree()

        repo.create_commit('HEAD', author, author, "Merge commit", tree, [repo.head.target, to_ref_commit.id])

        repo.state_cleanup()

        # Todo: push branch to github and open PR
    else:
        print(response.output_text)
