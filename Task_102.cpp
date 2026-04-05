#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

// Screen constants for collision checking
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Function for drawing circle using general equation of a circle
 void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    int thickness = 1; 
    
    for (int w = 0; w < radius * 2 + thickness; w++) {
        for (int h = 0; h < radius * 2 + thickness; h++) {
            int dx = radius - w; 
            int dy = radius - h;
            
            // Calculation of distance squared
            int Distsq = (dx * dx + dy * dy);
            
            // Check if the pixel is on the edge
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
    SDL_Window* window = SDL_CreateWindow("Growing Circle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Circle animation variables
    int centerX = SCREEN_WIDTH / 2 ;
    int centerY = SCREEN_HEIGHT / 2;
    float initialRadius = 10.0f;
    float currentRadius = initialRadius;
    float growthSpeed = 0.5f;

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isRunning = false;
        }

    // Increase the radius
        currentRadius += growthSpeed;

    // Reset if it hits window boundaries
    if (400 + currentRadius >= 800 || 400 - currentRadius <= 0 ||
        300 + currentRadius >= 600 || 300 - currentRadius <= 0) {
        currentRadius = 10.0f; 
    }
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to Black
    SDL_RenderClear(renderer);                      // Clear the whole screen

    // The drawing
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set color to White
    drawCircle(renderer, 400, 300, (int)currentRadius);   // Draw the new circle

    // Display circle
    SDL_RenderPresent(renderer);

        // Frame rate limit so the growth is visible
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

