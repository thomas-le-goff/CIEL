#include <filesystem>
#include <iostream>

#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"

#include "crypto_monster.hpp"
#include "part.hpp"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

const int RENDER_TEXTURE_WIDTH = 1280;
const int RENDER_TEXTURE_HEIGHT = 720;

int main()
{
	{
		SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);

		InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CryptoMonster");

		SearchAndSetResourceDir("resources");
		PartManager part_manager = {{
			{"arm", 30},
			{"body", 36},
			{"detail", 42},
			{"eye", 20},
			{"leg", 30},
			{"mouth", 14},
			{"nose", 4},
		}};

		RenderTexture2D target = LoadRenderTexture(RENDER_TEXTURE_WIDTH, RENDER_TEXTURE_HEIGHT);

		bool drawn = false;

		while (!WindowShouldClose())
		{
			// Re-generate
			if (IsKeyPressed(KEY_SPACE))
			{
				// TODO
			}

			// Export to image
			if (drawn && IsKeyPressed(KEY_ENTER))
			{
				// TODO
			}

			// TODO

			// Draw
			BeginDrawing();
			{
				if (!drawn)
				{
					drawn = true;

					BeginTextureMode(target);
					{
						ClearBackground(BLACK);

						// TODO
					}
					EndTextureMode();
				}

				DrawTexturePro(target.texture, Rectangle{0, 0, (float)target.texture.width, -(float)target.texture.height}, Rectangle{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, Vector2{0, 0}, 0, WHITE);

				DrawText("Appuyez sur ENTREE pour exporter l'image", 10, 10, 20, WHITE);
				DrawText("Appuyez sur ESPACE pour générer un nouveau CryptoMonster", 10, 35, 20, WHITE);
			}
			EndDrawing();
		}
	}

	CloseWindow();
	return 0;
}