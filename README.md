# BTS CIEL Courses

This Github repository contains all the sources for the courses, TDs and TPs I teach in BTS CIEL.

These courses are development-oriented and focus on Cyber-Security and good development practices (trusted computing).

## Get Started

The courses are mainly in slideshow format and are written using markdown and the MARP framework. (Course as code 😉)

```shell
npx @marp-team/marp-cli@latest slide-deck.md -w
```

## Automatic correction of language errors

A Python script and Github Actions workflows automatically correct spelling mistakes (often typing errors 🙄).

To trigger the correction, simply position the `spell-check` tag on the revision you want to start from, and the system will submit a PR containing the necessary corrections associated with the changes between the `spell-check` tag and the `last-spell-check` tag (which will then be positioned on `spell-check`).

Tags definitions:

- `last-spell-check` last revision processed by the correction system
- `spell-check` revision from which errors were processed