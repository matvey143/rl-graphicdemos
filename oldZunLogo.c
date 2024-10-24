#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>

// Thanks to github user cash-i1 I figured out how to handle wall hits.
// github.com/cash-i1/raylib-dvd-logo 

struct IntroBall {
	Vector2 coords;
	Color color;
	float velX;
	float velY;
};

//TODO: Needs agjustments.
void moveBall(struct IntroBall *ball_ptr)
{
	ball_ptr->coords.x += ball_ptr->velX;
	ball_ptr->coords.y += ball_ptr->velY;
	// Changing direction of ball if necessary.
	const static float minX = -80.0, maxX = 80.0;
	const static float minY = -30.0, maxY = 30.0;
	if (ball_ptr->coords.x >= maxX) ball_ptr->velX = -1.0;
	if (ball_ptr->coords.x <= minX) ball_ptr->velX = 1.0;
	if (ball_ptr->coords.y >= maxY) ball_ptr->velY = -1.0;
	if (ball_ptr->coords.y <= minY) ball_ptr->velY = 1.0;
}

// I wanted to recreate old ZUN intro (Touhou 1-3).
int main(void)
{
	const float radius = 20.0;
	const int ballAmount = 4;

	struct IntroBall balls[ballAmount];
	for (int i = 0; i < ballAmount; i++) {
		balls[i].coords = (Vector2) {-6.0, 6.0};
		balls[i].velX = -1.0;
		balls[i].velY = 1.0;
		//Need to move balls apart.
		for(int j = 0; j < 10 * i; j++) moveBall(&balls[i]);
	}
	// This colors are placeholders. TODO: change them to proper colors.
	balls[0].color = BLUE;
	balls[1].color = RED;
	balls[2].color = GREEN;
	balls[3].color = YELLOW;

	// Needs further adjustments.
	Camera2D camera;
	camera.target = (Vector2) {0.0, 0.0};
	camera.offset = (Vector2) {240.0, 80.0};
	camera.rotation = 0.0;
	camera.zoom = 3.0;

	// Might adjust program to make window resizable.
	const int screenWidth = 640, screenHeight = 480;
	InitWindow(screenWidth, screenHeight, u8"Old ZUN logo.");
	RenderTexture camTexture = LoadRenderTexture(screenWidth,screenHeight/2);

	// Text and fonts;
	char touhou[] = u8"\xe6\x9d\xb1\xe6\x96\xb9 project";
	Font mainfont = LoadFontEx("resources/ume-tmo3.ttf", 32, NULL, 64000);
	Vector2 textSize = MeasureTextEx(mainfont, touhou, 32.0, 0.0);
	
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		for (int i = 0; i < ballAmount; i++) moveBall(&balls[i]);
		BeginTextureMode(camTexture);
		{
			ClearBackground(BLACK);
			BeginMode2D(camera);
			for(int i = 0; i < ballAmount; i++) {
				DrawCircleV(balls[i].coords, radius, balls[i].color);
			}
			EndMode2D();
		}
		EndTextureMode();
		BeginDrawing();
		{
			ClearBackground(BLACK);
			DrawTexture(camTexture.texture, 0, screenHeight/4,
					(Color) { 255, 255, 255, 255});
			DrawTextEx(mainfont, touhou,
				(Vector2) {(screenWidth - textSize.x) / 2,
				(screenHeight - textSize.y) / 2},
				32.0, 0.0, WHITE);
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
