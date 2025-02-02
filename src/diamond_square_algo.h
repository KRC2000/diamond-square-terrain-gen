#ifndef DIAMOND_SQUARE_ALGO_H
#define DIAMOND_SQUARE_ALGO_H

#include <stdlib.h>
#include <stdbool.h>

float** GenHMapDiamondSquare(size_t size, float noiseMagnitude, float smoothFactor);
void FreeHMap(float** map, size_t size);

static void clamp(float* f);
static float getNoiseValue(float magnitude);
static bool isPowerOfTwo(size_t x);
static float getSquareNodeValue(size_t x, size_t y, float** map, size_t step, size_t mapSize);
static void squareStep(float** map, size_t mapSize, size_t* step, float magnitude);
static void diamondStep(float** map, size_t mapSize, size_t* step, float magnitude);

#endif
