from microbit import *
from random import *

MAX_ACC = 1024
MIN_ACC = -1024
RANGE_ACC = MAX_ACC - MIN_ACC

WIDTH = 5
HEIGHT = 5
SENSITIVITY = 100

# Q1: Pour ces valeurs donnez le résultat des fonctions suivantes. En déduire des usage possible sur Microbit
def get_x_movement() -> int:
    x = accelerometer.get_x()
    return int(((x - MIN_ACC) / RANGE_ACC) * WIDTH)


def get_y_movement() -> int:
    y = accelerometer.get_y()
    return int(((y - MIN_ACC) / RANGE_ACC) * HEIGHT)


# Q2: pensez-vous qu'une méthode plus adaptée existe ?

# Q3: Est-elle réellement plus adaptée ? Pourquoi ?

score = 0

ball_x = WIDTH // 2
ball_y = HEIGHT // 2

hole_x = randrange(WIDTH)
hole_y = randrange(HEIGHT)

n_ball_x = ball_x
n_ball_y = ball_y

# Q4: utilisé les fonctions de Microbit pour afficher une balle au position ball_x et ball_y de la matrice de LED de la carte.
while True:
    if n_ball_x != ball_x or n_ball_y != ball_y:
        display.set_pixel(ball_x, ball_y, 0)

    ball_x = n_ball_x
    ball_y = n_ball_y

    display.set_pixel(ball_x, ball_y, 4)

    # Q5: en utilisant les fonctions vu précedemment (get_x et get_y) faite en sorte d'afficher la balle au nouvelle position (en ayant uniquement une LED allumée)

    n_ball_x = max(0, min(WIDTH - 1, get_x_movement()))
    n_ball_y = max(0, min(WIDTH - 1, get_y_movement()))

    if ball_x == hole_x and ball_y == hole_y:
        display.set_pixel(hole_x, hole_y, 0)
        hole_x = randrange(WIDTH)
        hole_y = randrange(HEIGHT)
        score += 1
        audio.play(Sound.GIGGLE)
    else:
        display.set_pixel(hole_x, hole_y, 9)

    if button_a.is_pressed():
        display.scroll(score, wait=True, loop=False)

# Q6 (Bonus?) en utilisant les mêmes principes afficher un trou sur lequel le joueur doit aller pour marquer des points (déplacer le trou et incrémenté un score lorsque le joueur touche le trou).
# (hint: lien vers random.randrange)

# Q7 Comptabilisé le score du joeur (1 pt par trou touché) et afficher sa valeur lorsque le bouton A est pressé

# Q8 soyez auto-critique concernant votre programme: proposez des amélioration (modularité etc.)

# Pour les courageux https://microbit-micropython.readthedocs.io/en/latest/accelerometer.html
