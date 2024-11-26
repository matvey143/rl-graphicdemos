#include <math.h>
#include "raylib.h"

// TESTING DO NOT USE.
// Might not work on tiling WM without support of transperency
int main(void)
{
	SetConfigFlags(FLAG_WINDOW_MOUSE_PASSTHROUGH | 
			// I struggle to get it working on XFCE
			FLAG_WINDOW_TRANSPARENT |
			FLAG_WINDOW_UNDECORATED |
			FLAG_WINDOW_TOPMOST |
			FLAG_WINDOW_UNFOCUSED);
	InitWindow(GetScreenWidth(), GetScreenHeight(), "Friend");
	SetWindowPosition(0, 0);
	Vector2 FriendXY = {400.0f, 400.0f};
	while (!WindowShouldClose())
	{
		if (IsKeyDown(KEY_C) & IsKeyDown(KEY_RIGHT_CONTROL) |
				IsKeyDown(KEY_C) & IsKeyDown(KEY_LEFT_CONTROL)){
			CloseWindow();
			return 0;
		}
		// TODO: Add here logic to move friend according to cursor XY.
		BeginDrawing();
		{
			ClearBackground(BLANK);
			DrawCircleV(FriendXY, 20.0f, YELLOW);
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
