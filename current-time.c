#include "raylib.h"
#include <time.h>

int drawSeparator(int offset, int ledWidth, int screenheight, Color color)
{
	int pad = (screenheight - 2 * ledWidth) / 3;
	DrawRectangle(offset + ledWidth, pad, ledWidth, ledWidth, color);
	DrawRectangle(offset + ledWidth, pad + pad + ledWidth,
			ledWidth, ledWidth, color);
	offset += 2 * ledWidth;
	return offset;
}

int drawDigit(int offset,
		int hLedLength,
		int vLedLength,
		int ledWidth,
		int digit,
		Color color)
{
	Color ledColors[] = {DARKGRAY, DARKGRAY, DARKGRAY, DARKGRAY, DARKGRAY,
		DARKGRAY, DARKGRAY};
	/*  000                                 *
	 * 3   5                                *
	 * 3   5                                *
	 *  111                                 *
	 * 4   6                                *
	 * 4   6                                *
	 *  222                                 * 
	 *  This is the order of LEDs in array. */
	switch (digit) {
	case 0:
		ledColors[0] = color, ledColors[2] = color,
			ledColors[3] = color, ledColors[4] = color, 
			ledColors[5] = color, ledColors[6] = color;
		break;
	case 1:
		ledColors[5] = color, ledColors[6] = color;
		break;
	case 2:
		ledColors[0] = color, ledColors[1] = color, ledColors[2] = color,
			ledColors[4] = color, ledColors[5] = color;
		break;
	case 3:
		ledColors[0] = color, ledColors[1] = color, ledColors[2] = color,
			ledColors[5] = color, ledColors[6] = color;
		break;
	case 4:
		ledColors[3] = color, ledColors[5] = color, ledColors[6] = color,
			ledColors[1] = color;
		break;
	case 5:
		ledColors[0] = color, ledColors[1] = color, ledColors[2] = color,
			ledColors[3] = color, ledColors[6] = color;
		break;
	case 6:
		ledColors[0] = color, ledColors[1] = color, ledColors[2] = color,
			ledColors[3] = color, ledColors[6] = color,
			ledColors[4] = color;
		break;
	case 7:
		ledColors[5] = color, ledColors[6] = color,
			ledColors[0] = color;
		break;
	case 8:
		ledColors[0] = color, ledColors[1] = color, ledColors[2] = color,
			ledColors[3] = color, ledColors[6] = color,
			ledColors[4] = color, ledColors[5] = color;
		break;
	case 9:
		ledColors[0] = color, ledColors[1] = color, ledColors[2] = color,
			ledColors[3] = color, ledColors[6] = color,
			ledColors[5] = color;
		break;
	default:
		break;
	}
	// Top horizontal
	DrawRectangle(ledWidth * 2 + offset, ledWidth,
			hLedLength, ledWidth, ledColors[0]);
	// Middle horizontal
	DrawRectangle(ledWidth * 2 + offset, ledWidth * 2 + vLedLength,
			hLedLength, ledWidth, ledColors[1]);
	// Bottom horizontal
	DrawRectangle(ledWidth * 2 + offset, ledWidth * 3 + vLedLength * 2,
			hLedLength, ledWidth, ledColors[2]);
	// Topleft vertical
	DrawRectangle(ledWidth + offset, ledWidth * 2, 
			ledWidth, vLedLength, ledColors[3]);
	// Bottomleft vertical
	DrawRectangle(ledWidth + offset, ledWidth * 3 + vLedLength,
			ledWidth, vLedLength, ledColors[4]);
	// Topright vertical
	DrawRectangle(ledWidth * 2 + offset + hLedLength, ledWidth * 2,
			ledWidth, vLedLength, ledColors[5]);
	// Bottomright vertical
	DrawRectangle(ledWidth * 2 + offset + hLedLength, ledWidth * 3 + vLedLength,
			ledWidth, vLedLength, ledColors[6]);
	offset += 3 * ledWidth + hLedLength;
	return offset;
}

int main(void)
{
	// TODO: add more colors maybe?
	Color ledOptions[] = {GREEN, BLUE, RED, ORANGE, PURPLE, YELLOW, WHITE,
		MAGENTA};
	int optionSize = sizeof ledOptions / sizeof ledOptions[0];
	int selectedColor = 0;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(640, 180, u8"Clock. Press space to change color.");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		// Might not be perfect.
		int screenwidth = GetScreenWidth();
		int screenheight = GetScreenHeight();
		int ledWidth = screenwidth / (23 * 2);
		int hLedLength = (screenwidth - ledWidth * 23) / 6;
		int vLedLength = (screenheight - ledWidth * 5) / 2;

		time_t curtime = time(NULL);
		struct tm *tmtime = localtime(&curtime);
		
		BeginDrawing();
		{
			if (IsKeyPressed(KEY_SPACE)) {
				if (selectedColor == optionSize - 1)
					selectedColor = 0;
				else
					selectedColor++;
			}
			ClearBackground(BLACK);
			// Hours.
			int offset = drawDigit(0, hLedLength, vLedLength, ledWidth,
					tmtime->tm_hour / 10, ledOptions[selectedColor]);
			offset = drawDigit(offset, hLedLength, vLedLength, ledWidth,
					tmtime->tm_hour % 10, ledOptions[selectedColor]);
			offset = drawSeparator(offset, ledWidth, screenheight, ledOptions[selectedColor]);
			// Minutes.
			offset = drawDigit(offset, hLedLength, vLedLength, ledWidth, 
					tmtime->tm_min / 10, ledOptions[selectedColor]);
			offset = drawDigit(offset, hLedLength, vLedLength, ledWidth, 
					tmtime->tm_min % 10, ledOptions[selectedColor]);
			offset = drawSeparator(offset, ledWidth, screenheight, ledOptions[selectedColor]);
			// Seconds.
			offset = drawDigit(offset, hLedLength, vLedLength, ledWidth,
					tmtime->tm_sec / 10, ledOptions[selectedColor]);
			offset = drawDigit(offset, hLedLength, vLedLength, ledWidth,
					tmtime->tm_sec % 10, ledOptions[selectedColor]);
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
