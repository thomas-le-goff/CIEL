from microbit import *

while True:
    if button_a.is_pressed() and not audio.is_playing():
        audio.play(Sound.HELLO)        