
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;


const int screenWidth = 800;
const int screenHight = 600;
vector<SDL_Rect> snakCoordinate;
int Yspeed = 1;
int Xspeed = 1;
int X;
int Y;

void initializeSnake()
{
    snakCoordinate.clear();
    // head at 400, 300
    snakCoordinate.push_back({400, 300, 20, 20}); 
    // other body parts
    snakCoordinate.push_back({380, 300, 20, 20});
    snakCoordinate.push_back({360, 300, 20, 20});   
}

//movement function
void snakeMovement(vector<SDL_Rect>& body)
{
    SDL_Rect head = body.front();
     // handle input for snake
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_UP]) head.y -= 20;
        if(state[SDL_SCANCODE_DOWN]) head.y += 20;
        if(state[SDL_SCANCODE_LEFT]) head.x -= 20;
        if(state[SDL_SCANCODE_RIGHT]) head.x += 20;

        if(state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_RIGHT]) {
            body.insert(body.begin(), head);
            body.pop_back();
        }       
}

// function to draw a snake
 void drawSnake(SDL_Renderer* renderer, const vector<SDL_Rect>& body) {
    for(int i = 0; i < body.size(); i++) {
         if(i == 0)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // head in blue

    else
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // other parts in white
    
    SDL_RenderFillRect(renderer, &body[i]);
  }
}

void randomRect(SDL_Renderer* renderer, int* w, int* h)
{
    SDL_Rect segment_food;
    if(*w < screenWidth && *h < screenHight)
    {
        SDL_Rect segment_food = {*w, *h, 20, 20};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // food in red
        SDL_RenderFillRect(renderer, &segment_food);
    }
 }
     
int main(int argc, char* argv[]) {
    srand(time(0));
    int w = (rand() % (screenWidth / 21)) * 21;
    int h = (rand() % (screenHight / 21)) * 21;
    
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHight, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool isRunning = true;
    SDL_Event event;
    initializeSnake(); 
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isRunning = false;
           
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_Delay(16);
        drawSnake( renderer,  snakCoordinate);
        randomRect(renderer, &w, &h);
        snakeMovement(snakCoordinate);
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}