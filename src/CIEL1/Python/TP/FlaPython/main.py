import pygame, os, random
from enum import Enum
from collections import deque

class GameSate(Enum):
    WAITING = 1
    PLAYING = 2
    LOSING = 3

PATH = os.path.abspath('.')+'/'

WIDTH = 720
HEIGHT = 1280
SCALE = 8

INITIAL_PIPE_POSITION = pygame.math.Vector2(WIDTH, HEIGHT/2)
PIPE_RANGE = 500

GRAVITY = 2000
FLAP_STRENGTH =1000
MAX_FALL_SPEED =750

### Initialization
def load_image(file_name, scale=1):
    image = pygame.image.load(PATH + file_name).convert_alpha()
    return pygame.transform.scale(image, (image.get_width() * scale, image.get_height() * scale))

def initialize():
    font_renderer = pygame.font.SysFont('Comic Sans MS', 128)

    pipe_rect = pygame.Rect((0, 0), (32*SCALE, PIPE_RANGE))
    pipe_rect.midleft = INITIAL_PIPE_POSITION + pygame.math.Vector2(0, random.randint(-HEIGHT/4, HEIGHT/4))

    player_rect = pygame.Rect((0, 0), (16*SCALE, 16*SCALE))
    player_rect.center = pygame.math.Vector2(16*SCALE, HEIGHT/2)

    state = dict(
        current_scene = GameSate.WAITING,
        pipe = dict(
            rect=pipe_rect,
            speed=400,
            sprite=load_image("pipe.png", scale=SCALE),
            gone=False
        ),
        player = dict(
            rect=player_rect,
            score = 0,
            velocity=pygame.math.Vector2(0, 0),
            acc_y=0,
            clip=pygame.Rect((0, 0), player_rect.size),
            alive=True,
            animation=dict(
                animation_speed=2,
                default_animation=0,
                animations_deque=deque(),
                current_frame=0,
                sprite_sheet=load_image("player_sprite_sheet.png", scale=SCALE),
                last_tick=pygame.time.get_ticks(),
                clips=[
                    [pygame.Rect((0, 0), player_rect.size)],
                    [pygame.Rect((0, 0), player_rect.size), pygame.Rect((16*SCALE, 0), player_rect.size)]
                ]
            )
        ),
        background=[shadowed_surface(load_image(f"background_{i}.png", SCALE)) for i in range(2)],
        menu_text = font_renderer.render('Tap to play', False, "white"),
        font_renderer = font_renderer
    )

    return state

def shadowed_surface(surface, intensity=128):
    shadow = pygame.Surface(surface.get_size(), flags=pygame.SRCALPHA)
    shadow.fill((0, 0, 0, intensity))
    surface.blit(shadow, (0, 0))
    return surface

def set_next_animation(animation, index, force=False):
    if force:
        animation["animations_deque"].appendleft(index)
    else:
        animation["animations_deque"].append(index)

def get_current_animation_clips(animation):
    animations_deque = animation["animations_deque"]
    default_animation_clips = animation["clips"][animation["default_animation"]]
    if len(animations_deque) > 0:
        return animation["clips"][animations_deque[0]]

    return default_animation_clips

def update_animation(animation, dt):
    now = pygame.time.get_ticks()
    frame_duration = 2 #2sec
    clips = get_current_animation_clips(animation)

    if now - (frame_duration * 50) > animation["last_tick"]:
        animation["last_tick"] = now
        next_frame = (animation["current_frame"] + 1) % len(clips)
        
        # Animation is done
        if next_frame == 0 and len(animation["animations_deque"]) > 0:
            animation["animations_deque"].popleft()

        animation["current_frame"] = next_frame

def draw_animation(screen, pos, animation):
    clips = get_current_animation_clips(animation)
    current_clip = clips[animation["current_frame"]]
    sprite_sheet = animation["sprite_sheet"]

    screen.blit(sprite_sheet, pos, area=current_clip)

### Entities
def update_pipe(pipe, dt):
    pipe["rect"].x -= pipe["speed"] * dt

    if pipe["rect"].x + (32*SCALE) < 0:
        pipe["rect"].midleft = INITIAL_PIPE_POSITION + pygame.math.Vector2(0, random.randint(-HEIGHT/4, HEIGHT/4))
        pipe["gone"] = False
    
def draw_pipe(screen, pipe):
    empty_rect = pipe["rect"]
    top_pipe_rect = pygame.Rect((0, 0), (empty_rect.width, 128*SCALE))
    bottom_pipe_rect = pygame.Rect(empty_rect.topleft, (empty_rect.width, 128*SCALE))

    top_pipe_rect.bottomleft = empty_rect.topleft
    bottom_pipe_rect.topleft = empty_rect.bottomleft

    screen.blit(pygame.transform.flip(pipe["sprite"], False, True), top_pipe_rect)
    screen.blit(pipe["sprite"], bottom_pipe_rect)

def update_player(player, keys, dt):
    player["velocity"].y += GRAVITY * dt
    player["velocity"].y = min(player["velocity"].y, MAX_FALL_SPEED)
    
    if keys.get(pygame.K_SPACE) == pygame.KEYDOWN or keys.get(pygame.BUTTON_LEFT) == pygame.MOUSEBUTTONDOWN:
        player["velocity"].y = -FLAP_STRENGTH
        set_next_animation(player["animation"], 1, True)

    player["rect"].topleft = player["rect"].topleft + (player["velocity"] * dt)
    
    update_animation(player["animation"], dt)

def draw_player(screen, player):
    draw_animation(screen, player["rect"].topleft ,player["animation"])

def update_score(player, pipe, dt):
    if pipe["gone"] == True:
        return

    if pipe["rect"].x < player["rect"].x:
        pipe["gone"] = True
        player["score"] += 1 

def draw_score(screen, font_renderer, score):
    score_text = font_renderer.render(str(score), False, "white")
    screen.blit(score_text, (WIDTH / 2 - (score_text.get_width() / 2), score_text.get_height()))

def draw_background(screen, background, dt):
    for i in range(0, len(background)):
        screen.blit(background[i], (0, 0))

def handle_collision(player, pipe, dt):
    # TODO: mutualize with draw_pipe (or store it in state)
    empty_rect = pipe["rect"]
    top_pipe_rect = pygame.Rect((0, 0), (empty_rect.width, 128*SCALE))
    bottom_pipe_rect = pygame.Rect(empty_rect.topleft, (empty_rect.width, 128*SCALE))

    top_pipe_rect.bottomleft = empty_rect.topleft
    bottom_pipe_rect.topleft = empty_rect.bottomleft

    if player["rect"].collidelist([top_pipe_rect, bottom_pipe_rect]) != -1:
        player["alive"] = False

def handle_fall(player, dt):
    if player["rect"].y > HEIGHT:
        player["alive"] = False

### Scenes
def play_menu(screen, state, keys, dt):
    state["current_scene"] = GameSate.WAITING
    mt = state["menu_text"]

    # Update
    if keys.get(pygame.K_SPACE) == pygame.KEYDOWN or keys.get(pygame.BUTTON_LEFT) == pygame.MOUSEBUTTONDOWN:
        # Kind of reset (TODO: better way of doing this)
        state["current_scene"] = GameSate.PLAYING
        state["player"]["alive"] = True
        state["player"]["score"] = 0
        state["player"]["rect"].center = pygame.math.Vector2(16*SCALE, HEIGHT/2)
        state["pipe"]["rect"].midleft = INITIAL_PIPE_POSITION + pygame.math.Vector2(0, random.randint(-PIPE_RANGE, PIPE_RANGE))
        state["pipe"]["gone"] = False

    # Draw
    screen.blit(mt, (WIDTH / 2 - (mt.get_width() / 2), HEIGHT / 2 - (mt.get_height() / 2)))

    return state

def play_game(screen, state, keys, dt):
    state["current_scene"] = GameSate.PLAYING

    # Update
    background = state["background"]
    player = state["player"]
    pipe = state["pipe"]

    update_pipe(pipe, dt)
    update_player(player, keys, dt)
    update_score(player, pipe, dt)
    
    handle_collision(player, pipe, dt)
    handle_fall(player, dt)

    # Draw
    draw_background(screen, background, dt)
    draw_player(screen, player)
    draw_pipe(screen, pipe)
    draw_score(screen, state["font_renderer"], player["score"])

    if player["alive"] == False:
        state["current_scene"] = GameSate.WAITING

    return state

def play_losing(screen, state, keys, dt):
    return state

def main():

    pygame.init()

    screen = pygame.display.set_mode((WIDTH, HEIGHT), flags= pygame.SCALED | pygame.FULLSCREEN)
    # screen = pygame.display.set_mode((WIDTH, HEIGHT), flags=pygame.SCALED)
    clock = pygame.time.Clock()
    running = True
    dt = 0

    state = initialize()

    while running:
        keys = dict()
        for event in pygame.event.get():
            if event.type == pygame.QUIT: 
                running = False
            elif event.type == pygame.KEYDOWN or event.type == pygame.KEYUP:
                keys[event.key] = event.type
            elif event.type == pygame.MOUSEBUTTONDOWN or event.type == pygame.MOUSEBUTTONUP:
                keys[event.button] = event.type

        screen.fill("black")

        match state["current_scene"]:
            case GameSate.WAITING:
                state = play_menu(screen, state, keys, dt)
            case GameSate.PLAYING:
                state = play_game(screen, state, keys, dt)
            case GameSate.LOSING:
                state = play_losing(screen, state, keys, dt)

        pygame.display.flip()
        dt = clock.tick(60) / 1000

    pygame.quit()

if __name__ == "__main__":
    print(pygame.version.ver)
    main()