---
title: Python - Exercices sur la gestion des fichiers et des exceptions 
version: 1.0.0
theme: default
header: Python - Exercices sur la gestion des fichiers et des exceptions
paginate: true
marp: true
style: |-
  section {
    font-size: 1.6em;
  }

  img[alt~="center"] {
    display: block;
    margin: 0 auto;
  }

  section.lead h1 {
    text-align: center;
  }

  section.gridify {
    display: grid;
    grid-template:
      "title title" auto
      "instructions instructions" auto
      "left right" 1fr
      / 1fr 1fr;
    gap: 0 1rem;
  }

  section.gridify > h2 {
    grid-area: title;
  }

  section.gridify > p {
    grid-area: instructions
  }

  section.gridify > pre:nth-of-type(1) {
    grid-area: left;
  }

  section.gridify > pre:nth-of-type(2) {
    grid-area: right;
  }
---

# Python - Exercices sur la gestion des fichiers et les exceptions

_BTS CIEL_

--------------------------------------------------------------------------------

<!-- _class: gridify -->

## Exercice 1

Adaptez le code suivant pour obtenir la sortie attendue.

```python
import json

config = {}
default_config_filename = "default_config.json"
config_filename = "config.json"
with open(config_filename) as file:
    config = json.load(file)

print("Configuration : ")
for k, v in config:
    print(f"clé : {k}, valeur : {v}")
```
    
```python

```

```python
Sortie actuelle :

Traceback (most recent call last):
  File "/tmp/missing_file.py", line 6, in <module>
    with open(config_filename) as file:
         ~~~~^^^^^^^^^^^^^^^^^
FileNotFoundError: [Errno 2] No such file or directory: 'config.json'
```

```
Sortie attendue :

Aucun fichier de configuration trouvé. Utilisation de la configuration par défaut.
Configuration :
clé : port, valeur : 22
clé : user, valeur : root
clé : hostname, valeur : localhost

```

--------------------------------------------------------------------------------

<!-- _class: gridify -->

## Exercice 2

Adaptez le code suivant pour obtenir la sortie attendue.

```python
import json

config = {}
default_config_filename = "default_config.json"
config_filename = "config.json"
with open(config_filename) as file:
    config = json.load(file)

print("Configuration : ")
for k, v in config:
    print(f"clé : {k}, valeur : {v}")
```
    
```python

```

```python
Traceback (most recent call last):
  File "/tmp/missing_file.py", line 7, in <module>
    config = json.load(file)
  File "/usr/lib/python3.13/json/__init__.py", line 293, in load
    return loads(fp.read(),
        cls=cls, object_hook=object_hook,
        parse_float=parse_float, parse_int=parse_int,
        parse_constant=parse_constant, object_pairs_hook=object_pairs_hook, **kw)
  File "/usr/lib/python3.13/json/__init__.py", line 346, in loads
    return _default_decoder.decode(s)
           ~~~~~~~~~~~~~~~~~~~~~~~^^^
  File "/usr/lib/python3.13/json/decoder.py", line 345, in decode
    obj, end = self.raw_decode(s, idx=_w(s, 0).end())
               ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^
  File "/usr/lib/python3.13/json/decoder.py", line 363, in raw_decode
    raise JSONDecodeError("Expecting value", s, err.value) from None
json.decoder.JSONDecodeError: Expecting value: line 1 column 1 (char 0)
```

```
Sortie attendue :

Fichier de configuration invalide. Utilisation de la configuration par défaut.
Configuration :
clé : port, valeur : 22
clé : user, valeur : root
clé : hostname, valeur : localhost

```
--------------------------------------------------------------------------------

<!-- _class: gridify -->

## Exercice 3

Adaptez le code suivant pour obtenir la sortie attendue.

```python
import json

config = {}
default_config_filename = "default_config.json"
config_filename = "config.json"
with open(config_filename) as file:
    config = json.load(file)

print("Configuration : ")
for k, v in config:
    print(f"clé : {k}, valeur : {v}")
```
    
```python

```

```python
Traceback (most recent call last):
  File "/tmp/missing_file.py", line 6, in <module>
    with open(config_filename) as file:
         ~~~~^^^^^^^^^^^^^^^^^
PermissionError: [Errno 13] Permission denied: 'config.json'
```

```
Sortie attendue :

Impossible d'utiliser le fichier de configuration. Utilisation de la configuration par défaut.
Configuration :
clé : port, valeur : 22
clé : user, valeur : root
clé : hostname, valeur : localhost

```

--------------------------------------------------------------------------------

<!-- _class: gridify -->

## Exercice 4

Adaptez le code suivant pour obtenir la sortie attendue.

```python
import urllib.request
import json

sentence_api_url = "https://sentence.underthekey.com/language?language=eng&count=1"

def json_http_request(url):
    return json.load(urllib.request.urlopen(sentence_api_url))

with open("sentences.txt") as file:
    for i in range(10):
        response = json_http_request(sentence_api_url)
        sentence = response[0]["content"]
        file.write(sentence.strip() + '\n')
        print(sentence)
```
    
```python

```

```python
Traceback (most recent call last):
  File "/tmp/missing_file.py", line 13, in <module>
    file.write(sentence.strip() + '\n')
    ~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^
io.UnsupportedOperation: not writable
```

```
Sortie attendue :

Build something out of LEGO.
Everybody makes mistakes.
You never really grow up.
If it ain't broke don't fix it.
If you are feeling down, try holding a pencil between your top lip and your nose for five minutes.
Don't eat anything your grandparents wouldn't recognize as food.
Never regret. If it's good, it's wonderful. If it's bad, it's experience.
The person who never made a mistake never made anything.
Learn from your mistakes.
Don't cross the streams.
```

--------------------------------------------------------------------------------

<!-- _class: gridify -->

## Exercice 5

Adaptez le code suivant pour obtenir la sortie attendue.

```python
import urllib.request
import json

sentence_api_url = "https://sentence.underthekey.com/language?language=eng&count=1"

def json_http_request(url):
    return json.load(urllib.request.urlopen(sentence_api_url))

with open("sentences.txt", "w") as file:
    for i in range(10):
        response = json_http_request(sentence_api_url)
        sentence = response[0]["content"]
        file.write(sentence.strip() + '\n')
        print(sentence)
```
    
```python

```

```txt
Build something out of LEGO.
Everybody makes mistakes.
Traceback (most recent call last):
  File "/tmp/missing_file.py", line 11, in <module>
    response = json_http_request(sentence_api_url)
  File "/tmp/missing_file.py", line 7, in json_http_request
    return json.load(urllib.request.urlopen(sentence_api_url))
                     ~~~~~~~~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^
    ...
  File "/usr/lib/python3.13/urllib/request.py", line 466, in _call_chain
    result = func(*args)
  File "/usr/lib/python3.13/urllib/request.py", line 613, in http_error_default
    raise HTTPError(req.full_url, code, msg, hdrs, fp)
urllib.error.HTTPError: HTTP Error 429: 
```

```
Sortie attendue :

Build something out of LEGO.
Everybody makes mistakes.
API indisponible, arrêt du programme.
```