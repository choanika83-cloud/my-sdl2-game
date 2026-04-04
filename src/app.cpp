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

