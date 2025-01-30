#include "raylib.h"
#include <time.h>

int drawSeparator(int offset, int ledWidth, int screenheight)
{
	DrawRectangle(offset + ledWidth, screenheight / 4, ledWidth, ledWidth, GREEN);
	DrawRectangle(offset + ledWidth, screenheight / 4 + screenheight / 2, ledWidth, ledWidth, GREEN);
	offset += 2 * ledWidth;
	return offset;
}

int drawDigit(int offset, int hLedLength, int vLedLength, int ledWidth)
{
	/*  000                                 *
	 * 3   5                                *
	 * 3   5                                *
	 *  111                                 *
	 * 4   6                                *
	 * 4   6                                *
	 *  222                                 * 
	 *  This is the order of LEDs in array. */
	// Top horizontal
	DrawRectangle(ledWidth * 2 + offset, ledWidth, hLedLength, ledWidth, GRAY);
	// Middle horizontal
	DrawRectangle(ledWidth * 2 + offset, ledWidth * 2 + vLedLength, hLedLength, ledWidth, GRAY);
	// Bottom horizontal
	DrawRectangle(ledWidth * 2 + offset, ledWidth * 3 + vLedLength * 2, hLedLength, ledWidth, GRAY);
	// Topleft vertical
	DrawRectangle(ledWidth + offset, ledWidth * 2, ledWidth, vLedLength, GRAY);
	// Bottomleft vertical
	DrawRectangle(ledWidth + offset, ledWidth * 3 + vLedLength, ledWidth, vLedLength, GRAY);
	// Topright vertical
	DrawRectangle(ledWidth * 2 + offset + hLedLength, ledWidth * 2, ledWidth, vLedLength, GRAY);
	// Bottomright vertical
	DrawRectangle(ledWidth * 2 + offset + hLedLength, ledWidth * 3 + vLedLength, ledWidth, vLedLength, GRAY);
	offset += 3 * ledWidth + hLedLength;
	return offset;
}

int main(void)
{
	// I intend to make digits size change depending on window size.
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(640, 360, u8"Clock.");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		// Might not be perfect.
		int screenwidth = GetScreenWidth();
		int screenheight = GetScreenHeight();
		int ledWidth = screenwidth / (23 * 5);
		int hLedLength = (screenwidth - ledWidth * 23) / 6;
		int vLedLength = (screenheight - ledWidth * 5) / 2;

		struct tm curTime = localtime(time(NULL));
		
		BeginDrawing();
		{
			ClearBackground(BLACK);
			// Hours.
			int offset = drawDigit(0, hLedLength, vLedLength, ledWidth);
			offset = drawDigit(offset, hLedLength, vLedLength, ledWidth);
			offset = drawSeparator(offset, ledWidth, screenheight);
			// Minutes.
			offset = drawDigit(offset, hLedLength, vLedLength, ledWidth);
			offset = drawDigit(offset, hLedLength, vLedLength, ledWidth);
			offset = drawSeparator(offset, ledWidth, screenheight);
			// Seconds.
			offset = drawDigit(offset, hLedLength, vLedLength, ledWidth);
			offset = drawDigit(offset, hLedLength, vLedLength, ledWidth);
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
