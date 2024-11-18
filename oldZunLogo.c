#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Defining borders of camera area.
// They are macros because they are used by two different functions.
// Might be messy hardcoded crap, but it does it's job.
#define DEFAULT_MIN_X  0.0f
#define DEFAULT_MAX_X  640.0f
#define DEFAULT_MIN_Y  0.0f
#define DEFAULT_MAX_Y  240.0f

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

// Both of these are a mess
void resetStar(struct bgStar *star, float widthScale, float heightScale)
{
	star->coords.x = randomFloat(DEFAULT_MIN_X * widthScale,
			DEFAULT_MAX_X * widthScale);
	star->coords.y = randomFloat(DEFAULT_MIN_Y * heightScale,
			DEFAULT_MAX_Y * heightScale);

	const static float minSpeed = 3.0f, maxSpeed = 10.0f;
	star->speed = randomFloat(minSpeed, maxSpeed);
}

void moveStar(struct bgStar *star, float angle,
		float widthScale, float heightScale)
{
	star->coords.x += cos(angle) * star->speed;
	star->coords.y += sin(angle) * star->speed;

	if (star->coords.x >= DEFAULT_MAX_X * widthScale)
		resetStar(star, widthScale, heightScale);
	else if (star->coords.x <= DEFAULT_MIN_X * widthScale)
		resetStar(star, widthScale, heightScale);
	else if (star->coords.y >= DEFAULT_MAX_Y * heightScale)
		resetStar(star, widthScale, heightScale);
	else if (star->coords.y <= DEFAULT_MIN_Y * heightScale)
		resetStar(star, widthScale, heightScale);
}

//TODO: Needs agjustments.
// Thanks to github user cash-i1 I figured out how to handle wall hits.
// github.com/cash-i1/raylib-dvd-logo 
void moveBall(struct IntroBall *ball_ptr, float widthScale, float heightScale)
{
	ball_ptr->coords.x += ball_ptr->velX;
	ball_ptr->coords.y += ball_ptr->velY;
	if (ball_ptr->coords.x >= DEFAULT_MAX_X * widthScale)
		ball_ptr->velX = -1.0;
	if (ball_ptr->coords.x <= DEFAULT_MIN_X * widthScale)
		ball_ptr->velX = 1.0;
	if (ball_ptr->coords.y >= DEFAULT_MAX_Y * heightScale)
		ball_ptr->velY = -1.0;
	if (ball_ptr->coords.y <= DEFAULT_MIN_Y * heightScale)
		ball_ptr->velY = 1.0;
}

// I wanted to recreate old ZUN intro (Touhou 1-3).
int main(void)
{
	srand(time(NULL));

	struct IntroBall mainBall;
	mainBall.coords = (Vector2) {-6.0f, -6.0f};
	mainBall.velX = -1.0f;
	mainBall.velY = -1.0f;

	const int tempBallAmount = 3;
	struct IntroBall tempBalls[tempBallAmount];
	for (int i = 0; i < tempBallAmount; i++) {
		tempBalls[i].coords = mainBall.coords; 
		tempBalls[i].velX = mainBall.velX; 
		tempBalls[i].velY = mainBall.velY; 
	}

	// These colors came from picking colors of screenshot, might be inaccurate.
	mainBall.color = (Color) {0x00, 0x00, 0x63, 0xFF};
	tempBalls[0].color = (Color) {0x00, 0x00, 0x9C, 0xFF};
	tempBalls[1].color = (Color) {0x00, 0x00, 0xEF, 0xFF};
	tempBalls[2].color = (Color) {0x63, 0x75, 0xFF, 0xFF};

	// Initiating stars in background.
	int starAmount = 1;
	float angle = PI;
	struct bgStar *stars = malloc(starAmount * sizeof (struct bgStar));

	// Needs further adjustments.
	Camera2D camera;
	camera.target = (Vector2) {0.0, 0.0};
	camera.offset = (Vector2) {0.0, 0.0};
	camera.rotation = 0.0;
	camera.zoom = 1.0;

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
		if (curWidth != prevWidth || curHeight != prevHeight) {
			const static int pixelsPerStar = 15000;
			starAmount = curWidth * curHeight / pixelsPerStar;
			stars = realloc(stars, starAmount * sizeof (struct bgStar));
			for (int i = 0; i < starAmount; i++)
				resetStar(&stars[i], widthScale, heightScale);

			UnloadRenderTexture(camTexture);
			camTexture = LoadRenderTexture(curWidth, curHeight/2);
		}

		for (int i = 0; i < starAmount; i++)
			moveStar(&stars[i], angle, widthScale, heightScale);

		moveBall(&mainBall, widthScale, heightScale);
		for (int i = 0; i < tempBallAmount; i++) {
			for (int j = 0; j < (i + 1) * 10; j++) {
				moveBall(&tempBalls[i], widthScale, heightScale);
			}
		}
		angle += 0.001;
		// Basically a reset every full turn.
		if (angle > PI + PI) angle -= PI + PI;

		BeginTextureMode(camTexture);
		{
			ClearBackground(BLACK);
			BeginMode2D(camera);

			const static float starSize = 2.0f;
			for(int i = 0; i < starAmount; i++) {
				DrawCircleV(stars[i].coords, starSize, WHITE);
			}

			const static float ballRadius = 30.0f;
			DrawCircleV(mainBall.coords, ballRadius, mainBall.color);
			for(int i = 0; i < tempBallAmount; i++) {
				DrawCircleV(tempBalls[i].coords, 
						ballRadius, tempBalls[i].color);
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
		// Reseting 
		for (int i = 0; i < tempBallAmount; i++) {
			tempBalls[i].coords = mainBall.coords; 
			tempBalls[i].velX = mainBall.velX; 
			tempBalls[i].velY = mainBall.velY; 
		}
	}
	CloseWindow();
	free(stars);
	return 0;
}
