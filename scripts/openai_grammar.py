import os
import subprocess
import tempfile
import sys
import argparse

from pygit2 import init_repository
from openai import OpenAI

def apply_patch(repo_path, patch_content):
    with tempfile.NamedTemporaryFile(mode='w+', delete=True, encoding='utf-8') as tmp:
        tmp.write(patch_content)
        subprocess.run(["git", "apply", tmp.name], cwd=repo_path, check=True)
        
if __name__ == "__main__":
    parser=argparse.ArgumentParser(description="")
    parser.add_argument("from_ref", type=str)
    parser.add_argument("to_ref", type=str)
    parser.add_argument("--dry-run", action='store_true', default=False)

    args = parser.parse_args()

    from_ref = args.from_ref
    to_ref = args.to_ref
    dry_run = args.dry_run
    
    repo_path = os.path.join("..")
    repo = init_repository(repo_path)
    diff = repo.diff(to_ref, from_ref)
    patch = diff.patch

    repo.branches.local.create(f"{to_ref}-fixed")

    if patch == None:
        exit

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
        apply_patch(repo_path, response.output_text)