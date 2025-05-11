#include "CustomTerrainRivers.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

CustomTerrainRivers::CustomTerrainRivers(int width, int height)
    : width(width), height(height), flowMap(height, std::vector<float>(width, 0.0f)) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void CustomTerrainRivers::generateRivers(int numDroplets) {
    for (int i = 0; i < numDroplets; ++i) {
        int x = std::rand() % width;
        int y = std::rand() % height;

        // Simulate the river flowing from a starting point
        simulateDroplet(x, y);
    }

    // Normalize flow map values to range [0, 1]
    float maxFlow = 0.0f;
    for (const auto& row : flowMap)
        for (float v : row)
            if (v > maxFlow) maxFlow = v;

    if (maxFlow > 0.0f) {
        for (auto& row : flowMap)
            for (float& v : row)
                v /= maxFlow;
    }
}

void CustomTerrainRivers::simulateDroplet(int x, int y) {
    for (int steps = 0; steps < 200; ++steps) {
        if (x < 1 || y < 1 || x >= width - 1 || y >= height - 1)
            break;

        flowMap[y][x] += 1.0f; // Add to river flow

        auto [nx, ny] = getLowestNeighbor(x, y);
        if (nx == x && ny == y)
            break; // No more flow (we're at the lowest point)

        x = nx;
        y = ny;
    }
}

std::pair<int, int> CustomTerrainRivers::getLowestNeighbor(int x, int y) {
    int bestX = x;
    int bestY = y;

    // Compare all 8 neighbors
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            // Stay within bounds
            if (nx < 0 || ny < 0 || nx >= width || ny >= height) continue;

            // Check which neighbor is "lower" (in terms of coordinate value)
            if ((ny > bestY) || (ny == bestY && nx > bestX)) {
                bestX = nx;
                bestY = ny;
            }
        }
    }

    return { bestX, bestY };
}

const std::vector<std::vector<float>>& CustomTerrainRivers::getRiverFlow() const {
    return flowMap;
}
