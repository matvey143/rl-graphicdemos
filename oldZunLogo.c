#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

// Defining borders of camera area.
// They are macros because they are used by two different functions.
#define MIN_X -80.0f
#define MAX_X  80.0f
#define MIN_Y -30.0f
#define MAX_Y  30.0f

float randomFloat(float minimum, float maximum)
{
	float scale = rand() / (float) RAND_MAX;
	return minimum + scale * (maximum - minimum);
}

struct bgStar {
	Vector2 coords;
	float speed;
};

struct IntroBall {
	Vector2 coords;
	Color color;
	float velX;
	float velY;
};

void resetStar(struct bgStar *star)
{
	star->coords.x = randomFloat(MIN_X, MAX_X);
	star->coords.y = randomFloat(MIN_Y, MAX_Y);

	const static float minSpeed = 5.0f, maxSpeed = 10.0f;
	star->speed = randomFloat(minSpeed, maxSpeed);
}

void moveStar(struct bgStar *star, float angle)
{
	star->coords.x += cos(angle) * star->speed;
	star->coords.y += sin(angle) * star->speed;

	// Checking if star is out of bounds
	static const Rectangle collisionBox = {MIN_X, MIN_Y,
		MAX_X - MIN_X, MAX_Y - MIN_Y};
	if (!CheckCollisionPointRec(star->coords, collisionBox))
		resetStar(star);
}

//TODO: Needs agjustments.
// Thanks to github user cash-i1 I figured out how to handle wall hits.
// github.com/cash-i1/raylib-dvd-logo 
void moveBall(struct IntroBall *ball_ptr)
{
	ball_ptr->coords.x += ball_ptr->velX;
	ball_ptr->coords.y += ball_ptr->velY;
	if (ball_ptr->coords.x >= MAX_X) ball_ptr->velX = -1.0;
	if (ball_ptr->coords.x <= MIN_X) ball_ptr->velX = 1.0;
	if (ball_ptr->coords.y >= MAX_Y) ball_ptr->velY = -1.0;
	if (ball_ptr->coords.y <= MIN_Y) ball_ptr->velY = 1.0;
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
	// These colors came from picking colors from screenshot.
	balls[0].color = (Color) {0x00, 0x00, 0x63, 0xFF};
	balls[1].color = (Color) {0x00, 0x00, 0x9C, 0xFF};
	balls[2].color = (Color) {0x00, 0x00, 0xEF, 0xFF};
	balls[3].color = (Color) {0x63, 0x75, 0xFF, 0xFF};

	// Initiating stars in background.
	const int starAmount = 12;
	float angle = PI;
	struct bgStar stars[starAmount];
	for (int i = 0; i < starAmount; i++) resetStar(&stars[i]);

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
		for (int i = 0; i < starAmount; i++) moveStar(&stars[i], angle);
		for (int i = 0; i < ballAmount; i++) moveBall(&balls[i]);

		BeginTextureMode(camTexture);
		{
			ClearBackground(BLACK);
			BeginMode2D(camera);
			for(int i = 0; i < starAmount; i++) {
				DrawPixelV(stars[i].coords, WHITE);
			}
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
