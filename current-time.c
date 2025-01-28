#include "raylib.h"
#include <time.h>

int main(void)
{
	// I intend to make digits size change depending on window size.
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(640, 480, u8"Clock.");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();
		{
			ClearBackground(BLACK);
			// TODO: Here should be "non-lit" clock digits.
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
