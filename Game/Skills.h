#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "textureManager.h"
#include "Brick.h"
#include"BallObject.h"
#include <vector>
#include <iostream>
using namespace std;
class BallObject;
class Skills {
private:
	int _start;
	int _duration;
	SDL_Texture* skillTexture;
	SDL_Rect destRect;
	int _x, _y, _w, _h;
	int _pos;
public:
	Skills(vector<vector<Brick*>>& table, int loot, int pos);
	void execLaser(vector<vector<Brick*>>& table);
	void setTexture(string sheet);
	void render();
	void update();
	int getStart() { return _start; }
	int getDuration() { return _duration; }
	void execHp(BallObject*& ball);
};

