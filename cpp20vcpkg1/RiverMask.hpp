#ifndef RIVER_MASK_H
#define RIVER_MASK_H

#include "CustomTerrainNoise.hpp"
#include <cmath>
#include <algorithm>

class RiverMask {
public:
    explicit RiverMask(CustomTerrainNoise& noiseGen);

    // Returns a value from 0.0 to 1.0 indicating river strength
    float getRiverMask(float x, float y, float base, float scale = 0.02f);

private:
    CustomTerrainNoise& noise;

    // Inverted ridge function to produce valleys
    float ridgeNoise(float x, float y, float base);

    // Optional threshold function to sharpen rivers
    float threshold(float value, float edge);
};

#endif // RIVER_MASK_H
