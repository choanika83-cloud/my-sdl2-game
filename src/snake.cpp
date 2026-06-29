#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<SDL_ttf.h>
#include<string>

using namespace std;

// --- Constants & Globals ---
const int screenWidth = 840;
const int screenHeight = 640;
vector<SDL_Rect> snakCoordinate;
int score = 0;
int w;
int h;
SDL_Rect segment_food;
TTF_Font* font = nullptr;
SDL_Texture* scoreText = nullptr;
SDL_Texture* messageText = nullptr;
SDL_Rect scoreRect = {10, 605, 120, 30};

// ----Randomly renders food---
void randomRect(SDL_Renderer* renderer)
{ 
w = 60 + (rand() % 37) * 20; 
h = 60 + (rand() % 27) * 20;

 segment_food = {w, h, 20, 20};
 }

void initializeSnake()
{
 snakCoordinate.clear();
// ---head at 400, 300----
 snakCoordinate.push_back({400, 300, 20, 20}); 
// ---other body parts---
 snakCoordinate.push_back({380, 300, 20, 20});
 snakCoordinate.push_back({360, 300, 20, 20});  
}

//-----Movement Function-------
void snakeMovement(vector<SDL_Rect>& body, SDL_Renderer* renderer, bool &gameOver)
{
  if(gameOver) 
    return;  
 SDL_Rect head = body.front();

//------ Handle Input for Snake------
 const Uint8* state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_UP]) head.y -= 20;

else if(state[SDL_SCANCODE_DOWN]) head.y += 20;

else if(state[SDL_SCANCODE_LEFT]) head.x -= 20;

else if(state[SDL_SCANCODE_RIGHT]) head.x += 20;

if (body.size() > 1 && head.x == body[1].x && head.y == body[1].y) // prevent turn in opposite direction
    return;


if(state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_RIGHT]) {

body.insert(body.begin(), head); 
 
if(SDL_HasIntersection(&head, &segment_food)) {
randomRect(renderer);
 score += 1;
 string stringScore = "SCORE: " + to_string(score);
SDL_Color white = {255, 255, 255, 255};
SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, stringScore.c_str(), white);


if(scoreSurface != nullptr) {
    if(scoreText != nullptr) {
SDL_DestroyTexture(scoreText);}
scoreText = SDL_CreateTextureFromSurface(renderer, scoreSurface);
SDL_FreeSurface(scoreSurface);
}}

 else {
    body.pop_back();
}

//------ Collsion Detection--------

if(head.x <= 40 || head.y <= 40 || head.x >= 800 || head.y >= 600) {
    gameOver = true;
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* messageSurface = TTF_RenderText_Solid(font, "GAME OVER", white);
    messageText = SDL_CreateTextureFromSurface(renderer, messageSurface);
    SDL_FreeSurface(messageSurface);
     string stringScore = "SCORE: " + to_string(score);
SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, stringScore.c_str(), white);


if(scoreSurface != nullptr) {
    if(scoreText != nullptr) {
SDL_DestroyTexture(scoreText);}
scoreText = SDL_CreateTextureFromSurface(renderer, scoreSurface);
SDL_FreeSurface(scoreSurface);
    }
}

for(int i = 1; i < body.size(); i++) {
    if(SDL_HasIntersection(&head, &body[i])) {
        gameOver = true;
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* messageSurface = TTF_RenderText_Solid(font, "GAME OVER", white);
    messageText = SDL_CreateTextureFromSurface(renderer, messageSurface);
    SDL_FreeSurface(messageSurface);
    }
        
    }
}
}

//------Function to Draw a Snake------
void drawSnake(SDL_Renderer* renderer, const vector<SDL_Rect>& body) {
 for(int i = 0; i < body.size(); i++) {
    if(i == 0)
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // head in blue

    else
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // other parts in white
 
 SDL_RenderFillRect(renderer, &body[i]);
 }
}

// --- Main Loop ---
int main(int argc, char* argv[]) {
//---- Initialize game window & font-----
 srand(time(0));
 SDL_Init(SDL_INIT_VIDEO);
 TTF_Init();
 font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 24);
 if(font == nullptr)
     cout << "font error" << TTF_GetError() << '\n';    
 SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);    
SDL_Color white = {255, 255, 255, 255};
SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, "SCORE: 0", white);
 scoreText = SDL_CreateTextureFromSurface(renderer, scoreSurface);
SDL_FreeSurface(scoreSurface);
 initializeSnake(); 
 randomRect(renderer);
 
 bool isRunning = true;
 bool gameOver = false;
  SDL_Event event;
 while (isRunning) {
 while (SDL_PollEvent(&event)) {
 if (event.type == SDL_QUIT) isRunning = false;
 }

 SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
 SDL_RenderClear(renderer);

if(!gameOver) 
{
    drawSnake( renderer, snakCoordinate);
    SDL_RenderCopy(renderer, scoreText, nullptr, &scoreRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, 40, 600, 800, 600);
    SDL_RenderDrawLine(renderer, 40, 40, 40, 600);
    SDL_RenderDrawLine(renderer, 40, 40, 800, 40);
    SDL_RenderDrawLine(renderer, 800, 40, 800, 600);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Draw the food
    SDL_RenderFillRect(renderer, &segment_food);

}

else 
{
    SDL_Delay(60);
    SDL_Rect messageRect = {300, 300, 200, 50};
    SDL_Rect scoreRect = {300, 350, 200, 50};
    SDL_RenderCopy(renderer, messageText, nullptr, &messageRect);
    SDL_RenderCopy(renderer, scoreText, nullptr, &scoreRect);    
}
 
SDL_Delay(40);
 snakeMovement(snakCoordinate, renderer, gameOver);
 SDL_RenderPresent(renderer);
 }
 
 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 SDL_Quit();
 return 0;
}

