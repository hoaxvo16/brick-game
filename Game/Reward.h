#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "textureManager.h"
#include <iostream>
#include "Brick.h"
using namespace std;
class Reward : public Brick {
private:
public:
	Reward(int x, int y, int width, int height, int loot) : Brick(x, y, width, height, loot) {}
	int getX();
	int getY();
	int getW();
	int getH();
	void update();
	void render();
	void updateHpImg() {}
};

