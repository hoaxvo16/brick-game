#pragma once
#include "Brick.h"

class Rect : public Brick {
private:
public:
	Rect(string brickSheet, int x, int y, int width, int height, string type, int hp, int loot): Brick(brickSheet, x, y, width, height, type, hp, loot) {}
	int getX();
	int getY();
	int getW();
	int getH();
	//Update img when hit
	void updateHpImg();
	void render();
};

