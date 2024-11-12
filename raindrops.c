#include "raylib.h"
#include <stdlib.h>
#include <time.h>

// TODO: make a rain drop effect on a puddle.
// Density of raindrop should not change after altering resolution.
// I might want to use some data structure for this.
// Likely will be std::vector of c++.

typedef struct {
	Vector2 coords;
	int lifeTime;
	float radius;
	unsigned char alpha;
} Raindrop;

// randomInt(1, 6) should be similiar to dice roll
int randomInt(int minimum, int maximum)
{
	return rand() % maximum - minimum + 2;
}

float randomFloat(float minimum, float maximum)
{
	float scale = rand() / (float) RAND_MAX;
	return minimum + scale * (maximum - minimum);
}

void spreadDrop(Raindrop *drop)
{
	const static float radiusPerFrame = 0.5f;
	const static unsigned char alphaPerFrame = 5;

	drop->radius += radiusPerFrame;
	if (drop->alpha > alphaPerFrame)
		drop->alpha = 0;
	else
		drop->alpha -= alphaPerFrame;
}

void resetDrop(Raindrop *drop, int screenX, int screenY)
{
	drop->coords.x = randomFloat(0.0, float(screenX));
	drop->coords.y = randomFloat(0.0, float(screenY));
	drop->radius = 0.0;
	drop->alpha = 0xFF;

	// Negative values means delay.
	const static int minDelay = -5;
	const static int maxDelay = -20;
	drop->lifeTime = randomInt(minDelay, maxDelay);
}

int main(void)
{
	const int defaultWidth = 640, defaultHeight = 480;
	const Color waterColor = (Color) {0x02, 0x25, 0x2D, 0xFF};
	const int pixelsPerDrop = 100;

	int curWidth = defaultWidth, curHeight =  defaultHeight;
	// IF in WHILE should be triggered as soon as loop starts. 
	int prevWidth = 0, prevHeight = 0;
	int dropAmount;
	Raindrop *drops = malloc(sizeof (Raindrop));

	srand(time(NULL));

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(defaultWidth, defaultHeight, "Rain.");
	SetWindowMinSize(320, 240);
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		curWidth = GetScreenWidth();
		curHeight = GetScreenHeight();
		if (curWidth != prevWidth || curHeight != prevHeight) {
			dropAmount = curWidth * curHeight / pixelsPerDrop;
			drops = realloc(drops, dropAmount * sizeof (Raindrop));
			for (int i = 0; i < dropAmount; i++)
				resetDrops(*drops[i], curWidth, curHeight);
		}
		// TODO: Here should be events
		for (int i = 0; i < dropAmount; i++) {
			if (drops[i]->alpha != 0)
				spreadDrop();
			else
		}

		BeginDrawing();
		ClearBackground(waterColor);
		EndDrawing();

		prevWidth = curWidth;
		prevHeight = curHeight;
	}
	free(drops);
	return 0;
}
