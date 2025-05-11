#ifndef NOISE_RENDERER_H
#define NOISE_RENDERER_H

#include "CustomTerrainNoise.hpp"
#include "CustomTerrainRivers.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <stb_image_write.h>  // Include STB Image Write for saving

#include <filesystem>  // C++17

namespace fs = std::filesystem;

static std::string generateUniqueFilename(const std::string& baseName, const std::string& extension) {
    int index = 1;
    std::string filename;
    do {
        filename = baseName + "_" + std::to_string(index) + "." + extension;
        ++index;
    } while (fs::exists(filename));
    return filename;
}

class NoiseRenderer {
public:
    NoiseRenderer(SDL_Renderer* renderer);
    void renderNoise(int width, int height);

private:
    SDL_Renderer* renderer;
    CustomTerrainRivers noiseMaker;
    CustomTerrainRivers riverMaker;
    bool imageSaved;  // Flag to track if image is saved already
};

#endif // NOISE_RENDERER_H
