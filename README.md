
# Diamond-Square Terrain Generation Algorithm

## Demonstration
Demo implemented using Raylib

https://github.com/user-attachments/assets/8fc5831c-6954-4ca7-93a8-3a518dec6272



## How To Utilize

1. Copy `diamond_square_algo.h` and `diamond_square_algo.c` into your project.
2. Include `diamond_square_algo.h`.

```c
#include "diamond_square_algo.h"
```

3. Generate a map.

```c
// Map can only be square - hence map size represented with one value.
// Map size should be one greater than an integer power of two: 
// n = 1+2^k, where k is a positive integer.
// That means that valid map sizes are: 9(8+1), 17(16+1), 33(32+1), 
// 65(64+1), 129(128+1), 257(256+1), 513(512+1), ...
unsigned long mapSize = 256 + 1;

// Magnitude of the random noise
float magnitude = 0.7;

// Speed of magnitude decline
float smoothing = 1.3;

// Returns a 2D array where each cell value is in the range from 0.f to 1.f
float** map = GenHMapDiamondSquare(mapSize, magnitude, smoothing);
```

4. Use generated map for your needs. For example draw it.

```c
for (size_t x = 0; x < mapSize; x++) {
    for (size_t y = 0; y < mapSize; y++)
        DrawPixel(x, y, (Color){255 * map[x][y], 255 * map[x][y], 255 * map[x][y], 255});
}
```


