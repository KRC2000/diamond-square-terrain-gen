#include "diamond_square_algo.h"

#include <assert.h>
#include <time.h>

// https://janert.me/blog/2022/the-diamond-square-algorithm-for-terrain-generation/

float** GenHMapDiamondSquare(size_t size, float noiseMagnitude, float smoothFactor) {
	srand(time(NULL));

	assert(size >= 3);
	assert(isPowerOfTwo(size-1));

	float** arr = malloc(sizeof(float*) * size);
	for (size_t i = 0; i < size; i++)
		arr[i] = calloc(size, sizeof(float));

	// Step 1: Init corners with random values
	arr[0][0] = (float)rand() / RAND_MAX;
	arr[size-1][0] = (float)rand() / RAND_MAX;
	arr[0][size-1] = (float)rand() / RAND_MAX;
	arr[size-1][size-1] = (float)rand() / RAND_MAX;

	size_t step = size - 1;
	for (size_t i = 0; step > 1; i++) {
		if (i % 2 != 0) squareStep(arr, size, &step, noiseMagnitude);
		else diamondStep(arr, size, &step, noiseMagnitude);
		noiseMagnitude /= smoothFactor;
	}

	return arr;
}

void FreeHMap(float** map, size_t size) {
	if (map == NULL) return;
	for (size_t i = 0; i < size; i++) {
		if (map[i] == NULL) continue;
		free(map[i]);
	}
	free(map);
}

static void clamp(float* f) {
	if (*f < 0) *f = 0;
	if (*f > 1.f) *f = 1.f;
}

static float getNoiseValue(float magnitude) {
	float value = magnitude * ((float)rand() / RAND_MAX);
	value *= (rand() % 2) ? 1 : -1;

	return value;
}

static bool isPowerOfTwo(size_t x) {
	return (x != 0) && ((x & (x - 1)) == 0);
}

static float getSquareNodeValue(size_t x, size_t y, float** map, size_t step, size_t mapSize) {
	unsigned char count = 0;
	float sum = 0;

	if (x != 0) { sum += map[x - step][y]; count++; }
	if (x != mapSize-1) { sum += map[x + step][y]; count++; }
	if (y != 0) { sum += map[x][y - step]; count++; }
	if (y != mapSize-1) { sum += map[x][y + step]; count++; }

	return sum / count;
}

static void squareStep(float** map, size_t mapSize, size_t* step, float magnitude) {
	*step /= 2;

	for (size_t y = 0; y < mapSize; y += *step) {
		for (size_t x = *step - ((y / *step) % 2) * *step; x < mapSize; x += *step * 2) {
			map[x][y] = getSquareNodeValue(x, y, map, *step, mapSize) + getNoiseValue(magnitude);
			clamp(&map[x][y]);
		}
	}
}

static void diamondStep(float** map, size_t mapSize, size_t* step, float magnitude) {
	for (size_t x = 0; x < mapSize-1; x += *step) {
		for (size_t y = 0; y < mapSize-1; y += *step) {
			float f1 = map[x][y];
			float f2 = map[x+*step][y];
			float f3 = map[x][y+*step];
			float f4 = map[x+*step][y+*step];
			float average = (f1 + f2 + f3 + f4) / 4;
			map[x + *step/2][y + *step/2] = average + getNoiseValue(magnitude);
			clamp(&map[x + *step/2][y + *step/2]);
		}
	}
}

