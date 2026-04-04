#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;
// function for drawing using general equation of a circle
 void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    int thickness = 1; 
    
    for (int i = 0; i < radius * 2 + thickness; i++) {
        for (int j = 0; j < radius * 2 + thickness; j++) {
            int dx = radius - i; 
            int dy = radius - j;
            
            // Calculation of distance squared
            int Distsq = (dx * dx + dy * dy);
            
            // Check if the pixel is on the "edge"
            // We check if it's between (r-1)^2 and (r)^2
            if (Distsq >= (radius - thickness) * (radius - thickness) && 
                Distsq <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Circle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isRunning = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the outline in white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        drawCircle(renderer, 400, 300, 100);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

