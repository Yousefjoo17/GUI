#include"SDL.h"
#include<SDL_image.h>
#include"SDL_ttf.h"
#include"SDL_mixer.h"
#include<iostream>
#include"player.h"
using namespace std;

#define SCREEN_WIDTH 1380
#define SCREEN_HEIGHT 700

void scrolling(player &p,SDL_Rect &camera)
{
	if (p.getoriginX() - SCREEN_WIDTH / 2 > 0)  //
		camera.x = p.getoriginX() - SCREEN_WIDTH / 2;
	if (p.getoriginY() - SCREEN_HEIGHT / 2 > 0)
		camera.y = p.getoriginY() - SCREEN_HEIGHT / 2;
}

int main(int argc, char* args[])
{
	SDL_Window* window = nullptr;
	SDL_Renderer* rendertarget = nullptr;
	int currentTime = 0;
	int prevtime = 0;
	float delta = 0.0f;
	const Uint8* keystate;
	SDL_Rect cameraRect = { 0,0,1380,700 };
	int levelwidth, levelheight;
	SDL_Init(SDL_INIT_VIDEO);
	

	window = SDL_CreateWindow("Basabosa", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	rendertarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);//Create a 2D rendering context for a window.

	player player1(rendertarget, "c3.png", 0, 0, 3, 4);
	player player2(rendertarget, "c3.png", 77, 5,3, 4);
	
	SDL_Texture* texture = IMG_LoadTexture(rendertarget, "c2.png");
	SDL_QueryTexture(texture, NULL, NULL, &levelwidth, &levelheight);
	//SDL_SetRenderDrawColor(rendertarget, 50, 60, 15, 19);

	bool is_running = true;
	SDL_Event ev; 

	while (is_running)
	{
		prevtime = currentTime;
		currentTime = SDL_GetTicks();
		delta = (currentTime - prevtime) / 1000.0f;

		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				is_running = false;
		
		}
		
		keystate = SDL_GetKeyboardState(NULL);
		player1.update(delta, keystate);
		player2.update(delta, keystate);

		scrolling(player1, cameraRect);


		if (cameraRect.x+cameraRect.w >= levelwidth)
			cameraRect.x=levelwidth- SCREEN_WIDTH ;
		if (cameraRect.y + cameraRect.h >= levelheight)
			cameraRect.y = levelheight - SCREEN_HEIGHT ;   //

		player2.intersection(player1);

		SDL_RenderClear(rendertarget);

		SDL_RenderCopy(rendertarget, texture, &cameraRect, NULL);
		player1.draw(rendertarget, cameraRect);
		player2.draw(rendertarget, cameraRect);
		SDL_RenderPresent(rendertarget);
	}


	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(rendertarget);
	SDL_DestroyTexture(texture);
	texture = NULL;
	window = NULL;
	rendertarget = NULL;
	SDL_Quit();
	return 0;
}