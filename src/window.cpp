#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

// Constants & Globals
const int screenWidth = 840;
const int screenHeight = 640;
vector<SDL_Rect> body;
int dx = 20, dy = 0; // FIXED: Using velocity variables to ensure continuous movement
SDL_Rect food;
int score = 0;
TTF_Font* font = nullptr;

// Helper: Spawn food inside boundaries
void spawnFood() {
    // FIXED: Adjusted math to ensure food never spawns outside the wall borders
    food.x = 60 + (rand() % 37) * 20;
    food.y = 60 + (rand() % 27) * 20;
    food.w = 20; food.h = 20;
}

// Logic: Update Snake Position
void updateSnake(bool &gameOver) {
    if (gameOver) return;

    const Uint8* state = SDL_GetKeyboardState(NULL);
    
    // FIXED: Perpendicular movement check (&& dy == 0) prevents 180-degree self-collision turns
    if (state[SDL_SCANCODE_UP] && dy == 0)    { dx = 0;  dy = -20; }
    else if (state[SDL_SCANCODE_DOWN] && dy == 0)  { dx = 0;  dy = 20;  }
    else if (state[SDL_SCANCODE_LEFT] && dx == 0)  { dx = -20; dy = 0;  }
    else if (state[SDL_SCANCODE_RIGHT] && dx == 0) { dx = 20;  dy = 0;  }

    // FIXED: Removed the giant 'if' block that required a key to be held. 
    // Now the head updates every frame based on the current velocity (dx, dy).
    SDL_Rect nextHead = {body.front().x + dx, body.front().y + dy, 20, 20};

    // FIXED: Boundary logic refined to match the drawn lines at 40 and 800/600
    if (nextHead.x < 40 || nextHead.x >= 800 || nextHead.y < 40 || nextHead.y >= 600) {
        gameOver = true; return;
    }

    // FIXED: Collision logic now checks against the new position BEFORE finalizing the move
    for (const auto& part : body) {
        if (nextHead.x == part.x && nextHead.y == part.y) {
            gameOver = true; return;
        }
    }

    // Movement: Insert head and handle tail growth
    body.insert(body.begin(), nextHead);
    if (SDL_HasIntersection(&nextHead, &food)) {
        score++;
        spawnFood();
    } else {
        body.pop_back(); // Remove tail if no food eaten
    }
}

int main(int argc, char* argv[]) {
    srand(time(0));
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 24);
    
    SDL_Window* window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initial state
    body.push_back({400, 300, 20, 20});
    spawnFood();

    bool isRunning = true, gameOver = false;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) if (event.type == SDL_QUIT) isRunning = false;

        // FIXED: updateSnake is now called every frame regardless of key input
        updateSnake(gameOver);

        // Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw Walls
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, 40, 40, 800, 40);
        SDL_RenderDrawLine(renderer, 40, 600, 800, 600);
        SDL_RenderDrawLine(renderer, 40, 40, 40, 600);
        SDL_RenderDrawLine(renderer, 800, 40, 800, 600);

        // Draw Food
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &food);

        // Draw Snake
        for (size_t i = 0; i < body.size(); ++i) {
            SDL_SetRenderDrawColor(renderer, (i == 0 ? 0 : 255), 255, 255, 255);
            SDL_RenderFillRect(renderer, &body[i]);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100); 
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}