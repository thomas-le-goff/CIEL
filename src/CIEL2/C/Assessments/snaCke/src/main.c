// ███████╗███╗   ██╗ █████╗  ██████╗██╗  ██╗███████╗
// ██╔════╝████╗  ██║██╔══██╗██╔════╝██║ ██╔╝██╔════╝
// ███████╗██╔██╗ ██║███████║██║     █████╔╝ █████╗  
// ╚════██║██║╚██╗██║██╔══██║██║     ██╔═██╗ ██╔══╝  
// ███████║██║ ╚████║██║  ██║╚██████╗██║  ██╗███████╗
// ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝
// Thomas Le Goff - BTS CIEL2 2025 

#include <stdlib.h>
#include <math.h>
#include <time.h>

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
	int score;
	float accumulator;
} GameState;

/**
 * @brief Checks if two squares are colliding.
 *
 * Determines whether two square entities, centered at positions `a` and `b`,
 * overlap each other. The size (width/height) of each square is given by
 * `a_size` and `b_size`.
 *
 * @param a        Center position of the first square.
 * @param b        Center position of the second square.
 * @param a_size   Size (width/height) of the first square.
 * @param b_size   Size (width/height) of the second square.
 *
 * @return true if the two squares overlap, false otherwise.
 */
bool check_square_collision(Vector2 a, Vector2 b, int a_size, int b_size)
{
	// TODO: 2.1
	return false;
}

/**
 * @brief Moves the snake to a new position.
 *
 * Updates the position of the snake's head and shifts each body segment
 * to follow the position of the previous one. The order of segments
 * is preserved.
 *
 * @param head          Pointer to the first segment (head) of the snake.
 * @param new_position  New position of the head.
 */
void move_snake(SnakeChunk *head, Vector2 new_position)
{
	SnakeChunk *current = head;
	Vector2 next_position = new_position;

	while (current)
	{
		Vector2 current_position = current->position;
		// TODO: 1.3 (il manque une ligne ...)
		next_position = current_position;
		current = NULL; // TODO: 3.2 (ce n'est pas la bonne ligne ...)
	}
}

/**
 * @brief Grows the snake by adding one new segment.
 *
 * Adds a new segment at the end of the snake, copying the position of
 * the current last segment. This increases the total length of the snake.
 *
 * @param head  Pointer to the first segment (head) of the snake.
 */
void grow_snake(SnakeChunk *head)
{
	// TODO: 3.1 (comment initialiser new ?)
	SnakeChunk *new;
	SnakeChunk *last = head;

	while (/*TODO: 3.1 (quand avons-nous trouvé le dernier maillon ?)*/ false)
	{
		last = last->next;
	}

	// TODO: 3.1 (comment attacher le nouveau maillon au reste du serpent ?)
	new->position = head->position;
	new->next = NULL;
}

/**
 * @brief Frees all memory used by the snake.
 *
 * Iterates through the linked list representing the snake and releases
 * each dynamically allocated segment (head is not dynamically allocated).
 *
 * @param head  Pointer to the first segment (head) of the snake.
 */
void free_snake(SnakeChunk *head)
{
	// TODO: 4.2
}

/**
 * @brief Draws the player's current score on screen.
 *
 * This function is responsible for displaying the score
 * in a visible area of the window (e.g., top-left corner).
 * You can use Raylib functions like DrawText() or DrawTextFormat().
 *
 * @param score The current score to display.
 */
void draw_score(int score)
{
	// TODO: 2.3
}

/**
 * @brief Moves the apple to a new random position within the game window.
 *
 * The apple is repositioned randomly while ensuring it stays
 * within the visible area and not too close to the window borders.
 * You may adjust the random range for better gameplay balance.
 *
 * @param position A pointer to the apple's current position (Vector2).
 */
void move_apple(Vector2 *position)
{
	// Bonus : adaptez les valeurs pour rendre le jeu plus juste...
	position->x = GetRandomValue(SNAKE_CHUNK_SIZE, WINDOW_WIDTH - SNAKE_CHUNK_SIZE),
	position->y = GetRandomValue(SNAKE_CHUNK_SIZE, WINDOW_HEIGHT - SNAKE_CHUNK_SIZE);
}

/**
 * @brief Checks whether the Snake game is over.
 *
 * This function analyzes the current state of the snake starting from its head (`head`)
 * and returns `true` if a game-over condition is detected, such as:
 * - collision with the game field boundaries;
 * - collision with the snake's own body;
 *
 * @param head Pointer to the first segment (the head) of the snake.
 * @return true if the game is over, false otherwise.
 */
bool is_game_over(SnakeChunk *head)
{
	// TODO: 4.1
	return false;
}

GameState initial_state()
{
	GameState newState = {
		.snake_head = {
			.position = {WINDOW_WIDTH / 2 - SNAKE_CHUNK_SIZE / 2, WINDOW_HEIGHT / 2 - SNAKE_CHUNK_SIZE / 2},
			.next = NULL},
		.snake_direction = Up,
		.apple_position = {10, 10},
		.score = 0,
		.accumulator = 0};

	return newState;
}

/**
 * @brief Updates the game state for one frame.
 *
 * This function handles player input, time progression,
 * snake movement, and collision detection with the apple.
 * It should be called every frame from the main game loop.
 *
 * @param state The current game state (snake, apple, score, etc.).
 * @return The updated game state after processing movement and collisions.
 */
GameState update(GameState state)
{
	// TODO: 1.1
	if (IsKeyDown(KEY_UP) && state.snake_direction > Down)
	{
		state.snake_direction = Up;
	}

	if (IsKeyDown(KEY_RIGHT) && state.snake_direction <= Down)
	{
		state.snake_direction = Right;
	}

	float dt = GetFrameTime();
	state.accumulator += dt;
	while (state.accumulator >= STEP_INTERVAL)
	{
		state.accumulator -= STEP_INTERVAL;

		Vector2 new_position = state.snake_head.position;

		// TODO: 1.2
		switch (state.snake_direction)
		{
		case Up:
			new_position.y -= SNAKE_SPEED;
			break;
		default:
			break;
		}

		move_snake(&state.snake_head, new_position);

		if (check_square_collision(state.snake_head.position, state.apple_position, SNAKE_CHUNK_SIZE, APPLE_SIZE))
		{
			// TODO: 2.2
		}

		if (is_game_over(&state.snake_head))
		{
			free_snake(&state.snake_head);
			state = initial_state();
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
	draw_apple(state.apple_position);
	draw_snake(&state.snake_head);
	draw_score(state.score);
}

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SnaCke");

	SetRandomSeed(time(NULL));

	GameState state = initial_state();

	// Create the first apple
	move_apple(&state.apple_position);

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