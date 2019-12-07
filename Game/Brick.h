#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include "textureManager.h"
#include <iostream>
using namespace std;
class Brick {
protected:
	int _x, _y;
	int _tableX, _tableY;
	int _width, _height;
	string _type;
	int _hp;
	int _loot;
	string _sheet;
	SDL_Texture* brickTexture;
	SDL_Texture* rewardTexture;
	SDL_Rect destRect;
public:
	Brick(string brickSheet, int x, int y, int width, int height, string type, int hp, int loot);
	Brick(int x, int y, int width, int height, int loot);
	~Brick();
	virtual string getType() { return _type; }
	virtual int getHp() { return _hp; }
	virtual int getLoot() { return _loot; }
	virtual void update();
	virtual void render() = 0;
	virtual int getTableX() { return _tableX; }
	virtual int getTableY() { return _tableY; }
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual int getW() = 0;
	virtual int getH() = 0;
	virtual void updateHpImg() = 0;
};

