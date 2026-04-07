## Vérifier et réinstaller son environnement

### A - Vérifier l'environnement virtuel Python

Dans votre dossier contenant votre bot **RoboCode**, vérifiez si votre environnement virtuel est déjà créé :

```bash
ls -a
```

Si un dossier nommé `.venv` est présent, votre environnement virtuel est déjà créé. Vous pouvez alors **passer directement à l'étape C**.
Sinon, **passez à l'étape B**.

### B - Créer l'environnement virtuel

Pour créer un environnement virtuel, utilisez la commande suivante :

```bash
python3 -m venv .venv
```

### C - Activer l'environnement virtuel

Pour activer l'environnement, utilisez la commande suivante :

```bash
source .venv/bin/activate
```

### D - Installer RoboCode

Si vous venez de créer votre environnement, il est nécessaire d'y installer la bibliothèque RoboCode (pensez à activer l'environnement via l'étape C) :

```bash
pip install robocode-tank-royale==0.37.0
```