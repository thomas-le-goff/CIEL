---
title: C++ - IHM avec Qt - BTS CIEL
version: 1.0.0
theme: default
_class: invert
footer: Thomas Le Goff - 2026
header: C++ - IHM avec Qt - BTS CIEL
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

  section.gridify {
    display: grid;
    grid-template:
      "title title" auto
      "up-left up-right" 1fr
      "down-left down-right" 1fr
      / 1fr 1fr;
    gap: 0 1rem;
    align-items: start;
  }

  section.gridify > h2 {
    grid-area: title;
  }

  section.gridify > pre:nth-of-type(1) {
    grid-area: up-left;
  }

  section.gridify > pre:nth-of-type(2) {
    grid-area: up-right;
  }

  section.gridify > pre:nth-of-type(3) {
    grid-area: down-left;
  }

  section.gridify > pre:nth-of-type(4) {
    grid-area: down-right;
  }
---

# C++ - IHM avec Qt

_BTS CIEL_

![bg right:33%](./img/qt_cover.webp)

--------------------------------------------------------------------------------

## Présentation de Qt

Qt est un framework C++ cross-platform qui s'appuie fortement sur la programmation orienté objet.

- **Modules importants** :

  - **Qt Widgets** : Interfaces classiques (boutons, fenêtres, etc.).
  - **Qt Quick** : Interfaces modernes (QML/JavaScript).
  - **Qt Core** : Conteneurs, threads, fichiers, etc.
  - **Qt Network** : Réseau (TCP, HTTP, WebSocket).
  - **Qt SerialBus** : Communication CAN, Modbus.

--------------------------------------------------------------------------------

## Présentation de Qt

![center width:900px](./img/qt_actors.drawio.svg)

--------------------------------------------------------------------------------

## Présentation de Qt

![center](./img/qt_lvcim_rapas.png)

--------------------------------------------------------------------------------

## Présentation de Qt

![center width:800px](./img/qt_mercedes.png)

--------------------------------------------------------------------------------

## Cross-platform ?

![center](./img/qt_cross_platform.png)

--------------------------------------------------------------------------------

## Qt Widget VS Qt Quick

**Critère**           | **Qt Widgets**          | **Qt Quick**
--------------------- | ----------------------- | ------------------------------
**Langage**           | C++ (POO)               | QML / C++
**Style d'interface** | Classique (bureautique) | Moderne et fluide (animations)
**Rendu graphique**   | Logiciel (CPU)          | Accéléré (GPU)
**Cible embarquée**   | Économe en ressources   | Riche en fonctionnalités

--------------------------------------------------------------------------------

## Qt Widget VS Qt Quick

### Exemple de programme QML

```qml
import QtQuick

Rectangle {
    id: canvas
    width: 250
    height: 200
    color: "blue"

    Image {
        id: logo
        source: "pics/logo.png"
        anchors.centerIn: parent
        x: canvas.height / 5
    }
}
```

--------------------------------------------------------------------------------

## Qt Widget

![center width:700px](./img/qt_widget_explain.png)

--------------------------------------------------------------------------------

## Architecture Vue-Modèle

![center width:400px](./img/modelview-overview.png)

--------------------------------------------------------------------------------

## Architecture Vue-Modèle

### Modèle

Le modèle prend la forme d'une **instance de classe**.

Cette classe doit **hériter** de `QAbstractItemModel` ou de l'un de ses héritiers :

- `QAbstractListModel` pour les ensembles **unidimensionnels** (une liste)
- `QAbstractTableModel` pour les ensembles **multidimensionnels** (un tableau)

Qt offre des modèles plus avancés pour travailler avec des sources de données standards :

- `QStringListModel` pour stocker une liste de chaînes de charactères
- `QFileSystemModel` pour stocker des informations du système de stockage local (arborescence)
- `QSqlqueryModel` pour l'accès aux bases de données relationnelles (SQL)

--------------------------------------------------------------------------------

## Architecture Vue-Modèle

### Modèle

![center width:800px](./img/modelview-models.png)

--------------------------------------------------------------------------------

## Architecture Vue-Modèle

![center width:400px](./img/modelview-overview.png)

--------------------------------------------------------------------------------

## Architecture Vue-Modèle

### Vue

La vue prend la forme d'une **instance de classe**.

Cette classe doit hériter de `QAbstractItemView` ou de l'un de ses héritiers :

- `QListView` pour représenter les données sous forme de liste
- `QTableView` pour représenter les données sous forme de tableau
- `QTreeView` pour représenter les données sous forme d'arbre

--------------------------------------------------------------------------------

## Architecture Vue-Modèle

### Vue

![center width:1000px](./img/qt_view.png)

--------------------------------------------------------------------------------

## Architecture Vue-Modèle

![center width:400px](./img/modelview-overview.png)

--------------------------------------------------------------------------------

## Architecture Vue-Modèle

### Délégué (delegate)

Le délégué prend la forme d'une **instance de classe**.

Cette classe doit hériter de `QAbstractItemDelegate`.

La classe généralement utilisée est `QStyledItemDelegate`.

--------------------------------------------------------------------------------

<style scoped="">section{font-size:20px;}</style>

## Architecture Vue-Modèle

### Exemple complet

```c++
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSplitter *splitter = new QSplitter;

    // Model
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    // View
    QTreeView *tree = new QTreeView(splitter);
    tree->setModel(model);
    tree->setRootIndex(model->index(QDir::currentPath()));

    QListView *list = new QListView(splitter);
    list->setModel(model);
    list->setRootIndex(model->index(QDir::currentPath()));

    splitter->setWindowTitle("Two views onto the same file system model");
    splitter->show();
    return app.exec();
}
```

--------------------------------------------------------------------------------

## Architecture Vue-Modèle

### Exemple complet

![center](./img/qt_mv_sample.png)

--------------------------------------------------------------------------------

## Architecture Vue-Modèle

### Signals et slots (programmation événementielle)

![center width:800px](./img/modelview-slots.png)

--------------------------------------------------------------------------------

## Architecture Vue-Modèle

### Signals et slots

```c++
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton bouton("Quitter");

    QObject::connect(&bouton, &QPushButton::clicked, &app, &QApplication::quit);

    bouton.show();

    return app.exec();
}
```

--------------------------------------------------------------------------------

## Architecture Vue-Modèle

### Signals et slots

```c++
#include <QApplication>
#include <QPushButton>
#include <iostream>

void onClick()
{
    std::cout << "Bouton cliqué !" << std::endl;
}

int main(int argc, char *argv[])
{
    // ...
    QObject::connect(&bouton, &QPushButton::clicked, &onClick);
    // ...
}
```

--------------------------------------------------------------------------------

## Architecture Vue-Modèle

### Signals et slots

- Les signaux émis par **le modèle** informent la vue **des modifications** apportées aux données détenues par la source de données.
- Les signaux émis par **la vue** fournissent des informations sur **les interactions** de l'utilisateur avec les éléments affichés.
- Les signaux émis par **le délégué** sont utilisés pendant l'édition pour informer le modèle et la vue de **l'état de l'éditeur**.

--------------------------------------------------------------------------------

## Architecture Vue-Modèle

### Notion de widget

![center](./img/qt_widget_widget.webp)

--------------------------------------------------------------------------------

<style scoped="">section{font-size:20px;}</style>

## Gestion de la mémoire dans Qt

Il n'y a pas un problème ?

```c++
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSplitter *splitter = new QSplitter;

    // Model
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    // View
    QTreeView *tree = new QTreeView(splitter);
    tree->setModel(model);
    tree->setRootIndex(model->index(QDir::currentPath()));

    QListView *list = new QListView(splitter);
    list->setModel(model);
    list->setRootIndex(model->index(QDir::currentPath()));

    splitter->setWindowTitle("Two views onto the same file system model");
    splitter->show();
    return app.exec();
}
```

--------------------------------------------------------------------------------

## Les outils

### Qt Creator

![center width:850px](./img/qt_design_studio.webp)

--------------------------------------------------------------------------------

## Les licences Qt

![center](./img/qt_licensing.png)
