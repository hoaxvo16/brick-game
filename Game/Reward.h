#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "textureManager.h"
#include <iostream>
#include "Brick.h"
#include "BrickGame.h"
using namespace std;
class Reward : public Brick {
private:
public:
	Reward(int x, int y, int width, int height, int loot,int collected) : Brick(x, y, width, height, loot, collected) {}
	int getX();
	int getY();
	int getW();
	int getH();
	void updateReward();
	void render();
	void updateHpImg() {}
	int isTouchWithPaddle(PaddleObject* paddle);
	bool isOut();
};

