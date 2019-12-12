#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include "textureManager.h"
#include <iostream>
#include "PaddleObject.h"
using namespace std;
class Brick {
protected:
	int _x, _y;
	int _tableX, _tableY;
	int _width, _height;
	string _type;
	int _collected = 0;
	int _hp;
	int _loot;
	string _sheet;
	SDL_Texture* brickTexture;
	SDL_Texture* rewardTexture;
	SDL_Rect destRect;
public:
	Brick(string brickSheet, int x, int y, int width, int height, string type, int hp, int loot);
	Brick(int x, int y, int width, int height, int loot,int collected);
	~Brick();
	virtual string getType() { return _type; }
	virtual int getHp() { return _hp; }
	virtual int getLoot() { return _loot; }
	virtual bool isCollected() { return _collected; }
	virtual void setCollected() { _collected = 1; }
	virtual void update();
	virtual void updateReward();
	virtual void render() = 0;
	virtual int getTableX() { return _tableX; }
	virtual int getTableY() { return _tableY; }
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual int getW() = 0;
	virtual int getH() = 0;
	virtual int getDestx() { return destRect.x; };
	virtual int getDesty() { return destRect.y; };
	virtual void updateHpImg() = 0;
	virtual void setDestx(int x){ destRect.x = x; }
	virtual void setDesty(int y){ destRect.y = y; }
	virtual bool isOut() { return true; }
	virtual int isTouchWithPaddle(PaddleObject* paddle);
};

