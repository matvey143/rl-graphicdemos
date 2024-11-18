#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* stars-2d.c - basic animation that creates random circle-shaped projectiles * 
 * and moves them from the center of the window. This animation should adapt  *
 * to changed window size.                                                    */
struct Star {
	float speed;
	float angle;
	Vector2 coords;
	Color color;
};

// Credit goes baz from Stack Overflow forum for this function.
// https://stackoverflow.com/a/44105089
float generateRandomFloat(float minimum, float maximum)
{
	float scale = rand() / (float) RAND_MAX;
	return minimum + scale * (maximum - minimum);
}

void moveStar(struct Star *ptr_star, int xOffset, int yOffset)
{
	ptr_star->coords.x += xOffset + cos(ptr_star->angle) * ptr_star->speed;
	ptr_star->coords.y += yOffset + sin(ptr_star->angle) * ptr_star->speed;
}

void initNewStar(struct Star *projectile, int startX, int startY)
{
	projectile->speed = generateRandomFloat(1.0, 10.0);
	projectile->angle = generateRandomFloat(0.0, PI + PI);
	projectile->coords = (Vector2) {startX, startY};
	int temp = rand();
	char *byte = (char *) &temp;
	projectile->color = (Color) {byte[0], byte[1], byte[2], 0xFF};
}

// TODO: Make star amount scale with window size.
int main(void)
{
	bool noColor = false; 

	const int defaultWidth = 640, defaultHeight = 480;
	const int minWidth = 320, minHeight = 240;
	int prevWidth = defaultWidth, prevHeight = defaultHeight;
	int halfHeight = defaultHeight / 2, halfWidth = defaultWidth / 2;

	srand(time(NULL));

	const int pixelsPerStar = 15000;
	int starsAmount = defaultWidth * defaultHeight / pixelsPerStar;
	struct Star *stars = malloc(sizeof (struct Star) * starsAmount);
	stars[0] = (struct Star) {0.0, 0.0, (Vector2) {halfWidth, halfHeight}, WHITE};
	for (int i = 1; i < starsAmount; i++) {
		initNewStar(&stars[i], halfWidth, halfHeight);
	}

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(defaultWidth, defaultHeight,
			u8"stars-2d. Press spacebar to change color mode.");
	SetWindowMinSize(minWidth, minHeight);
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		int curHeight = GetScreenHeight();
		int curWidth = GetScreenWidth();
		// Needed to center stars on screen.
		halfHeight = curHeight / 2;
		halfWidth = curWidth / 2;
		// Needed to offset depending on changed window size
		int halfDiffWidth = (curWidth - prevWidth) / 2;
		int halfDiffHeight = (curHeight - prevHeight) / 2;
		if (curWidth != prevWidth || curHeight != prevHeight) {
			starsAmount = curWidth * curHeight / pixelsPerStar;
			stars = realloc(stars, starsAmount * sizeof (struct Star));

			stars[0].angle = 0.0;
			stars[0].speed = 0.0;
			stars[0].coords = (Vector2) {halfWidth, halfHeight};
			stars[0].color = WHITE;
			for (int i = 1; i < starsAmount; i++) {
				initNewStar(&stars[i], halfWidth, halfHeight);
			}
		}
		// For checking if star is still within window.
		Rectangle screenRec = (Rectangle) {0, 0, curWidth, curHeight};
		if (IsKeyReleased(KEY_SPACE)) noColor = !noColor;

		// Don't like this hack, but without it central star is slightly off-center after resizing window.
		initNewStar(&stars[0], halfWidth, halfHeight);
		for (int i = 1; i < starsAmount; i++) {
			moveStar(&stars[i], halfDiffWidth, halfDiffHeight);
			if (!CheckCollisionPointRec(stars[i].coords, screenRec))
				initNewStar(&stars[i], halfWidth, halfHeight);
		}
		BeginDrawing();
		{
			ClearBackground(BLACK);
			const static float radius = 5.0;
			if(noColor) {
				for(int i = 0; i < starsAmount; i++) {
					DrawCircleV(stars[i].coords, radius, WHITE);
				}
			}
			else {
				for(int i = 1; i < starsAmount; i++) {
					DrawCircleV(stars[i].coords, radius, stars[i].color);
				}
				DrawCircleV(stars[0].coords, radius, WHITE);
			}
#ifdef DEBUG
			DrawFPS(0, 0);
#endif
		}
		EndDrawing();
		prevWidth = curWidth;
		prevHeight = curHeight;
	}
	return 0;
}
