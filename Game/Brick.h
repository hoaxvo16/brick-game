#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include "textureManager.h"
#include <iostream>
using namespace std;
class Brick {
protected:
	int _empty = 1;
	int _x, _y;
	int _width, _height;
	string _type;
	int _hp;
	bool _loot;
	SDL_Texture* brickTexture;
	SDL_Rect destRect;
public:
	virtual int isEmpty() {
		return _empty;
	}
	Brick(int empty, const char* brickSheet, int x, int y, int width, int height, string type, int hp, bool loot);
	~Brick();
	virtual string getType() { return _type; }
	virtual int getHp() { return _hp; }
	virtual void update();
	virtual void render();
};

