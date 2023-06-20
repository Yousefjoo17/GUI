#include "player.h"
#include"SDL_image.h"
#include<cmath>
#include<iostream>
using namespace std;

int player::playernumber = 0;

player::player(SDL_Renderer* renderertarget, string filepath, int x, int y, int framesX, int framesY)
{

	SDL_Surface* surface = IMG_Load(filepath.c_str());

	texture = SDL_CreateTextureFromSurface(renderertarget, surface);
	
	SDL_FreeSurface(surface);
	
	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);
 
	texturewidth = cropRect.w;//

	cropRect.w /= framesX;
	cropRect.h /=  framesY;

	positionRect.x = x;
	positionRect.y = y;
	positionRect.w = cropRect.w;
	positionRect.h = cropRect.h;

	framewidth = cropRect.w;
	frameheight= cropRect.h;

	movespeed = 250.0f;

	originX = framewidth / 2;
	originY = frameheight / 2;

	isActive = false;

	playernumber++;

	if (playernumber == 1)
	{
		//SDL_SetTextureColorMod(texture, 0, 0, 155);
		keys[0] = SDL_SCANCODE_UP;
		keys[1] = SDL_SCANCODE_DOWN;
		keys[2] = SDL_SCANCODE_LEFT;
		keys[3] = SDL_SCANCODE_RIGHT;
	}
	else if(playernumber==2)
	{
		//SDL_SetTextureColorMod(texture, 0, 155, 0);
		keys[0] = SDL_SCANCODE_W;
		keys[1] = SDL_SCANCODE_S;
		keys[2] = SDL_SCANCODE_A;
		keys[3] = SDL_SCANCODE_D;
	}

}

player::~player()
{
	SDL_DestroyTexture(texture);
}

void player::update(float delta, const Uint8* keystate)
{
	isActive = true;
	if (keystate[keys[0]])    //transition from point to another point
	{
		positionRect.y -= movespeed * delta;
		cropRect.y = 0;
	}
	else if (keystate[keys[1]])
	{
		positionRect.y += movespeed * delta;
		cropRect.y = frameheight;
	}
	else if (keystate[keys[2]])
	{
		positionRect.x -= movespeed * delta;
		cropRect.y = frameheight * 3;
	}
	else if (keystate[keys[3]])
	{
		positionRect.x += movespeed * delta;
		cropRect.y = frameheight * 2;
	}
	else
		isActive = false;

	if (isActive)   // making the animation
	{
		framecounter += delta;
		if (framecounter >= 0.25f)
		{
			framecounter = 0;
			cropRect.x += framewidth;
			if (cropRect.x >= texturewidth)
				cropRect.x = 0;
		}
	}
	else
	{
		framecounter = 0;
		cropRect.x = framewidth;
	}
	
}

void player::draw(SDL_Renderer* renderertarget, SDL_Rect camerarect)
{
	SDL_Rect drawingRect = { positionRect.x - camerarect.x ,positionRect.y - camerarect.y,positionRect.w,positionRect.h };
	SDL_RenderCopy(renderertarget, texture, &cropRect,&drawingRect);
	//drawingRect instead of positionRect

}
bool player::intersection(player& p)
{
	
	if (abs(p.positionRect.x - positionRect.x) < (framewidth-15) && abs(p.positionRect.y - positionRect.y) < frameheight)
	{
		SDL_SetTextureColorMod(texture, 255, 0, 0); 
		return true;
	}
	else
	{
		SDL_SetTextureColorMod(texture, 255,255,255);
		return false;
	}
}

int player::getoriginX()
{
	return originX+positionRect.x;
}

int player::getoriginY()
{
	return originY+positionRect.y;
}






