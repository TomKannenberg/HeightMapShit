#ifndef CUSTOM_TERRAIN_NOISE_H
#define CUSTOM_TERRAIN_NOISE_H

#include <vector>

class CustomTerrainNoise {
public:
    CustomTerrainNoise();
    float makeNoise(float x, float y);

private:
    std::vector<int> permute;

    // Core Perlin noise generation
    float generatePerlinNoise(float x, float y);

    // Multi-octave smooth noise
    float fractalNoise(float x, float y, int octaves, float persistence);

    // Artistic warping
    float domainWarp(float x, float y, float warpAmount);
    float applyArtisticWarp(float value);

    // Utility functions
    float fade(float t);
    float lerp(float a, float b, float t);
    float grad(int hash, float x, float y);
};

#endif // CUSTOM_TERRAIN_NOISE_H
