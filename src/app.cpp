#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Function to draw a circle 

void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, bool isColliding) {
    int thickness = 2; 
    
    // Visual effect of collision: Red if colliding, White if safe
    if (isColliding) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
    
    for (int w = 0; w < radius * 2 + thickness; w++) {
        for (int h = 0; h < radius * 2 + thickness; h++) {
            int dx = radius - w; 
            int dy = radius - h;
            
            // Calculate distance squared
            int distSq = (dx * dx + dy * dy);
            
            // Check if the pixel is on the edge
            if (distSq >= (radius - thickness) * (radius - thickness) && 
                distSq <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Circles Collision", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Circle 1: Moves left to right continuously
    float c1X = 0.0;
    float c1Y = 300.0;
    int c1Radius = 40;
    float c1Speed = 3.0f;

    // Circle 2: Controlled by user (Starting at center width, top)
    float c2X = SCREEN_WIDTH / 2.0f;
    float c2Y = 0.0f; 
    int c2Radius = 40;
    float c2Speed = 5.0f;

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isRunning = false;
        }

        // Handle input for circle 2
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_UP])    c2Y -= c2Speed;
        if (state[SDL_SCANCODE_DOWN])  c2Y += c2Speed;
        if (state[SDL_SCANCODE_LEFT])  c2X -= c2Speed;
        if (state[SDL_SCANCODE_RIGHT]) c2X += c2Speed;

        // Update circle (Automated Movement)
        c1X += c1Speed;
        // If it goes off the right edge, wrap it back to the left edge
        if (c1X > SCREEN_WIDTH + c1Radius) {
            c1X = -c1Radius;
        }

        // Ditermine collision
        // Distance formula: (x2 - x1)^2 + (y2 - y1)^2
        float dx = c2X - c1X;
        float dy = c2Y - c1Y;
        float distanceSquared = (dx * dx) + (dy * dy);
        
        // They collide if distance is less than the sum of their radii
        int radiusSum = c1Radius + c2Radius;
        bool isColliding = distanceSquared <= (radiusSum * radiusSum);

        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw both circles passing the collision state
        drawCircle(renderer, (int)c1X, (int)c1Y, c1Radius, isColliding);
        drawCircle(renderer, (int)c2X, (int)c2Y, c2Radius, isColliding);

        SDL_RenderPresent(renderer);

        // Frame rate limit
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
