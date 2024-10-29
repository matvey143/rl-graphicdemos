#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

// Defining borders of camera area.
// They are macros because they are used by two different functions.
// Might be messy hardcoded crap, but it does it's job.
#define MIN_X -80.0f
#define MAX_X  140.0f
#define MIN_Y -30.0f
#define MAX_Y  60.0f

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

float randomFloat(float minimum, float maximum)
{
	float scale = rand() / (float) RAND_MAX;
	return minimum + scale * (maximum - minimum);
}


void resetStar(struct bgStar *star)
{
	star->coords.x = randomFloat(MIN_X, MAX_X);
	star->coords.y = randomFloat(MIN_Y, MAX_Y);

	const static float minSpeed = 1.0f, maxSpeed = 5.0f;
	star->speed = randomFloat(minSpeed, maxSpeed);
}

void moveStar(struct bgStar *star, float angle,
		float widthScale, float heightScale)
{
	star->coords.x += cos(angle) * star->speed;
	star->coords.y += sin(angle) * star->speed;

	static const float height = MAX_X - MIN_X, width = MAX_Y - MIN_Y;
	// Checking if star is out of bounds
	Rectangle collisionBox = {MIN_X * widthScale, MIN_Y * heightScale,
		width * widthScale, height * heightScale};
	if (!CheckCollisionPointRec(star->coords, collisionBox))
		resetStar(star);
}

//TODO: Needs agjustments.
// Thanks to github user cash-i1 I figured out how to handle wall hits.
// github.com/cash-i1/raylib-dvd-logo 
void moveBall(struct IntroBall *ball_ptr, float widthScale, float heightScale)
{
	ball_ptr->coords.x += ball_ptr->velX;
	ball_ptr->coords.y += ball_ptr->velY;
	if (ball_ptr->coords.x >= MAX_X * widthScale) ball_ptr->velX = -1.0;
	if (ball_ptr->coords.x <= MIN_X * widthScale) ball_ptr->velX = 1.0;
	if (ball_ptr->coords.y >= MAX_Y * heightScale) ball_ptr->velY = -1.0;
	if (ball_ptr->coords.y <= MIN_Y * heightScale) ball_ptr->velY = 1.0;
}

// TODO: make window resizable
// I wanted to recreate old ZUN intro (Touhou 1-3).
int main(void)
{
	const float radius = 20.0;
	const int tempBallAmount = 3;

	struct IntroBall mainBall;
	struct IntroBall tempBalls[ballAmount];

	// TODO: there are long term desync between tempBalls if window is resized.
	// Need to adjust program to address this behavour. 
	// These colors came from picking colors of screenshot, might be inaccurate.
	mainBall.color = (Color) {0x00, 0x00, 0x63, 0xFF};
	tempBalls[0].color = (Color) {0x00, 0x00, 0x9C, 0xFF};
	tempBalls[1].color = (Color) {0x00, 0x00, 0xEF, 0xFF};
	tempBalls[2].color = (Color) {0x63, 0x75, 0xFF, 0xFF};

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
	const int defaultWidth = 640, defaultHeight = 480;
	int curWidth = defaultWidth, curHeight = defaultHeight;
	int prevWidth = 0, prevHeight = 0;
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(defaultWidth, defaultHeight, u8"Old ZUN logo.");
	SetWindowMinSize(320, 240);
	RenderTexture camTexture;

	// Text and fonts;
	char touhou[] = u8"\xe6\x9d\xb1\xe6\x96\xb9 project";
	Font mainfont = LoadFontEx("resources/ume-tmo3.ttf", 32, NULL, 64000);
	Vector2 textSize = MeasureTextEx(mainfont, touhou, 32.0, 0.0);
	
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		curWidth = GetScreenWidth();
		curHeight = GetScreenHeight();
		float widthScale = (float) curWidth / defaultWidth;
		float heightScale = (float) curHeight / defaultHeight;
		// Window is resized.
		if (curWidth != prevWidth && curHeight != prevHeight) {
			UnloadRenderTexture(camTexture);
			camTexture = LoadRenderTexture(curWidth, curHeight/2);
		}

		for (int i = 0; i < starAmount; i++)
			moveStar(&stars[i], angle, widthScale, heightScale);
		for (int i = 0; i < ballAmount; i++)
			moveBall(&tempBalls[i], widthScale, heightScale);
		angle += 0.01;
		// Basically a reset every full turn.
		if (angle > PI + PI) angle -= PI + PI;

		BeginTextureMode(camTexture);
		{
			ClearBackground(BLACK);
			BeginMode2D(camera);
			for(int i = 0; i < starAmount; i++) {
				DrawPixelV(stars[i].coords, WHITE);
			}
			for(int i = 0; i < ballAmount; i++) {
				DrawCircleV(tempBalls[i].coords, radius, tempBalls[i].color);
			}
			EndMode2D();
		}
		EndTextureMode();
		BeginDrawing();
		{
			ClearBackground(BLACK);
			DrawTexture(camTexture.texture, 0, curHeight/4,
					(Color) { 255, 255, 255, 255});
			DrawTextEx(mainfont, touhou,
				(Vector2) {(curWidth - textSize.x) / 2,
				(curHeight - textSize.y) / 2},
				32.0, 0.0, WHITE);
		}
		EndDrawing();
		prevWidth = curWidth;
		prevHeight = curHeight;
	}
	CloseWindow();
	return 0;
}
