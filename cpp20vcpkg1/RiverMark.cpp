#include "RiverMask.hpp"

RiverMask::RiverMask(CustomTerrainNoise& noiseGen)
    : noise(noiseGen) {}

float RiverMask::ridgeNoise(float x, float y, float base) {
    // Ridged noise for river channels
    base = 1.0f - std::abs(base); // Ridge
    return base * base; // Sharpen ridges
}

float RiverMask::threshold(float value, float edge) {
    return value > edge ? 1.0f : 0.0f;
}

float RiverMask::getRiverMask(float x, float y, float base, float scale) {
    // Primary river mask using low-frequency ridged noise
    float riverVal = ridgeNoise(x, y, base);

    // Optional: Modulate with base terrain to keep rivers at lower altitudes
    float terrainInfluence = 1.0f - std::clamp(base, 0.0f, 1.0f);

    // Blend both factors to shape river presence
    float mask = riverVal * terrainInfluence;

    // Sharpen river edges
    return threshold(mask, 0.15f); // Increase threshold for narrower rivers
}
