#include <stdio.h>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "diamond_square_algo.h"

void regenTexture(RenderTexture2D* rt, float** map, size_t res) {
	UnloadRenderTexture(*rt);
	*rt = LoadRenderTexture(res, res);
	BeginTextureMode(*rt);
	for (size_t x = 0; x < res; x++) {
		for (size_t y = 0; y < res; y++) {
			DrawPixel(x, y,
					  (Color){255 * map[x][y], 255 * map[x][y], 255 * map[x][y],
							  255});
		}
	}
	EndTextureMode();
}

int main() {
	int resolutions[7] = {9, 17, 33, 65, 129, 257, 513};


	int resId = 4;
	int prevResId = resId;
	bool resolutionEditMode = false;
	float magnitude = 0;
	float smoothing = 1;
	float prevMagnitude = magnitude;
	float prevSmoothing = smoothing;

	int screenSize = 512 + 1;
	InitWindow(screenSize, screenSize, "Gen algo test");

	float** map = GenHMapDiamondSquare(resolutions[resId], magnitude, smoothing);

	RenderTexture2D rt; 
	regenTexture(&rt, map, resolutions[resId]);

	uint pixSize = screenSize / resolutions[resId];

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);

		DrawTexturePro(rt.texture, (Rectangle){0, 0, rt.texture.width, rt.texture.height}, (Rectangle){0, 0, screenSize, screenSize}, (Vector2){0}, 0, WHITE);

		if (GuiDropdownBox((Rectangle){0, 0, 300, 30},
						   "9x9;17x17;33x33;65x65;129x129;257x257;513x513",
						   &resId, resolutionEditMode)) {
			resolutionEditMode = !resolutionEditMode;
			if (resId != prevResId) {
				FreeHMap(map, resolutions[prevResId]);
				pixSize = screenSize / resolutions[resId];
				map = GenHMapDiamondSquare(resolutions[resId], magnitude,
										   smoothing);
				regenTexture(&rt, map, resolutions[resId]);
				prevResId = resId;
			}
		}

		if (GuiButton((Rectangle){(float)screenSize / 2 - 50, screenSize - 110, 100, 30}, "Regen")) {
			FreeHMap(map, resolutions[resId]);
			map = GenHMapDiamondSquare(resolutions[resId], magnitude, smoothing);
			regenTexture(&rt, map, resolutions[resId]);
		}

		char str[10];
		sprintf(str, "%f", magnitude);
		GuiSliderBar(
			(Rectangle){(float)screenSize / 2 - 75, screenSize - 30, 150, 30},
			"Noise Magnitude(0-1)", str, &magnitude, 0, 1);
		sprintf(str, "%f", smoothing);
		GuiSliderBar(
			(Rectangle){(float)screenSize / 2 - 75, screenSize - 60, 150, 30},
			"Smoothing Factor(0-3)", str, &smoothing, 0, 3);
		if (magnitude != prevMagnitude || smoothing != prevSmoothing) {
			FreeHMap(map, resolutions[resId]);
			map = GenHMapDiamondSquare(resolutions[resId], magnitude, smoothing);
			regenTexture(&rt, map, resolutions[resId]);
			prevMagnitude = magnitude;
			prevSmoothing = smoothing;
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
