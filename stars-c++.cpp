#include "raylib.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

#define MAX_STARS 64
#define RADIUS 5.0

/* stars-c++.cpp - basically a port of stars2d.c to C++.                      *
 * I thought using of class function would result in more readable code.      */

// I know rand() is not recomended in C++, but I wanted to port stars2d.c 
// with minimal changes to functionality.
float generateRandomFloat(float minimum, float maximum)
{
	float scale = std::rand() / (float) RAND_MAX;
	return minimum + scale * (maximum - minimum);
}

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
	void resetPosition(int startX, int startY)
	{
		speed = generateRandomFloat(1.0, 10.0);
		angle = generateRandomFloat(0.0, M_PI * 2);
		coords = (Vector2) {(float) startX, (float) startY};
		int temp = std::rand();
		unsigned char *byte_ptr = (unsigned char *) &temp;
		color = (Color) {byte_ptr[0], byte_ptr[1], byte_ptr[2], 0xFF};
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

	std::srand(time(NULL));
	Star stars[MAX_STARS];
	
	stars[0].angle = 0.0;
	stars[0].speed = 0.0;
	stars[0].coords = (Vector2) { (float)halfWidth, (float)halfHeight };
	stars[0].color = WHITE;
	for (int i = 1; i < MAX_STARS; i++) {
		stars[i].resetPosition(halfWidth, halfHeight);
	}

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(defaultWidth, defaultHeight, u8"stars-2d in C++. Press spacebar to change color mode.");
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
		Rectangle screenRec = (Rectangle) {0, 0, (float) curWidth, (float) curHeight};
		// For checking if star is still within window.
		
		// Don't like this hack, but without it central star is slightly off-center after resizing window.
		stars[0].resetPosition(halfWidth, halfHeight);
		for (int i = 1; i < MAX_STARS; i++) {
			stars[i].moveStar(halfDiffWidth, halfDiffHeight);
			if (!CheckCollisionPointRec(stars[i].coords, screenRec))
				stars[i].resetPosition(halfWidth, halfHeight);
		}
		BeginDrawing();
		{
			ClearBackground(BLACK);
			if (noColor) {
				for(int i = 0; i < MAX_STARS; i++)
					DrawCircleV(stars[i].coords, RADIUS, WHITE);
			}
			else {
				for(int i = 1; i < MAX_STARS; i++) {
					DrawCircleV(stars[i].coords, RADIUS, stars[i].color);
				}
				DrawCircleV(stars[0].coords, RADIUS, WHITE);
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
