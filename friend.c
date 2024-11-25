#include "raylib.h"

// TESTING DO NOT USE.
int main(void)
{
	SetConfigFlags(FLAG_WINDOW_MOUSE_PASSTHROUGH | FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED);
	InitWindow(GetScreenWidth(), GetScreenHeight(), "Friend");
	SetWindowPosition(0, 0);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		{
			ClearBackground(BLANK);
			DrawCircle(400, 400, 20, YELLOW);
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
