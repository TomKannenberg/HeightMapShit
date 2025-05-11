#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "SDLApp.hpp"
#include "NoiseRenderer.hpp"

int main(int argc, char* argv[]) {
    SDLApp app;
    if (!app.init("Noise Rendering", 512, 512)) {
        while (1);
    }

    NoiseRenderer noiseRenderer(app.getRenderer());
    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(app.getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(app.getRenderer());
        noiseRenderer.renderNoise(512, 512);
        SDL_RenderPresent(app.getRenderer());
    }

    app.cleanup();
    while (1);
}
