#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STARS 32
#define RADIUS 5.0

/* stars-2d.c - basic animation that creates random circle-shaped projectiles * 
 * and moves them from the center of the window. This animation should adapt  *
 * to changed window size.                                                    */
struct Star {
	float speed;
	float angle;
	Vector2 coords;
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
	projectile->angle = generateRandomFloat(0.0, M_PI * 2);
	projectile->coords = (Vector2) {startX, startY};
}

int main(void)
{
	const int defaultWidth = 640;
	const int defaultHeight = 480;
	int prevWidth = defaultWidth;
	int prevHeight = defaultHeight;
	const int minWidth = 320;
	const int minHeight = 240;
	int halfHeight = defaultHeight / 2;
	int halfWidth = defaultWidth / 2;

	srand(time(NULL));
	struct Star stars[MAX_STARS];
	stars[0] = (struct Star) {0.0, 0.0, (Vector2) {halfWidth, halfHeight}};
	for (int i = 1; i < MAX_STARS; i++) {
		initNewStar(&stars[i], halfWidth, halfHeight);
	}

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(defaultWidth, defaultHeight, u8"stars-2d.");
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
		// For checking if star is still within window.
		Rectangle screenRec = (Rectangle) {0, 0, curWidth, curHeight};

		for (int i = 0; i < MAX_STARS; i++) {
			moveStar(&stars[i], halfDiffWidth, halfDiffHeight);
			if (!CheckCollisionPointRec(stars[i].coords, screenRec))
				initNewStar(&stars[i], halfWidth, halfHeight);
		}
		BeginDrawing();
		{
			ClearBackground(BLACK);
			for(int i = 0; i < MAX_STARS; i++)
				DrawCircleV(stars[i].coords, RADIUS, WHITE);
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
