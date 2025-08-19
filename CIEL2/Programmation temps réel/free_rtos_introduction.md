---
title: RTOS - Introduction à FreeRTOS - BTS CIEL
version: 1.0.0
theme: default
_class: invert
footer: Thomas Le Goff - 2025
header: RTOS - Introduction à FreeRTOS - BTS CIEL
paginate: true
marp: true
style: |
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

  .columns {
    display: flex;
    justify-content: space-around;
    align-items: center;
  }
---

# RTOS - Introduction à FreeRTOS

_BTS CIEL_

![bg right:33%](./img/free_rtos_cover.png)

---

## Sommaire

- Programmation et système temps réel
- FreeRTOS
- ESP32 et M5Stack
- Cybersécurité

![bg right:20%](./img/free_rtos_cover.png)

---

## Programmation et système temps réel

La programmation temps réel est un moyen de garantir le respect du temps d'exécution d'une tâche.

Ce type de programmation est nécessaire dans certains secteurs :

- l'industrie de production
- l'aéronautique
- l'automobile
- le médical

> Wikipédia : Les systèmes temps réel prennent en compte des contraintes temporelles dont le respect est aussi important que l'exactitude du résultat.

![bg right:20%](./img/rtos_industry.jpg)

---

## Programmation et système temps réel

### Concurrence VS Parallélisme

![width:800 center](./img/concurrent_vs_parallelism.jpg)

---

## Programmation et système temps réel

### Concurrence VS Parallélisme

- Concurrence : le CPU alterne les instructions de plusieurs tâches pour **simuler l'exécution de deux tâches en même temps**. Le CPU ne peut exécuter qu'une seule instruction à la fois.
- Parallélisme : pour que deux tâches s'exécutent réellement en parallèle il faut **au minimum deux CPUs** (cœur / thread).

> ℹ️ Le vrai parallélisme est utilisé (et nécessaire) uniquement pour des enjeux de performances (répartir la charge de travail).

![bg right:10%](./img/parallelism.webp)

---

## Programmation et système temps réel

Les "Real-Time Operating System" (RTOS) sont des OS spécialisés offrant un environnement simple et **déterministe**.

Ils intègrent **moins de fonctionnalités** (beaucoup moins !) que les OS généralistes (GPOS), mais, garentissent le respect des priorités des différentes tâches que doit réaliser le système.

> ℹ️ Un **système déterministe** est un système qui réagit toujours de la même façon à un événement

---
## Programmation et système temps réel

### Ordonnancement et préemption

La majorité des OS modernes ont un ordonnancement préemptif : L'ordonnanceur choisit la tâche / le processus qui est en cours d'exécution à un instant T.

La différence entre un RTOS et un GPOS se trouve au niveau du choix de la tâche :

- RTOS : une tâche peut être interrompue si une tâche **plus prioritaire** devient prête (la priorisation des tâches est à la main du programmeur)

- GPOS : tous les processus sont mis en concurrence via un ordonnanceur complexe qui garantit à la fois **équité et réactivité**

> ℹ️ Sur un GPOS il est très compliqué de prédire la tâche qui sera en cours d'exécution à un instant T.

---

## Programmation et système temps réel

Deux niveaux de temps réel :

- **le temps réel strict (hard)** : la contrainte de temps est associée à une situation critique voire catastrophique.

  - système de freinage d'urgence
  - surveillance de capteurs (avion, centrale nucléaire)

- **le temps réel souple (soft)** : la contrainte de temps est associée à de la pénibilité / mauvaise expérience pour l'utilisateur.
  - IHM (attention un bouton d'arrêt d'urgence correspond à la catégorie strict)
  - latence réseaux

![bg right:20%](./img/power_plant.jpg)

---

## Programmation et système temps réel

Concrètement :

1. On définit la liste des tâches que doit faire le système
2. On définit la priorité de chaque tâche
3. On partage le temps (time-slicing) que doit accorder l'OS à chaque tâche
4. On programme le système en utilisant un RTOS

---

## Programmation et système temps réel

### Quelques RTOS

[![](https://mermaid.ink/img/pako:eNp1VNtO20AQ_ZXRPlSplKS-5OL4LdCAkKBAHEqFIlWLPcQr7LVZr2kCQupH9AP6WL4jf9Iv6azjgEPbPKyy3jkzZ86Z3UcWZhEyn2mRYiIkziWAFjpBmM5OA3gHx0KWS9CY5gWo9TMm8Pv7D1CYr38pLCAWhc6UuCuxmEsDtkeeAz6cf_pSBeYKU2FC4R5VITIJrfOSS12mEGQ3-hunk2BVUP7ifQ0fdGgZUo7Py8tM3Rb_y3MpZARTQfsK6ViW06HFJeSBQqz4G2hItNfPkHNF0WHMVQR7XKlVDRoY0NBsqp8P-7G4FqfBh-ns35UbocFFMKkVmkiNKleiIOWQJzAjQcG2qhTXvCACRangbDqZnJzNvk5ndXXPVB-9afa1M1A8jFHX9I-oRrIB2hYBbbuh9E7kXsLD2z2kLqGFy8706KTWyO4ZXJ9wjSLTLLxFvaW6aZSsBpRFKTTC-idcYR6vVJ3DSGY3JducQi04lzKTYc0k4bVAB1kpI653BdwxapzyBzI24TLE7eYloDW-DIDmhCYmKmKRb_sxAtqj3X4q19fPUVM208Ts7HCDcsykOG6DyBs0D-9KUVToca7FfSPSuNsx1wUurksaZHCcrtWD41nwZlwOx8DvMfzLc8dY4BgLXk8qqJBk34KmFXgJMlvRupGuRdyJihYKIjSKDrq2QwKwNktRpVxEdIMfTfY50zGmOGc-_Y3whpeJnrO5fKJQXuosWMmQ-Tc8KbDNVFYu4pddmZM7-FHwheIp87Uq6WPO5VWWNbfMf2RL5ndcp9_16MpZ7nDoDUaW22Yr5jsDr-vafbdn9x27P-y5T232UCWwu647sEbeyBq5Q8_q29625CQS9IS88MBqe7J5lqrXqc0WyrS4pY0yQrVP46SZ71rW0x9vDJZk?type=png)](https://mermaid.live/edit#pako:eNp1VNtO20AQ_ZXRPlSplKS-5OL4LdCAkKBAHEqFIlWLPcQr7LVZr2kCQupH9AP6WL4jf9Iv6azjgEPbPKyy3jkzZ86Z3UcWZhEyn2mRYiIkziWAFjpBmM5OA3gHx0KWS9CY5gWo9TMm8Pv7D1CYr38pLCAWhc6UuCuxmEsDtkeeAz6cf_pSBeYKU2FC4R5VITIJrfOSS12mEGQ3-hunk2BVUP7ifQ0fdGgZUo7Py8tM3Rb_y3MpZARTQfsK6ViW06HFJeSBQqz4G2hItNfPkHNF0WHMVQR7XKlVDRoY0NBsqp8P-7G4FqfBh-ns35UbocFFMKkVmkiNKleiIOWQJzAjQcG2qhTXvCACRangbDqZnJzNvk5ndXXPVB-9afa1M1A8jFHX9I-oRrIB2hYBbbuh9E7kXsLD2z2kLqGFy8706KTWyO4ZXJ9wjSLTLLxFvaW6aZSsBpRFKTTC-idcYR6vVJ3DSGY3JducQi04lzKTYc0k4bVAB1kpI653BdwxapzyBzI24TLE7eYloDW-DIDmhCYmKmKRb_sxAtqj3X4q19fPUVM208Ts7HCDcsykOG6DyBs0D-9KUVToca7FfSPSuNsx1wUurksaZHCcrtWD41nwZlwOx8DvMfzLc8dY4BgLXk8qqJBk34KmFXgJMlvRupGuRdyJihYKIjSKDrq2QwKwNktRpVxEdIMfTfY50zGmOGc-_Y3whpeJnrO5fKJQXuosWMmQ-Tc8KbDNVFYu4pddmZM7-FHwheIp87Uq6WPO5VWWNbfMf2RL5ndcp9_16MpZ7nDoDUaW22Yr5jsDr-vafbdn9x27P-y5T232UCWwu647sEbeyBq5Q8_q29625CQS9IS88MBqe7J5lqrXqc0WyrS4pY0yQrVP46SZ71rW0x9vDJZk)

---

## Programmation et système temps réel

#### What about Windows ?

![center](./img/windows_rtos.png)

---

## FreeRTOS

FreeRTOS est un système d'exploitation temps réel open source distribué sous licence **MIT**.

Rachat par Amazon AWS en 2017 => "From Cloud to IoT"

> FreeRTOS : https://www.freertos.org/

> Amazon AWS : https://aws.amazon.com/fr/freertos/

![bg left:20%](./img/free_rtos_logo.jpg)

---

## FreeRTOS

Principales fonctionnalités :

- Ordonnancement préemptif ou coopératif
- Attribution de priorités aux tâches
- Files d’attente (queues)
- Sémaphores binaires et à compteurs
- Mode sans tick pour les applications à très basse consommation (sur certaines architectures)

> AWS ajoute d'autres fonctionnalités liées au cloud par le biais de bibliothèques optionnelles https://www.freertos.org/Documentation/03-Libraries/04-AWS-libraries/01-Introduction

![bg left:20%](./img/free_rtos_logo.jpg)

---

## FreeRTOS

- FreeRTOS se présente sous la forme de sources (fichiers) écrits en langage C.

- L'OS est entièrement téléversé sur la mémoire de la carte embarquée comme un programme "classique".

- FreeRTOS nécessite très peu de ressources pour fonctionner :

  - 25 MHz CPU
  - 64 KB RAM

![bg left:20%](./img/free_rtos_logo.jpg)

---

<style scoped>section{font-size:20px;}</style>

## ESP32 et M5Stack

**ESP32** est un microcontrôleur offrant des capacités inégalées pour son prix (< 3€) :

- Processeur
  - Dual-core Xtensa LX6 (jusqu’à 240 MHz)
  - Versions plus récentes avec RISC-V (ex. ESP32-C3, ESP32-C6)
- 520 KB SRAM interne
- Flash externe typiquement 4 MB (SPI NOR Flash)
- Wi-Fi 802.11 b/g/n
- Bluetooth 4.2 / BLE 5.0 (selon versions)
- GPIO (jusqu’à 34)
- ADC, DAC, PWM
- UART, SPI, I2C, I2S, CAN
- Capteurs capacitifs tactiles intégrés

Ses capacités permettent d'embarquer des fonctionnalités avancées ainsi que des OS spécialisés (comme FreeRTOS).

---

<style scoped>section{font-size:20px;}</style>

## ESP32 et M5Stack

Comparaison avec d'autres modèles :

| Puce                       | Points forts                                 | Limites / pourquoi moins populaire                     |
| -------------------------- | -------------------------------------------- | ------------------------------------------------------ |
| ESP32                      | Wi-Fi + BT intégrés, puissant, pas cher      | Consommation plus élevée qu’un STM32 ultra-low power   |
| STM32                      | Large gamme, très fiable, faible conso       | Pas de Wi-Fi/BT natif, prix plus élevé pour équivalent |
| Arduino (AVR)              | Simplicité, communauté historique            | Très limité en puissance et connectivité               |
| Raspberry Pi Pico (RP2040) | Très flexible, double core ARM M0+, pas cher | Pas de Wi-Fi/BT intégré (sauf version W)               |

> https://fr.wikipedia.org/wiki/ESP32

---

<style scoped>section{font-size:20px;}</style>

## ESP32 et M5Stack

M5Stack (Core 2) est un kit de développement basé sur la plateforme ESP32.

C'est un ESP32 avec des capteurs et actionneurs en plus.

| Caractéristique   | **ESP32**                             | **M5Stack Core2**                  |
| ----------------- | ------------------------------------- | ---------------------------------- |
| Nature            | Puce / SoC MCU                        | Kit tout-en-un basé sur ESP32      |
| Connectivité      | Wi-Fi + Bluetooth                     | Wi-Fi + Bluetooth                  |
| Mémoire           | \~520 KB SRAM interne                 | 16 MB Flash + 8 MB PSRAM           |
| Écran             | N/A                                   | LCD tactile 2.0"                   |
| Batterie intégrée | N/A                                   | 390 mAh                            |
| Capteurs intégrés | N/A                                   | Accéléro, RTC, micro, haut-parleur |
| Prix              | 3–5 €                                 | 40–50 €                            |
| Usage typique     | Intégration embarquée / produit final | Prototypage, démo, éducation, IoT  |

---

## ESP32 et M5Stack

Dans l'industrie, un M5Stack Core 2 serait envisagé en R&D pour passer sur une carte sur-mesure basée sur un ESP32 pour l'industrialisation.

<div class="columns">

<div>

![width:256](./img/m5stack.webp)

</div>

<div>

![width:256](./img/esp32.webp)

</div>

</div>

---

## Cybersécurité

ESP32 == Wifi et BLE == connectivité avec le monde extérieur == **sécurité**
