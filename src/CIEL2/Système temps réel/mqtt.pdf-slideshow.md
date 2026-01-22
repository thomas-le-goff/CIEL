---
title: MQTT
version: 1.0.0
theme: default
footer: Thomas Le Goff - 2025 - CC BY-NC-SA
header: MQTT - Communication M2M - BTS CIEL
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
      "title title title" auto
      "left left   right" 1fr
      / 1fr 1fr;
    gap: 0 1rem;
    align-items: start;
  }

  section.gridify > h2 {
    grid-area: title;
  }

  section.gridify > pre:nth-of-type(1) {
    grid-area: left;
  }

  section.gridify > pre:nth-of-type(2) {
    grid-area: right;
  }
---

# MQTT - Communication M2M

_BTS CIEL_

![bg right:40%](./img/mqtt-cover.jpg)

--------------------------------------------------------------------------------
