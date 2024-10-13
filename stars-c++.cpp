#include "raylib.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

#define MAX_STARS 32
#define RADIUS 5.0

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

	void moveStar(int xOffset, int yOffset)
	{
		//Сдвинуть снаряд учитывая его скорость и изменения размера окна.
		coords.x += xOffset + std::cos(angle) * speed;
		coords.y += yOffset + std::sin(angle) * speed;
	}
	void resetPosition(int startX, int startY)
	{
		speed = generateRandomFloat(1.0, 10.0);
		angle = generateRandomFloat(0.0, M_PI * 2);
		coords = (Vector2) {startX, startY};
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

	std::srand(time(NULL));
	Star stars[MAX_STARS];
	
	stars[0].angle = 0.0;
	stars[0].speed = 0.0;
	stars[0].coords = (Vector2) { (float)halfWidth, (float)halfHeight };
	for (int i = 1; i < MAX_STARS; i++) {
		stars[i].resetPosition(halfWidth, halfHeight);
	}

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(defaultWidth, defaultHeight, u8"Снаряды.");
	SetWindowMinSize(minWidth, minHeight);
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		int curHeight = GetScreenHeight();
		int curWidth = GetScreenWidth();
		halfHeight = curHeight / 2;
		halfWidth = curWidth / 2;
		int halfDiffWidth = (curWidth - prevWidth) / 2;
		int halfDiffHeight = (curHeight - prevHeight) / 2;
		Rectangle screenRec = (Rectangle) {0, 0, curWidth, curHeight};

		stars[0].resetPosition(halfWidth, halfHeight);
		for (int i = 1; i < MAX_STARS; i++) {
			stars[i].moveStar(halfDiffWidth, halfDiffHeight);
			if (!CheckCollisionPointRec(stars[i].coords, screenRec))
				stars[i].resetPosition(halfWidth, halfHeight);
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