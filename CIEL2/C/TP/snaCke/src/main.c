/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include <stdlib.h>
#include <math.h>

#include "raylib.h"
#include "raymath.h"

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720

#define SNAKE_CHUNK_SIZE 50

#define SNAKE_SPEED SNAKE_CHUNK_SIZE

#define APPLE_SIZE 25
#define APPLE_STEM_WIDTH 4
#define APPLE_STEM_HEIGHT 8

#define STEP_PER_SECOND 4.0f
#define STEP_INTERVAL (1.0f / STEP_PER_SECOND)

#define PINK (Color){255, 100, 150, 255}

typedef enum
{
	Up,	   // 0
	Down,  // 1
	Right, // 2
	Left   // 3
} Direction;

typedef struct SnakeChunk_s
{
	Vector2 position;
	struct SnakeChunk_s *next;
} SnakeChunk;

typedef struct GameState
{
	SnakeChunk snake_head;
	Vector2 apple_position;
	Direction snake_direction;
	float accumulator;
} GameState;

// Exo : inspecter l'usage de la mémoire par le programme (Valgring, configuration GCC, Debugger de Visual Studio Code)

// Exo : coder cette méthode.
bool check_square_collision(Vector2 a, Vector2 b, int a_size, int b_size)
{
	return a.x <= b.x + b_size && a.x + a_size >= b.x && a.y <= b.y + b_size && a.y + a_size >= b.y;
}

Vector2 move_apple(Vector2 position)
{
	// Exo : adapter les valeurs pour rendre le jeu plus juste => mettre un écart de taille SNAKE_SIZE entre le mure et la pomme.
	position.x = GetRandomValue(SNAKE_CHUNK_SIZE, WINDOW_WIDTH - SNAKE_CHUNK_SIZE),
	position.y = GetRandomValue(SNAKE_CHUNK_SIZE, WINDOW_HEIGHT - SNAKE_CHUNK_SIZE);

	return position;
}

void move_snake(SnakeChunk *head, Vector2 new_position)
{
	// Exo : version recursive (plus simple mais attention au limite)

	// Recursive version
	// if (head) {
	// 	move_snake(head->next, head->position);
	// 	head->position = new_position;
	// }

	Vector2 last_position = new_position;
	SnakeChunk *current = head;

	// Exo: qu'est-ce que la NASA n'aime pas dans ce code ?

	while (current)
	{
		Vector2 current_position = current->position;

		current->position = last_position;
		last_position = current_position;
		current = current->next;
	}
}

void grow_snake(SnakeChunk *head)
{
	SnakeChunk *next = (SnakeChunk *)malloc(sizeof(SnakeChunk));

	// Exo: doit-on réellement rechercher la queue ? Est-ce qu'il n'y a pas une solution moins couteuse ?
	// SnakeChunk *tail = head;
	// while (tail->next)
	// {
	// 	tail = tail->next;
	// }

	// Exo: découverte et utilisation de l'allocateur mémoire proposé par Raylib.

	// next->position = head->position;
	// next->next = NULL; // Exo : en quoi cette ligne est-elle nécessaire ? Que ce passe-t-il si ->next n'est pas initialisé à NULL ?

	// tail->next = next;

	// Alternative : insertion en tête
	next->position = head->position;
	next->next = head->next;

	head->next = next;
}

GameState update(GameState state)
{
	// Exo : comment améliorer ce code ? => ne pas utiliser un enum mais directement un vecteur pour exprimer la direction du serpent.
	// Move the snake

	if (IsKeyDown(KEY_UP) && state.snake_direction > Down)
	{
		state.snake_direction = Up;
	}
	else if (IsKeyDown(KEY_DOWN) && state.snake_direction > Down)
	{
		state.snake_direction = Down;
	}

	if (IsKeyDown(KEY_RIGHT) && state.snake_direction <= Down)
	{
		state.snake_direction = Right;
	}
	else if (IsKeyDown(KEY_LEFT) && state.snake_direction <= Down)
	{
		state.snake_direction = Left;
	}

	float dt = GetFrameTime();
	state.accumulator += dt;
	while (state.accumulator >= STEP_INTERVAL)
	{
		state.accumulator -= STEP_INTERVAL;

		Vector2 new_position = state.snake_head.position;

		switch (state.snake_direction)
		{
		case Up:
			new_position.y -= SNAKE_SPEED;
			break;
		case Down:
			new_position.y += SNAKE_SPEED;
			break;
		case Right:
			new_position.x += SNAKE_SPEED;
			break;
		case Left:
			new_position.x -= SNAKE_SPEED;
			break;

		default:
			break;
		}

		move_snake(&state.snake_head, new_position);

		// Does the snake eats the apple ?
		if (check_square_collision(state.snake_head.position, state.apple_position, SNAKE_CHUNK_SIZE, APPLE_SIZE))
		{
			state.apple_position = move_apple(state.apple_position);
			grow_snake(&state.snake_head);
		}
	}

	return state;
}

void DrawRectangleWithBorder(int x, int y, int width, int height, Color fill, Color border, float borderThickness)
{
	DrawRectangle(x, y, width, height, border);
	DrawRectangle(x + borderThickness, y + borderThickness, width - borderThickness * 2, height - borderThickness * 2, fill);
}

void DrawRectangleWithMargin(int x, int y, int width, int height, Color fill, float marginThickness)
{
	DrawRectangle(x + marginThickness, y + marginThickness, width - marginThickness * 2, height - marginThickness * 2, fill);
}

void draw_eye(int x, int y, int eyeSize, int pupilSize)
{
	DrawRectangle(x, y, eyeSize, eyeSize, WHITE);

	DrawRectangle(
		x + (eyeSize - pupilSize) / 2,
		y + (eyeSize - pupilSize) / 2,
		pupilSize,
		pupilSize,
		BLACK);
}

void draw_tongue(int head_x, int head_y, int head_size, int length)
{
	int tongueWidth = head_size / 6;
	int tongueX = head_x + head_size / 2 - tongueWidth / 2;
	int tongueY = head_y + head_size - length / 4;

	DrawRectangle(tongueX, tongueY, tongueWidth, length, PINK);

	int branchLength = length * 2;
	int branchWidth = tongueWidth / 2;

	Vector2 origin = {branchWidth / 2.0f, 0};

	DrawRectanglePro(
		(Rectangle){tongueX, tongueY, branchWidth, branchLength},
		origin,
		-30,
		PINK);

	DrawRectanglePro(
		(Rectangle){tongueX + tongueWidth, tongueY, branchWidth, branchLength},
		origin,
		30,
		PINK);
}

void draw_snake(SnakeChunk *head)
{
	if (!head)
		return;

	SnakeChunk *chunk = head;
	int i = 0;
	while (chunk)
	{
		// Head
		if (chunk != head)
		{
			DrawRectangleWithMargin(chunk->position.x, chunk->position.y, SNAKE_CHUNK_SIZE, SNAKE_CHUNK_SIZE, DARKGREEN, Clamp(i, 1, 16));
		}

		chunk = chunk->next;
		i++;
	}

	// Draw head on top
	draw_tongue(head->position.x, head->position.y, SNAKE_CHUNK_SIZE, 8);

	DrawRectangleWithBorder(head->position.x, head->position.y, SNAKE_CHUNK_SIZE, SNAKE_CHUNK_SIZE, GREEN, DARKGREEN, 4);

	int eyeSize = SNAKE_CHUNK_SIZE / 4;
	int pupilSize = eyeSize / 2;
	int eyeOffsetX = SNAKE_CHUNK_SIZE / 5;
	int eyeOffsetY = SNAKE_CHUNK_SIZE / 5;

	draw_eye(head->position.x + eyeOffsetX, head->position.y + eyeOffsetY, eyeSize, pupilSize);
	draw_eye(head->position.x + SNAKE_CHUNK_SIZE - eyeOffsetX - eyeSize, head->position.y + eyeOffsetY, eyeSize, pupilSize);
}

void draw_apple(Vector2 apple_position)
{
	const int apple_border = 4;
	const int apple_halo = apple_border + apple_border * sin(GetTime() * 4);
	const int apple_halo_size = apple_border;

	DrawRectangleWithBorder(
		apple_position.x - apple_halo_size - apple_halo,
		apple_position.y - apple_halo_size - apple_halo,
		APPLE_SIZE + apple_halo_size * 2 + apple_halo * 2,
		APPLE_SIZE + apple_halo_size * 2 + apple_halo * 2,
		BLACK,
		RED,
		apple_border / 2);

	DrawRectangleWithBorder(apple_position.x, apple_position.y, APPLE_SIZE, APPLE_SIZE, RED, MAROON, apple_border);

	const int stemX = apple_position.x + APPLE_SIZE / 2 - APPLE_STEM_WIDTH / 2;
	const int stemY = apple_position.y - APPLE_STEM_HEIGHT + apple_border;

	DrawRectangle(stemX, stemY, APPLE_STEM_WIDTH, APPLE_STEM_HEIGHT, BROWN);
}

void draw(GameState state)
{
	// Draw apple
	draw_apple(state.apple_position);

	// Draw snake
	draw_snake(&state.snake_head);
}

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SnaCk");

	GameState state = {
		.snake_head = {
			.position = {WINDOW_WIDTH / 2 - SNAKE_CHUNK_SIZE / 2, WINDOW_HEIGHT / 2 - SNAKE_CHUNK_SIZE / 2},
			.next = NULL},
		.snake_direction = Up,
		.apple_position = {10, 10},
		.accumulator = 0};

	while (!WindowShouldClose())
	{
		state = update(state);

		BeginDrawing();

		ClearBackground(BLACK);

		draw(state);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}