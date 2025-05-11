#ifndef CUSTOM_TERRAIN_RIVERS_H
#define CUSTOM_TERRAIN_RIVERS_H

#include <vector>

class CustomTerrainRivers {
public:
    CustomTerrainRivers(int width = 512, int height = 512);

    // Generate rivers based purely on x, y coordinates
    void generateRivers(int numDroplets = 10000);

    // Get the river flow map
    const std::vector<std::vector<float>>& getRiverFlow() const;

private:
    int width, height;
    std::vector<std::vector<float>> flowMap;  // River flow map

    // Simulate a droplet flowing downhill based purely on x, y coordinates
    void simulateDroplet(int startX, int startY);

    // Get the lowest neighbor by comparing the surrounding x, y
    std::pair<int, int> getLowestNeighbor(int x, int y);
};

#endif // CUSTOM_TERRAIN_RIVERS_H
