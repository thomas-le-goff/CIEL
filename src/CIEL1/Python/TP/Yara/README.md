# Analyse statique de fichiers avec Python et YARA_X

Dans ce TP, nous allons explorer l’analyse statique, comprendre les limites des expressions régulières, découvrir YARA et YARA_X, puis mettre en pratique la détection de fichiers suspects avec Python.  
Nous terminerons par un **cas réel de détection d’un webshell PHP obfusqué (Anuna)**.

## Qu’est-ce que l’analyse statique ?

L’analyse statique consiste à **examiner un fichier sans l’exécuter**.

Elle est utilisée en cybersécurité pour :
- Détecter des malwares
- Identifier des fichiers suspects
- Rechercher des signatures connues
- Inspecter du code obfusqué
- Repérer des comportements potentiellement dangereux

Elle est plus sûre que l’analyse dynamique car **aucun code n’est executé**.

## Expressions régulières : utile mais limité

Les **regex** permettent de rechercher des motifs dans du texte.

Exemple Python :

```python
import re

with open("password.txt", "r", encoding="utf-8") as f:
    content = f.read()

matches = re.findall(r"password\s*=\s*.+", content)

print(matches)
````

> Exemple de fichier : [password.txt](/ciel1/s1-3-python-yara/password.text)

_✍️ Testez le script Python précedent._

_✍️ Prenez le temps de parcourir le site https://regex101.com/ notamment la bibliothèque d'expressions régulières https://regex101.com/library pour découvrir ce qu'il est possible de faire avec des expressions régulières_

## Pourquoi les regex ne suffisent pas ?

Les expressions régulières ont plusieurs limites :

* Difficiles à maintenir sur de gros projets
* Fragiles face à l’obfuscation
* Peu adaptées aux fichiers binaires (elles sont faites pour inspecter du texte)
* Impossible de structurer proprement des règles complexes
* Pas de système de classification ou métadonnées

_✍️ Prenez le temps de bien comprendre les limites des expressions régulières. Demandez à l'IA des explications si certaines notions ne vous sembles pas claires._

## Présentation de YARA

Pour pallier les manques liées aux expressions régulières, un projet Open source maintenu et gouverné par VirusTotal https://www.virustotal.com/gui/home/upload permet d'appliquer ce principe à l'analyse et la détection de malwares directement dans des fichiers binaires.

YARA est un langage de **règles de détection** basé sur :

* Des chaînes de texte
* Des patterns hexadécimaux
* Des conditions logiques
* Des métadonnées descriptives

Voici un exemple de règle Yara qui a pour objectif de détecter les chaînes `cmd.exe` et/ou `powershell` :

```yara
rule Suspicious_File
{
    strings:
        $cmd = "cmd.exe"
        $ps  = "powershell"

    condition:
        any of them
}
```

## Différence entre YARA et YARA_X

Yara est un moteur d'analyse statique développé à l'origine par [Victor Manuel Alvarez](https://github.com/plusvic). Depuis, le moteur a été repris par la société VirusTotal qui a decidé de le réécrire en Rust avec une architecture différente pour obtenir de meilleures performance. 

* **YARA** = moteur historique
* **YARA_X** = version moderne développée par VirusTotal

**YARA_X** apporte :

* Meilleures performances
* Moteur plus sécurisé
* API Python moderne
* Support actif

Ressources :

* [https://virustotal.github.io/yara-x/](https://virustotal.github.io/yara-x/)
* [https://yara.readthedocs.io/](https://yara.readthedocs.io/)
* [https://virustotal.github.io/yara-x/docs/intro/yara-x-vs-yara/](https://virustotal.github.io/yara-x/docs/intro/yara-x-vs-yara/)

Dans la suite du document le terme Yara est utilisé pour parler du projet dans sa globalité, mais, c'est bien le moteur YARA_X qui est utilisé dans les programmes. 

## Mise en place de l’environnement Python (venv)

Yara est développé en Rust, mais, il est possible de l'utiliser avec d'autres langages au travers de bibliothèques fourni par VirusTotal. C'est notamment le cas pour Python.

Pour utiliser YARA avec Python il est nécessaire d'installer le package `yara-x`

Etant donné que vous n'avez pas les droits administrateurs, vous devez utiliser un **environnement virtuel**.

> ### Environnement virtuel Python
>Un environnement virtuel vous permet d'avoir une "version locale de Python" dédiée à un ou plusieurs projets. Cela évite d'affecter la version système de Python, chaque utilisateur peut alors installer des packages sans risquer de "casser" le système.
> #### Création du venv
> 
> ```bash
> python -m venv venv
> ```
> 
> #### Activation
> 
> **Linux / macOS**
> 
> ```bash
> source venv/bin/activate
> ```
> 
> #### Installation de YARA_X
> 
> ```bash
> pip install yara-x
> ```
> Pour bien comprendre le principe et le fonctionnement des environnements virtuels exécutez la commande `whereis python3` dans l'environnement virtuel et en dehors de l'environnement virtuel :
> ```shell
> thomaslegoff@info-2211 ~ → whereis python3
> python3: /usr/bin/python3 /usr/lib/python3 /etc/python3 /usr/share/python3 /usr/share/man/man1/python3.1.gz
> ```
> En dehors :
> ```shell
> ((.venv) ) thomaslegoff@info-2211 yara → whereis python
> python: /home/thomaslegoff/Téléchargements/yara/.venv/bin/python
>```

## Préparation des fichiers d’analyse

Créez un dossier `samples/`.

### `clean.txt`

```text
Bonjour, ceci est un fichier normal.
```

### `suspicious.txt`

```text
This program runs cmd.exe and powershell
```

### `malware_like.txt`

```text
connect to remote server
download payload
execute cmd.exe
```

## Première règle YARA_X

Créez `rules.yar` :

```yara
rule Suspicious_Commands
{
    meta:
        author = "CIEL Student"
        description = "Detects suspicious command usage"

    strings:
        $cmd = "cmd.exe"
        $ps  = "powershell"
        $net = "download payload"

    condition:
        any of them
}
```

## Script Python pour scanner des fichiers

Créez `scan.py` :

```python
import yara_x
import os

RULES_FILE = "rules.yar"
SAMPLES_DIR = "samples"

compiler = yara_x.Compiler()
with open(RULES_FILE, "r") as f:
    compiler.add_source(f.read())

rules = compiler.build()

for filename in os.listdir(SAMPLES_DIR):
    path = os.path.join(SAMPLES_DIR, filename)

    with open(path, "rb") as f:
        data = f.read()

		scan_result = rules.scan(data)
    matches = scan_result.matching_rules

    print(f"\nScanning: {filename}")

    if matches:
        for match in matches:
            print(f"  Rule matched: {match.identifier}")
    else:
        print("No match")
```

# Étude de cas réelle — Détection du webshell PHP Anuna

Un **webshell PHP** est un fichier malveillant permettant à un attaquant de **contrôler un serveur à distance**.

Le shell **Anuna** est un **webshell obfusqué**, conçu pour :

* Cacher son vrai comportement
* Éviter la détection antivirus
* Télécharger et exécuter du code distant

Vous disposerez d’un fichier réel :

```
php_anuna.php
```

Ce fichier contient :

* Du code fortement obfusqué
* Des appels à `explode()`, `chr()`, `function_exists()`
* Une logique typique de backdoor PHP

## Règle YARA_X pour détecter Anuna

Cette règle cible des motifs spécifiques à ce webshell :

```yara
rule php_anuna
{
    meta:
        author      = "Vlad https://github.com/vlad-s"
        date        = "2016/07/18"
        description = "Catches a PHP Trojan"

    strings:
        $a = /<\?php \$[a-z]+ = '/
        $b = /\$[a-z]+=explode\(chr\(\([0-9]+[-+][0-9]+\)\)/
        $c = /\$[a-z]+=\([0-9]+[-+][0-9]+\)/
        $d = /if \(!function_exists\('[a-z]+'\)\)/

    condition:
        all of them
}
```

## Script Python de détection du webshell

Créez `scan_anuna.py` :

```python
import yara_x


def main():
    compiler = yara_x.Compiler()
    compiler.add_source('''
    rule php_anuna
    {
        meta:
            author      = "Vlad https://github.com/vlad-s"
            date        = "2016/07/18"
            description = "Catches a PHP Trojan"

        strings:
           	$a = /<\?php \$[a-z]+ = '/
            $b = /\$[a-z]+=explode\(chr\(\([0-9]+[-+][0-9]+\)\)/
            $c = /\$[a-z]+=\([0-9]+[-+][0-9]+\)/
            $d = /if \(!function_exists\('[a-z]+'\)\)/

        condition:
            all of them
    }
    ''')

    rules = compiler.build()
    scanner = yara_x.Scanner(rules)

    try:
        result = scanner.scan_file("./php_anuna.php")

        if result.matching_rules:
            print("Match found:\n")
            for rule in result.matching_rules:
                print(f"Rule: {rule.identifier}")
                for pattern in rule.patterns:
                    for match in pattern.matches:
                        print(f"  Pattern: {pattern.identifier}")
                        print(f"  Offset: {match.offset}")
        else:
            print("File OK.")

    except yara_x.ScanError as err:
        print(err)


if __name__ == "__main__":
    main()
```
> Exemple de fichier : [php_anuna.php](/ciel1/s1-3-python-yara/php_anuna.php)

## Travail demandé

* Exécuter la détection sur `php_anuna.php`
* Observer quelles parties du fichier déclenchent la règle
* Identifier les morceaux de code qui semblent obfusqués
* Modifier la règle pour :
  * Être plus stricte
  * Être plus permissive
* Tester la règle sur un fichier PHP normal

> Cette règle utilise principalement des conditions basées sur Regex, vous pouvez utiliser le site [regex101](https://regex101.com/r/kp6JD1/1) pour tester chaque règle séparement et voir quelle partie du fichier correspond. Pensez aussi à tester la régle sur des fichiers PHP légitime, comme ceux des projets suivants  https://github.com/WordPress/WordPress/tree/master, https://git.spip.net/spip/spip 


## Questions de réflexion

* Pourquoi ce webshell est difficile à lire ?
* En quoi YARA est plus robuste qu’une regex simple ?
* Un attaquant pourrait-il contourner cette règle ?
* Peut-on utiliser YARA pour détecter des fuites de secrets ou du code pirate ?

## Bonus

* Générer un rapport JSON des résultats
* Scanner un dossier entier de fichiers PHP
* Créer une base de règles pour différents types de menaces
* Ajouter un second webshell et créer une règle pour lui
