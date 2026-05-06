#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include<cmath>
using namespace std;
// function to draw a snake
 void drawSnake(SDL_Renderer* renderer, int X, int Y) {
  
  int count = 0;
  while (count < 5)
  {
    
    SDL_Rect segment = {X, Y, 20, 20};
    SDL_RenderFillRect(renderer, &segment);

    if(count == 0)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); //head in blue

    else
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //other parts in white
 
    count++;
    X += 21;
    
  }
}    
    


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isRunning = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        
        
        drawSnake(renderer, 400, 300);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}