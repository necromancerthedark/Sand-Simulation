#define SDL_MAIN_HANDLED 
#include <SDL2/SDL.h>
#define si 300
#define ji 300
#define FPS 30
#include<iostream>
#include <time.h>
using namespace std;

//Global Constants
const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 600;
int offsetX = 0;
int offsetY = 0;
bool drawLines = true;
int w = 2;
int row = SCREEN_WIDTH / w, cols = SCREEN_HEIGHT / w;

const int framedelay = 1000 / FPS;
int current[ji][si];
int next_gen[ji][si];
Uint32 framestart;
int frameTime;

int main(int argc, char** argv) {
	
	srand(static_cast<unsigned int>(time(0)));
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* win;
	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0,0,0 };
	bool gameLoop = true;
	bool s = false;
	int counter=0;

	win = SDL_CreateWindow("Sand Simulation", 50, 50, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_Rect rect;

	
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < cols; j++) {
			current[i][j] = 0;
			next_gen[i][j] = 0;
		}
	}

current[5][5] =2; 
current[5][3] =2;
current[5][2] =2;
	while (gameLoop) {

		framestart = SDL_GetTicks();

		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			gameLoop = false;
		}
		if (event.key.keysym.sym == SDLK_s) {
			s = true;
		}
		if (event.key.keysym.sym == SDLK_q) {
			gameLoop = false;
		}
		SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
		SDL_RenderClear(renderer);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < cols; j++) {
				rect.x = i * w;
				rect.y = j * w;
				rect.w = w;
				rect.h = w;
				if (current[i][j]==0){
					//SDL_RenderDrawRect(renderer, &rect);
				}
				else if (current[i][j] == 2) {
					SDL_SetRenderDrawColor(renderer,35,137,218,255);
					SDL_RenderFillRect(renderer, &rect);
				}
				else if (current[i][j] == 1) {

					SDL_SetRenderDrawColor(renderer,251,225,187,255);
					SDL_RenderFillRect(renderer, &rect);
				}
			}
		}
		SDL_RenderPresent(renderer);
				if (s) {
					for (int i = 0; i < row; i++)
					{
						for (int j = 0; j < cols; j++) {

            if (j+1<row && i-1>=0 && i+1<cols){
                    if( current[i][j]==1 && current[i][j+1]==0){ 
                            next_gen[i][j]=0;
                            next_gen[i][j+1] = 1;}
					else if (current[i][j]==1&& current[i+1][j+1]==0){ 
                            next_gen[i][j]=0;
                            next_gen[i+1][j+1]=1;}
					else if (current[i][j]==1 && current[i-1][j+1]==0){ 
                            next_gen[i][j]=0;
                            next_gen[i-1][j+1]=1;

						}
                    if( current[i][j]==2 && current[i][j+1]==0){ 
                            next_gen[i][j]=0;
                            next_gen[i][j+1] = 2;}
					}
				}
				}
				counter++;
				if (counter%20==0){
						next_gen[150][1] = 1;
				}
				else if (counter%10) {
				
						next_gen[147][1] = 1;

				}

					for (int i = 0; i < row; i++)
					{
						for (int j = 0; j < cols; j++) {
							current[i][j] = next_gen[i][j];
						}
					}

					frameTime = SDL_GetTicks() - framestart;

					if (frameTime < framedelay) {
						SDL_Delay(framedelay - frameTime);
					}
				}
	}
	
	return 0;
}

