#include "raylib.h"
#include <stdlib.h>
#include <time.h>

// Density of raindrop should not change after altering resolution.
// TODO: add more chaos maybe?

typedef struct {
	Vector2 coords;
	int lifeTime;
	float radius;
	unsigned char alpha;
} Raindrop;

// randomInt(1, 6) should be similiar to dice roll
int randomInt(int minimum, int maximum)
{
	return rand() % (maximum - minimum + 1) + minimum;
}

float randomFloat(float minimum, float maximum)
{
	float scale = rand() / (float) RAND_MAX;
	return minimum + scale * (maximum - minimum);
}

void spreadDrop(Raindrop *drop)
{
	drop->lifeTime++;
	if(drop->lifeTime > 0) {
		const static float radiusPerFrame = 0.5f;
		const static unsigned char alphaPerFrame = 2;

		drop->radius += radiusPerFrame;
		if (drop->alpha < alphaPerFrame)
			drop->alpha = 0;
		else
			drop->alpha -= alphaPerFrame;
	}
}

void resetDrop(Raindrop *drop, int screenX, int screenY)
{
	drop->coords.x = randomFloat(0.0, (float) screenX);
	drop->coords.y = randomFloat(0.0, (float) screenY);
	drop->radius = 0.0;
	drop->alpha = 0xFF;

	// Negative values means delay before apearing on screen.
	const static int minDelay = -80;
	const static int maxDelay = -5;
	drop->lifeTime = randomInt(minDelay, maxDelay);
}

int main(void)
{
	const int defaultWidth = 640, defaultHeight = 480;
	const Color waterColor = (Color) {0x02, 0x25, 0x2D, 0xFF};
	const int pixelsPerDrop = 10000;

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
				resetDrop(&drops[i], curWidth, curHeight);
		}
		for (int i = 0; i < dropAmount; i++) {
			if (drops[i].alpha != 0)
				spreadDrop(&drops[i]);
			else
				resetDrop(&drops[i], curWidth, curHeight);
		}

		BeginDrawing();
		ClearBackground(waterColor);
		for (int i = 0; i < dropAmount; i++) {
			if (drops[i].lifeTime > 0) {
				DrawCircleLinesV(drops[i].coords, drops[i].radius,
						(Color) {0xFF, 0xFF, 0xFF, drops[i].alpha});
			}
		}
		EndDrawing();

		prevWidth = curWidth;
		prevHeight = curHeight;
	}
	free(drops);
	return 0;
}
