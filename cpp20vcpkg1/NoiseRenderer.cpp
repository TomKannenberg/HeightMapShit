#include "NoiseRenderer.hpp"
#include <SDL2/SDL.h>
#include <iostream>

NoiseRenderer::NoiseRenderer(SDL_Renderer* renderer)
    : renderer(renderer), imageSaved(false) {}

void NoiseRenderer::renderNoise(int width, int height) {
    float scale = 0.02f;

    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        width,
        height
    );

    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return;
    }

    void* pixels = nullptr;
    int pitch = 0;

    if (SDL_LockTexture(texture, nullptr, &pixels, &pitch) != 0) {
        std::cerr << "Failed to lock texture: " << SDL_GetError() << std::endl;
        SDL_DestroyTexture(texture);
        return;
    }

    Uint32* pixelBuffer = static_cast<Uint32*>(pixels);
    int rowLength = pitch / 4;

    // Render noise to the texture
    riverMaker.generateRivers(8);

    // Retrieve the flow map where rivers are generated
    const auto& riverFlow = riverMaker.getRiverFlow();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float value = riverFlow[y][x];
            Uint8 color = static_cast<Uint8>((value + 1.0f) * 127.5f);
            pixelBuffer[y * rowLength + x] = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), color, color, color, 255);
        }
    }

    // Save the image before unlocking and destroying the texture
    if (!imageSaved) {
        int bufferSize = width * height * 4;
        unsigned char* imageData = new unsigned char[bufferSize];

        for (int i = 0; i < width * height; ++i) {
            Uint32 pixel = pixelBuffer[i];

            imageData[i * 4 + 3] = (pixel & 0xFF);         // R
            imageData[i * 4 + 2] = (pixel >> 8) & 0xFF;    // G
            imageData[i * 4 + 1] = (pixel >> 16) & 0xFF;   // B
            imageData[i * 4 + 0] = (pixel >> 24) & 0xFF;   // A
        }

        std::string filename = generateUniqueFilename("terrain_noise", "png");

        if (stbi_write_png(filename.c_str(), width, height, 4, imageData, width * 4)) {
            std::cout << "Image saved as " << filename << std::endl;
        } else {
            std::cerr << "Failed to save image." << std::endl;
        }

        delete[] imageData;
        imageSaved = true;
    }

    SDL_UnlockTexture(texture);

    // Render texture to the screen
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_DestroyTexture(texture);

    std::cout << "Rendered noise to texture. " << (width * height) << " pixels." << std::endl;
}