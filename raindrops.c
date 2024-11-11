#include "raylib.h"
#include <stdlib.h>
#include <time.h>

// TODO: make a rain drop effect on a puddle.
// Density of raindrop should not change after altering resolution.
// I might want to use some data structure for this.

float randomFloat(float minimum, float maximum)
{
	float scale = rand() / (float) RAND_MAX;
	return minimum + scale * (maximum - minimum);
}

struct Raindrop {
	Vector2 coords;
	int lifeTime;
};

void resetDrop(struct Raindrop *drop, int screenX, int screenY)
{
	drop->coords.x = randomFloat(0.0, float(screenX));
	drop->coords.y = randomFloat(0.0, float(screenY));
	// Res
}

int main(void)
{
	const int defaultWidth = 640, defaultHeight = 480;
	const Color waterColor = (Color) {0x02, 0x25, 0x2D, 0xFF};

	int curWidth = defaultWidth, curHeight =  defaultHeight;
	int prevWidth = 0, prevHeight = 0;

	srand(time(NULL));

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(defaultWidth, defaultHeight, "Rain.");
	SetWindowMinSize(320, 240);
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		curWidth = GetScreenWidth();
		curHeight = GetScreenHeight();
		if (curWidth != prevWidth || curHeight != prevHeight)
		// TODO: Here should be events

		BeginDrawing();
		ClearBackground(waterColor);
		EndDrawing();

		prevWidth = curWidth;
		prevHeight = curHeight;
	}
	return 0;
}
