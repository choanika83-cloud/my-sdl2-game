#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // 1. Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 2. Create the Window
    // In SDL2, we use SDL_WINDOWPOS_UNDEFINED and a 'flags' argument (like SDL_WINDOW_SHOWN)
    SDL_Window* window = SDL_CreateWindow(
        "Hello SDL2 Window", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        800, 300, 
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 3. Main Loop
    bool isRunning = true;
    SDL_Event event;
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            // In SDL2, it is SDL_QUIT (not SDL_EVENT_QUIT)
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }
    }

    // 4. Cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}