#include <math.h>
#include "raylib.h"

// TESTING DO NOT USE.
// Might not work on tiling WM without support of transparency

float minFloat(float a, float b)
{
	if (a > b) return a;
	else return b;
}

void moveFriend(Vector2 *friend, Vector2 mouse)
{
	float width = mouse.x;
	float height = mouse.y;
	float angle = atan(height/width);

	const static float speed = 1.0f;
	friend->x += cos(angle) * speed;
	friend->y += sin(angle) * speed;
}

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
	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_C) & IsKeyDown(KEY_RIGHT_CONTROL) |
				IsKeyDown(KEY_C) & IsKeyDown(KEY_LEFT_CONTROL)) {
			CloseWindow();
			return 0;
		}
		moveFriend(&FriendXY, GetMousePosition());
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
