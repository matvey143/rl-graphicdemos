#include <math.h>
#include "raylib.h"
#include "raymath.h"

// TESTING DO NOT USE.
// Might not work on tiling WM without support of transparency

int main(void)
{
	SetConfigFlags( FLAG_WINDOW_MOUSE_PASSTHROUGH |
			// ^ This seems to break GetMousePosition()
			FLAG_WINDOW_TRANSPARENT);
	InitWindow(640, 480, "Friend");
	Vector2 friendXY = {400.0f, 400.0f};
	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_C) & IsKeyDown(KEY_RIGHT_CONTROL) |
				IsKeyDown(KEY_C) & IsKeyDown(KEY_LEFT_CONTROL)) {
			CloseWindow();
			return 0;
		}
		const float speed = 1.0f;
		friendXY = Vector2MoveTowards(friendXY, GetMousePosition(), speed);
		BeginDrawing();
		{
			ClearBackground(BLANK);
			DrawCircleV(friendXY, 20.0f, YELLOW);
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
