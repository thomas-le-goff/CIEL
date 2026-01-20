from microbit import *
from random import *

MAX_ACC = 1024
MIN_ACC = -1024
RANGE_ACC = MAX_ACC - MIN_ACC

WIDTH = 5
HEIGHT = 5
SENSITIVITY = 100

def get_x_movement() -> int:
    x = accelerometer.get_x()
    return int(((x - MIN_ACC) / RANGE_ACC) * WIDTH)


def get_y_movement() -> int:
    y = accelerometer.get_y()
    return int(((y - MIN_ACC) / RANGE_ACC) * HEIGHT)


score = 0

ball_x = WIDTH // 2
ball_y = HEIGHT // 2

hole_x = randrange(WIDTH)
hole_y = randrange(HEIGHT)

n_ball_x = ball_x
n_ball_y = ball_y

while True:
    if n_ball_x != ball_x or n_ball_y != ball_y:
        display.set_pixel(ball_x, ball_y, 0)

    ball_x = n_ball_x
    ball_y = n_ball_y

    display.set_pixel(ball_x, ball_y, 4)


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

