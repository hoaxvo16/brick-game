#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
class AbstractGame	//Này là lớp ảo để dành cho 2 loại Game (2 player và vs BOT)
{
protected:
	bool isRunning;
	SDL_Window* window;
public:
	AbstractGame(){}
	~AbstractGame(){}
	static SDL_Renderer* rendered;
	virtual void init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen,int savegame) = 0;
	virtual void update()=0;
	virtual void render()=0;
	virtual void handleEvents()=0;
	virtual void clean()=0;
	bool running();
};