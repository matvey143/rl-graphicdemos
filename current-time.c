#include "raylib.h"
#include <time.h>

int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(640, 480, u8"Clock.");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();
		{
			ClearBackground(BLACK);
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
