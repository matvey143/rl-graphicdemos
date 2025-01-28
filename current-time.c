#include "raylib.h"
#include <time.h>

int drawDigit(int offset, int ledLength, int ledWidth)
{
	//Top horizontal
	DrawRectangle(ledWidth + ledWidth + offset, ledWidth, ledLength, ledWidth, GRAY);
	offset += 3 * ledWidth + ledLength;
	return offset;
}

int main(void)
{
	// I intend to make digits size change depending on window size.
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(640, 480, u8"Clock.");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		// TODO: finish. Horizontal and vertical LEDs
		// should have different length.
		int width = GetScreenWidth();
		int height = GetScreenHeight();
		int ledWidth = width / (23 * 5);
		int hLedLength = (width - ledWidth * 23) / 6;

		BeginDrawing();
		{
			ClearBackground(BLACK);
			drawDigit(0, ledLength, ledWidth);
			// TODO: Here should be "non-lit" clock digits.
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
