#include "CustomTerrainNoise.hpp"
#include <cmath>
#include <algorithm>
#include <cstdlib>

CustomTerrainNoise::CustomTerrainNoise() {
    permute.resize(512);
    for (int i = 0; i < 256; ++i)
        permute[i] = i;

    for (int i = 0; i < 256; ++i) {
        int j = rand() % 256;
        std::swap(permute[i], permute[j]);
        permute[i + 256] = permute[i];
    }
}

float CustomTerrainNoise::makeNoise(float x, float y) {
    float base = fractalNoise(x, y, 5, 0.55f);         // Slightly smoother persistence
    float warped = domainWarp(x, y, base * 0.3f);      // Lowered warp amount
    return applyArtisticWarp(warped);
}

float CustomTerrainNoise::generatePerlinNoise(float x, float y) {
    int X = static_cast<int>(floor(x)) & 255;
    int Y = static_cast<int>(floor(y)) & 255;

    x -= floor(x);
    y -= floor(y);

    float u = fade(x);
    float v = fade(y);

    int aa = permute[permute[X] + Y];
    int ab = permute[permute[X] + Y + 1];
    int ba = permute[permute[X + 1] + Y];
    int bb = permute[permute[X + 1] + Y + 1];

    float gradAA = grad(aa, x, y);
    float gradAB = grad(ab, x, y - 1);
    float gradBA = grad(ba, x - 1, y);
    float gradBB = grad(bb, x - 1, y - 1);

    float lerpX1 = lerp(gradAA, gradBA, u);
    float lerpX2 = lerp(gradAB, gradBB, u);

    return lerp(lerpX1, lerpX2, v);
}

float CustomTerrainNoise::fractalNoise(float x, float y, int octaves, float persistence) {
    float total = 0.0f;
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float maxAmplitude = 0.0f;

    for (int i = 0; i < octaves; ++i) {
        total += generatePerlinNoise(x * frequency, y * frequency) * amplitude;
        maxAmplitude += amplitude;
        amplitude *= persistence;
        frequency *= 2.0f;
    }

    return total / maxAmplitude;
}

float CustomTerrainNoise::domainWarp(float x, float y, float warpAmount) {
    float qx = generatePerlinNoise(x + 3.0f, y + 3.0f);
    float qy = generatePerlinNoise(x - 3.0f, y - 3.0f);

    float rx = generatePerlinNoise(x + warpAmount * qx, y + warpAmount * qy);
    float ry = generatePerlinNoise(x + warpAmount * qy, y + warpAmount * qx);

    float final = generatePerlinNoise(x + warpAmount * rx, y + warpAmount * ry);
    return std::clamp(final * 0.5f + 0.5f, 0.0f, 1.0f);  // Keep in [0,1] range
}

float CustomTerrainNoise::applyArtisticWarp(float value) {
    // Value is assumed to be in [0, 1]
    value = std::pow(value, 1.3f);                     // Gentle contrast
    return value * 2.0f - 1.0f;                        // Normalize to [-1, 1]
}

float CustomTerrainNoise::fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float CustomTerrainNoise::lerp(float a, float b, float t) {
    return a + t * (b - a);
}

float CustomTerrainNoise::grad(int hash, float x, float y) {
    int h = hash & 7;
    float u = h < 4 ? x : y;
    float v = h < 4 ? y : x;
    return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}
