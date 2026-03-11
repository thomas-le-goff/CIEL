Ce TP a pour objectif de vous faire découvrir la gestion des fichiers en utilisant la fonction `open` et le module `os`.

## Outils à votre disposition

### Liens et références utiles pour ce TP

- [Documentation officielle de `open`](https://docs.python.org/fr/3/tutorial/inputoutput.html#reading-and-writing-files)
- [Documentation officielle du module `os`](https://docs.python.org/fr/3/library/os.html)
- [Documentation du module `csv`](https://docs.python.org/fr/3/library/csv.html)

### Éditeur de code

Pour ce TP il n'est pas nécessaire d'utiliser de carte MicroBit, vous pouvez utiliser l'éditeur de votre choix :

- Visual Studio Code
- Geany

## 1 - Découverte de `open` et de `os`

Ces exercices ont pour objectifs de vous faire découvrir quelques usages courants de `open` et `os`.

### Exercice 1 - Créer et écrire dans un fichier

**Objectif** : Créer un fichier texte et y écrire une phrase.

```python
with open("mon_fichier.txt", "w", encoding="utf-8") as f:
    f.write("Bonjour, je suis un fichier créé avec Python !\n")
```

Questions :

- Que se passe-t-il si le fichier `mon_fichier.txt` existe déjà ?
- Quel est le rôle du paramètre `"w"` dans la fonction `open` ?
- Pourquoi utilise-t-on `encoding="utf-8"` ?
- Que signifie le `\n` à la fin de la phrase ? (essayer de trouver une alternative dans le module `os`)

### Exercice 2 - Lire le contenu d’un fichier

**Objectif** : Lire et afficher le contenu d’un fichier créé précédemment.

```python
with open("mon_fichier.txt", "r", encoding="utf-8") as f:
    contenu = f.read()
    print(contenu)
```

Questions :

- Que se passe-t-il si le fichier `mon_fichier.txt` n’existe pas ?
- Quelle est la différence entre les modes `"w"` et `"r"` ?
- Pourquoi utilise-t-on `with` pour ouvrir le fichier ?

### Exercice 3 - Lire un fichier ligne par ligne

Exemple de fichier : [data.text](/ciel1/s1-3-gestion-fichiers-python/data.text) (pensez à la renomme `data.txt`)

```python[data.text](/ciel1/s1-3-gestion-fichiers-python/data.text)
with open("data.txt", "r", encoding="utf-8") as f:
    for ligne in f:
        ligne = ligne.strip()
        print("→", ligne)
```

Lire un fichier ligne par ligne (v2) :

```python
with open("data.txt", "r") as f:
    lignes = f.readlines()
    for ligne in lignes:
        ligne = ligne.strip()
        print("→", ligne)
```

Questions :

- Quelle est la différence entre les deux versions ?
- Pourquoi utilise-t-on `strip()` ?

### Exercice 4 - Ouvrir un fichier et le créer s’il n’existe pas

```python
with open("log.txt", "a", encoding="utf-8") as f:
    f.write("Nouvelle entrée dans le fichier.\n")
```

> Exécutez le programme plusieurs fois pour comprendre l'intérêt du mode `a`.

Questions :

- Quel est le rôle du mode `"a"` ?
- Que se passe-t-il si le fichier `log.txt` n’existe pas ?
- Comment faire pour ajouter une date et une heure à chaque entrée ?

### Exercice 5 - Lire un fichier CSV

Exemple de fichier : [donnees.csv](/ciel1/s1-3-gestion-fichiers-python/donnees.csv)

```python
with open("donnees.csv", "r", encoding="utf-8") as f:
    for ligne in f:
        cellules = ligne.strip().split(",")
        print(cellules)
```

Encore mieux : le module `csv` :

```python
import csv

with open("donnees.csv", "r", newline="", encoding="utf-8") as f:
    lecteur = csv.reader(f)
    for ligne in lecteur:
        print(ligne)
```

Questions :

- Pourquoi utilise-t-on `newline=""` dans la fonction `open` ?
- Quelle est la différence entre `split(",")` et `csv.reader` ?
- Comment gérer un fichier CSV avec des délimiteurs différents (par exemple, `;`) ?

### Exercice 6 - Charger un fichier par défaut

```python
import os

fichier_principal = "config.txt"
fichier_defaut = "config_default.txt"

if os.path.exists(fichier_principal):
    chemin = fichier_principal
else:
    chemin = fichier_defaut

with open(chemin, "r", encoding="utf-8") as f:
    contenu = f.read()

print(contenu)
```

Questions :

- À quoi sert la fonction `os.path.exists` ?
- Comment modifier ce code pour afficher un message si aucun des deux fichiers n’existe ?
- Comment vérifier si un fichier est vide avant de le lire ?

### Exercice 7 - Passer en majuscule toutes les lignes d’un fichier

```python
with open("entree.txt", "r", encoding="utf-8") as fin:
    with open("sortie.txt", "w", encoding="utf-8") as fout:
        for ligne in fin:
            fout.write(ligne.upper())
```

Questions :

- Pourquoi ouvre-t-on deux fichiers en même temps ?
- Comment faire pour que le fichier de sortie ait le même nom que le fichier d’entrée, mais avec le suffixe `_MAJ` ?
- Comment adapter se code pour réécrire dans `entree.txt` plutôt que dans `sortie.txt` ?

### Exercice 8 - Création et gestion de dossiers

Objectif : Créer une arborescence de dossiers, vérifier leur existence et les supprimer si nécessaire.

#### Énoncé
1. Créez un dossier nommé `mon_super_projet` dans le répertoire courant.
2. À l’intérieur de `mon_super_projet`, créez deux sous-dossiers : `src` et `docs`.
3. Vérifiez que les dossiers ont bien été créés en affichant leur chemin absolu.
4. Supprimez le dossier `docs` et vérifiez qu’il n’existe plus.

#### Code de base à compléter
```python
import os

if not os.path.exists("mon_super_projet"):
    os.mkdir("mon_super_projet")
    print("Dossier 'mon_super_projet' créé.")
else:
    print("Le dossier 'mon_super_projet' existe déjà.")

chemin_src = os.path.join("mon_super_projet", "src")
chemin_docs = os.path.join("mon_super_projet", "docs")

if not os.path.exists(chemin_src):
    os.mkdir(chemin_src)
    print(f"Dossier '{chemin_src}' créé.")

if not os.path.exists(chemin_docs):
    os.mkdir(chemin_docs)
    print(f"Dossier '{chemin_docs}' créé.")

print(f"Chemin absolu de 'src' : {os.path.abspath(chemin_src)}")
print(f"Chemin absolu de 'docs' : {os.path.abspath(chemin_docs)}")

if os.path.exists(chemin_docs):
    os.rmdir(chemin_docs)
    print(f"Dossier '{chemin_docs}' supprimé.")
else:
    print(f"Le dossier '{chemin_docs}' n'existe pas.")
```

Questions :
- Pourquoi utilise-t-on `os.path.exists` avant de créer un dossier ?
- Quel est le rôle de `os.path.join` ?
- Que se passe-t-il si on essaie de supprimer un dossier non vide avec `os.rmdir` ?
- Comment faire pour supprimer un dossier et tout son contenu (y compris les sous-dossiers et fichiers) ?

### Exercice 9 - Lister et parcourir les fichiers d’un dossier

Objectif : Lister les fichiers et dossiers d’un répertoire, puis déplacer un fichier d’un dossier à un autre.

#### Énoncé
1. Dans le dossier `mon_super_projet`, créez un fichier nommé `fichier_test.txt` avec un contenu quelconque.
2. Listez tous les fichiers et dossiers présents dans `mon_super_projet`.
3. Déplacez le fichier `fichier_test.txt` dans le dossier `src`.
4. Vérifiez que le fichier a bien été déplacé en listant à nouveau le contenu de `mon_super_projet` et de `src`.

#### Code de base à compléter
```python
import os

chemin_fichier = os.path.join("mon_super_projet", "fichier_test.txt")
with open(chemin_fichier, "w", encoding="utf-8") as f:
    f.write("Contenu de test pour le fichier.")

print("Contenu initial de 'mon_super_projet' :")
for element in os.listdir("mon_super_projet"):
    print(f"- {element}")

chemin_destination = os.path.join("mon_super_projet", "src", "fichier_test.txt")
if os.path.exists(chemin_fichier):
    os.rename(chemin_fichier, chemin_destination)
    print(f"Fichier déplacé vers '{chemin_destination}'.")

print("\nContenu de 'mon_super_projet' après déplacement :")
for element in os.listdir("mon_super_projet"):
    print(f"- {element}")

print("\nContenu de 'src' après déplacement :")
for element in os.listdir(os.path.join("mon_super_projet", "src")):
    print(f"- {element}")
```

Questions :
- Pourquoi utilise-t-on `os.path.join` pour construire les chemins ?
- Quelle est la différence entre `os.listdir` et `os.scandir` ?
- Que se passe-t-il si le fichier de destination existe déjà lors de l’utilisation de `os.rename` ?
- Comment gérer les erreurs si le dossier de destination n’existe pas ?

## 2 - fail2ban V2

### Contexte du programme
Ce programme simule un [mini-fail2ban](https://fr.wikipedia.org/wiki/Fail2ban) en analysant un fichier de logs SSH pour détecter les adresses IP ayant trop de tentatives de connexion échouées. Il génère ensuite une liste noire (`blacklist`) des IP à bloquer.

### Fichiers manipulés par le programme

#### Fichier d'entrée : `auth.log`
Contenu :
Un fichier de logs SSH au format classique, comme celui-ci :
```
May 15 10:30:45 server sshd[1234]: Failed password for root from 192.168.1.100 port 22 ssh2
May 15 10:31:00 server sshd[1235]: Accepted password for admin from 192.168.1.101 port 22 ssh2
May 15 10:31:15 server sshd[1236]: Failed password for root from 192.168.1.100 port 22 ssh2
May 15 10:31:30 server sshd[1237]: Failed password for root from 192.168.1.100 port 22 ssh2
May 15 10:31:45 server sshd[1238]: Failed password for root from 192.168.1.100 port 22 ssh2
May 15 10:32:00 server sshd[1239]: Failed password for root from 192.168.1.100 port 22 ssh2
May 15 10:32:15 server sshd[1240]: Failed password for root from 192.168.1.100 port 22 ssh2
May 15 10:32:30 server sshd[1241]: Failed password for guest from 192.168.1.102 port 22 ssh2
```
- Chaque ligne représente une tentative de connexion SSH.
- Les lignes contiennent :
  - La **date et l'heure** de la tentative.
  - Le **statut** (`Accepted` ou `Failed`).
  - Le **nom d'utilisateur** cible.
  - L'**adresse IP** source.

> Exemple de fichier : [auth.log](/ciel1/s1-3-gestion-fichiers-python/auth.log)

##### Fichier de sortie : `blacklist`
Contenu :
Une liste d'adresses IP à bloquer, une par ligne :
```
192.168.1.100
192.168.1.102
```
- Ce fichier peut ensuite être utilisé par un script ou un outil (comme `iptables`) pour bloquer les IP.

### Étapes du programme

Le code suivant vous est fourni : 

```python
import re
from datetime import datetime


def parse_log_line(line: str) -> tuple:
    """
    Parse une ligne de log SSH et extrait les informations suivantes :
    - date_heure (objet datetime)
    - ip (str)
    - username (str)
    - success (bool : True = succès, False = échec)

    Exemple d'entrée :
    "May 15 10:30:45 server sshd[1234]: Failed password for root from 192.168.1.100 port 22 ssh2"

    Retourne un tuple : (date_heure, ip, username, success)
    """
    pattern = re.compile(
        r"(?P<month>\w+)\s+(?P<day>\d+)\s+(?P<hour>\d+:\d+:\d+)\s+.+?\s+sshd\[\d+\]:\s+(?P<status>Accepted|Failed)\s+password\s+for\s+(?P<username>\w+)\s+from\s+(?P<ip>\d+\.\d+\.\d+\.\d+)"
    )

    match = pattern.match(line)
    if not match:
        raise ValueError(f"Format de log invalide : {line}")

    month = match.group("month")
    day = match.group("day")
    hour = match.group("hour")
    ip = match.group("ip")
    username = match.group("username")
    success = match.group("status") == "Accepted"

    date_str = f"2026 {month} {day} {hour}"
    date_heure = datetime.strptime(date_str, "%Y %b %d %H:%M:%S")

    return (date_heure, ip, username, success)


def main():
    pass

if __name__ == "__main__":
    main()

```

#### 1. Parsing des logs
Objectif : Extraire les informations utiles de chaque ligne du fichier `auth.log`.

Etapes :
- Initialisez un dictionnaire `failedConnections` qui contiendra pour chaque IP le nombre de tentatives en échec.
- Pour chaque ligne du fichier de logs, utilisez la fonction `parse_log_line` afin de récupérer les informations suivantes :
	- La **date et l'heure** (ex : `May 15 10:30:45`).
  - L'**IP source** (ex : `192.168.1.100`).
  - Le **nom d'utilisateur** (ex : `root`).
  - Le **statut** de la connexion (`Accepted` ou `Failed`).
- Si la connexion a échouée (statut = `Failed`)
	- Si l'IP n'est pas présente dans le dictionnaire `failedConnections` il faut l'ajouter et initialiser le nombre de tentatives à 1.
  - Si l'IP est présente dans le dictionnaire il faut incrémenter le nombre de tentatives.

> `parse_log_line` retourne les informations sous forme de **tuple** : `(date_heure, ip, username, success)`.

Exemple de dictionnaire généré : 

```python
failedConnections = {"192.168.1.100" : 6, "192.168.1.102" : 1}
```
#### 2. Détection des IP à bannir
Objectif : déterminer quelles IP dépassent le **seuil d'échecs** (`threshold = 4`).

Etapes :
- Créez un **ensemble** (`set`) `toBanIps` qui contiendra les IP à bannir.
- On parcourt les entrées du **dictionnaire** `failedConnections`.
- Si une IP a un nombre d'échecs **supérieur au seuil**, elle est ajoutée à `toBanIps`.

#### 3. Génération de la liste noire
Objectif : écrire les IP à bannir dans un fichier `blacklist`.

Etapes :
- Ouvrez un fichier nommé `blacklist` en mode **ajout** (`"a"`) à l'aide de la fonction `open`.
- Pour chaque IP de `toBanIps` écrire une nouvelle ligne dans le fichier.
- Exemple de contenu final :
```
192.168.1.100
192.168.1.102
```

#### 4. Configuration du programme
Objectif: configurer le programme à l'aide d'un fichier au format `ini` ou `json`

Etapes :
- Au démarrage du programme vérifier si un fichier `config.json` ou `config.ini` existe dans le même dossier que le programme
- Ce fichier doit être chargé dans un dictionnaire (`dict`), chaque clé du dictionnaire correspond à un paramètre que l'utilisateur pourra modifier : 
	- Le seuil (`threshold`)
  - Le chemin d'export de la liste noire
- Adapter le reste du code pour utiliser les valeurs présente dans le dictionnaire de configuration
- Le fichier de configuration étant optionnel, le programme ne doit pas lever d'erreur s'il n'est pas présent et des valeurs par défaut adaptées doivent être utilisées.

> Astuce : vous pouvez vous aider des modules [`json`](https://docs.python.org/fr/3.10/library/json.html#module-json) et [`config-parser`](https://docs.python.org/fr/3.10/library/configparser.html)

Exemple de fichier de configuration :

```json
{
	"threshold": 4,
  "blacklist_file_path": "/tmp/blacklist.txt"
}
```