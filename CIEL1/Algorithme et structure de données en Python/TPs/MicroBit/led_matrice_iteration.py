from microbit import *

i = 0

while True:
    x = i % 5
    y = (i//5) % 5

    if display.get_pixel(x, y) > 0:
        display.set_pixel(x, y, 0)
    else:
        display.set_pixel(x, y, 9)

    i = i + 1

    if i > 24:
        i = 0

    sleep(100)