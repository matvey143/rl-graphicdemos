#include "raylib.h"
#include <cmath>
#include <random>

constexpr int maxStars = 64;
constexpr float radius = 5.0;
constexpr float minSpeed = 1.0;
constexpr float maxSpeed = 10.0;

//TODO: remake using 2dCamera
//Initializing random number generator for class Star
std::random_device randDevice;
std::mt19937 rng(randDevice());
std::uniform_real_distribution<float> randomAngle(0, 2 * M_PI);
std::uniform_real_distribution<float> randomSpeed(minSpeed, maxSpeed);
std::uniform_int_distribution<unsigned char> randomColor(0, 0xFF);

class Star {
public:
	float speed;
	float angle;
	Vector2 coords;
	Color color;

	void moveStar(int xOffset, int yOffset)
	{
		coords.x += xOffset + std::cos(angle) * speed;
		coords.y += yOffset + std::sin(angle) * speed;
	}
	Star(int startX, int startY)
	{
		speed = randomSpeed(rng);
		angle = randomAngle(rng);
		coords = (Vector2) {(float) startX, (float) startY};
		color.r = randomColor(rng);
		color.g = randomColor(rng);
		color.b = randomColor(rng);
		color.a = 0xFF;
	}
};

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

	bool noColor = false; 

	Star *stars = (Star *) malloc(maxStars * sizeof (Star));
	for (int i = 0; i < maxStars; i++)
	
	stars[0].angle = 0.0;
	stars[0].speed = 0.0;
	stars[0].coords = (Vector2) { (float)halfWidth, (float)halfHeight };
	stars[0].color = WHITE;
	for (int i = 1; i < maxStars; i++) {
		stars[i] = Star(halfWidth, halfHeight);
	}

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(defaultWidth, defaultHeight,
		u8"stars-2d in C++. Press spacebar to change color mode.");
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
		Rectangle screenRec;
		screenRec.x = 0.0;
		screenRec.y = 0.0;
		screenRec.width = (float) curWidth;
		screenRec.height = (float) curHeight;

		// Switching color mode.
		if (IsKeyReleased(KEY_SPACE)) noColor = !noColor;

		// Don't like this hack, but without it central star is slightly off-center after resizing window.
		stars[0] = Star (halfWidth, halfHeight);

		for (int i = 1; i < maxStars; i++) {
			stars[i].moveStar(halfDiffWidth, halfDiffHeight);
			if (!CheckCollisionPointRec(stars[i].coords, screenRec))
				stars[i] = Star(halfWidth, halfHeight);
		}
		BeginDrawing();
		{
			ClearBackground(BLACK);
			if (noColor) {
				for(int i = 0; i < maxStars; i++)
					DrawCircleV(stars[i].coords, radius, WHITE);
			}
			else {
				for(int i = 1; i < maxStars; i++) {
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
