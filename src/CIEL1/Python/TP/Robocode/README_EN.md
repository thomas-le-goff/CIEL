---
title: BTS CIEL1 - Getting Started with Robocode
author: Thomas Le Goff
header-includes:
  - '\usepackage{pmboxdraw}'
---

# Getting Started with Robocode

## Robocode

Robocode is a multiplayer programming game where the goal is to develop a robot (bot) that controls a tank and fights against other players.

Programming games are a great way to learn how to code while having fun. Here are a few well-known examples:

- Human Resource Machine
- The Farmer Was Replaced : <https://thefarmerwasreplaced.com/terms/>
- CodeCombat : <https://codecombat.com/>

### Useful Links

- Official Robocode website: <https://robocode.dev>
- Bot setup tutorial: <https://robocode.dev>
- Bot anatomy: <https://robocode.dev/articles/anatomy.html>
- Coordinates system: <https://robocode.dev/articles/coordinates-and-angles.html>
- Physics: <https://robocode.dev/articles/physics.html>
- Collision mechanics: <https://robocode.dev/articles/collision-mechanics.html>
- Scoring: <https://robocode.dev/articles/scoring.html>

## Step-by-step Introduction

Robocode consists of the following elements:

- the server, which handles matchmaking and communication with bots
- the bots, implemented as standalone scripts that communicate with the server via the WebSocket protocol

Robocode provides an SDK (Software Development Kit) in languages such as Python, C#, and Java to make bot development easier.

### Setting Up Your Bot

In this guide, we will use Python. To create your bot, follow these steps:

Create a folder that will contain your Python program. You can name it `FirstNameLastNameBot`. Put this folder into a `RoboCode` folder that will contain all your robocode bots. 

Here are the commands to create properly named folders:

```shell
cd ~/Documents
mkdir RoboCode && cd RoboCode
mkdir FirstNameLastNameBot && cd FirstNameLastNameBot
```

> It is essential that your files have the same name as the folder. Otherwise, the Robocode server will not detect your bot correctly, and it will not run.

Inside this folder, create a file named `FirstNameLastNameBot.json` (as the folder is named `FirstNameLastNameBot`) with the following content (remember to update the values):

```json
{
  "name": "My First Bot",
  "version": "1.0",
  "authors": [ "your name" ],
  "description": "My first bot",
  "homepage": "",
  "countryCodes": [ "fr" ],
  "platform": "Python",
  "programmingLang": "Python 3"
}
```

Next, create a file named `FirstNameLastNameBot.py` with the following content:

```python
from robocode_tank_royale.bot_api.bot import Bot
from robocode_tank_royale.bot_api.events import ScannedBotEvent, HitByBulletEvent


class MyBot(Bot):
    def run(self) -> None:
        """Called when a new round starts -> initialize and perform movement."""
        while self.running:
            self.forward(100)
            self.turn_gun_left(360)
            self.back(100)
            self.turn_gun_left(360)

    def on_scanned_bot(self, e: ScannedBotEvent) -> None:
        """We detected another bot -> fire!"""
        del e
        self.fire(1)

    def on_hit_by_bullet(self, e: HitByBulletEvent) -> None:
        """We were hit by a bullet -> turn perpendicular to it."""
        bearing = self.calc_bearing(e.bullet.direction)
        self.turn_right(90 - bearing)


def main() -> None:
    bot = MyBot()
    bot.start()


if __name__ == "__main__":
    main()
```

To install the Python SDK, you need to create a virtual environment using the `venv` module (in your project folder):

```shell
python3 -m venv .venv
source .venv/bin/activate
```

Once the virtual environment is activated, install the SDK with:

```shell
pip install robocode-tank-royale==0.37.0
```

Finally, create a file named `FirstNameLastNameBot.sh` containing the script used by the server to start your bot:

```shell
#!/bin/sh
set -e

cd -- "$(dirname -- "$0")"

if [ -x ".venv/bin/python" ]; then
    exec ".venv/bin/python" "FirstNameLastNameBot.py" # Make sure to update this line
else
    echo "Error: venv not found, please create and install dependencies in a Python venv" >&2
    exit 1
fi
```

Here is an example of a valid project structure:

```shell
.
└── FirstNameLastNameBot
    ├── FirstNameLastNameBot.json
    ├── FirstNameLastNameBot.py
    ├── FirstNameLastNameBot.sh
    └── .venv
```

--------------------------------------------------------------------------------

### Starting the Server

To start the server, look for the **robocode-tank-royale** application with the following icon:

![Robocode icon](img/robocode-logo.svg){ .center width=40% height=30% }

In the **Server** menu, click on **Start Local Server**. Once the server is running, you need to create a battle and select the bots that will fight.

In the **Battle** menu, click on **Start battle**. You should see the following window:

![Setup bot folder](img/setup_bot_folder.png){ .center width=80% height=50% }

A message will appear asking you to configure a bot directory. This directory allows the server to load different bot configurations and run them in battles (it is possible to create multiple bots from a single script).

You must configure the parent directory containing your bot. Example:

```
└── RoboCode
    └── FirstNameLastNameBot
        ├── FirstNameLastNameBot.json
        ├── FirstNameLastNameBot.py
        ├── FirstNameLastNameBot.sh
        └── .venv
```

The directory to set as **Bot root directory** is `RoboCode` (e.g. `~/Documents/RoboCode`), not `~/Documents/RoboCode/FirstNameLastNameBot`.

Once configured, you can select the bots that will fight:

1 - Start (boot) your bot by clicking on your bot script in the top left list "Bot Directories" and putting it to the right by clicking on `Boot ->` (you can boot multiple bot from the same script):

![Add bot boot](./img/boot_bot.png){ .center width=80% height=50% }

2 - Add your bots to the battle by clicking on your booted bot in the bottom left list "Joined Bots" and putting it to the right "Selected Bots" by clicking on `Add ->`:

![Add bot to match](./img/select_bots.png){ .center width=80% height=50% }

Once your bots are selected, start the battle by clicking **Start battle**.

> If you encounter issues while setting up the server or a battle, refer to: <https://robocode.dev/articles/gui.html>

## Activity Overview

### Create Your Bot (Team of 3)

In teams of three, you will develop a Python bot. Each member must work on a distinct part:

- one script dedicated to **gun control and shooting**
- one script dedicated to **movement and evasion**
- one script dedicated to **scanner management**

> Inspired by the following recommendations: <https://robocode.dev/tutorial/beyond-the-basics.html#strategy-types>

Each of you must work on **only one of the three parts**, then merge your scripts to create a complete bot. This bot will compete against other teams' bots in a final tournament (during the last session).

Even though you are working on separate parts, it is important to **define a common strategy** (**you must write this common strategy in a document and explain it to your teachers**) and **anticipate how your three programs will be integrated**.

To better understand bot development, you are encouraged to read the following pages:

- <https://robocode.dev/tutorial/getting-started.html>
- <https://robocode.dev/tutorial/beyond-the-basics.html>
- <https://robocode.dev/articles/anatomy.html>
- <https://robocode.dev/articles/coordinates-and-angles.html>
- <https://robocode.dev/articles/physics.html>
- <https://robocode.dev/articles/collision-mechanics.html>

### Fight Against Other Teams

At the end of the course, a tournament will take place where your bot will compete against those of the other teams. The game mode will be **"melee"**, with all bots fighting in the same match. The winning team will be the one with the highest score at the end of the match.

To fully understand match mechanics, you should read the following document: <https://robocode.dev/tutorial/getting-started.html#rounds-and-turns>

## Schedule

Session | Objective
------- | -----------------------------------------------------------------------------------------------------
24/03   | Introduction to the activity and Robocode (reading the documentation) + select your team members (1h)
27/03   | Start of script development (2h)
31/03   | Writing a document explaining your bot's strategy + oral presentation (~5 min) (1h)
03/04   | Script development (2h)
05/04   | Oral presentation of the strategy (~5 min) + final match (1h)
