#pragma once
#include "Brick.h"

class Rect : public Brick {
private:
public:
	Rect(int empty, const char* brickSheet, int x, int y, int width, int height, string type, int hp, bool loot): Brick(empty, brickSheet, x, y, width, height, type, hp, loot) {}
};

