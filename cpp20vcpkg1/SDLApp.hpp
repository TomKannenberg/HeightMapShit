#ifndef SDL_APP_H
#define SDL_APP_H
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#pragma comment(lib, "SDL2-static.lib")
#pragma comment(lib, "SetupAPI.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Imm32.lib")
#pragma comment(lib, "Version.lib")

class SDLApp {
public:
    SDLApp();
    bool init(const char* title, int width, int height);
    SDL_Renderer* getRenderer() const;
    SDL_Window* getWindow() const;
    void cleanup();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif // SDL_APP_H
