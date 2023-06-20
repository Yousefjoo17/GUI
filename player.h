#pragma once
#include"SDL.h"
#include"string"
#include<iostream>
using namespace std;
class player
{
private:
	SDL_Rect cropRect;
	SDL_Rect positionRect;
	SDL_Texture* texture;
	float movespeed;
	float framecounter;
	int framewidth, frameheight; //
	int texturewidth;
	static int playernumber;
	bool isActive;
	SDL_Scancode keys[4];
	int originX, originY;
public:
	player(SDL_Renderer* renderertarget, string filepath, int x, int y, int framesX, int framesY);
	~player();

	void update(float delta, const Uint8* keystate);
	void draw(SDL_Renderer* renderertarget,SDL_Rect camerarect);
	bool intersection(player &p);
	int getoriginX();
	int getoriginY();
	int getradius();
};

