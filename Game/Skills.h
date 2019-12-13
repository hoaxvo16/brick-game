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
	int _start = 0;
	int _duration;
	SDL_Texture* skillTexture;
	SDL_Rect destRect;
	int _x, _y, _w, _h;
	int _loot;
	int _pos;
public:
	Skills(vector<vector<Brick*>>& table, int loot, int pos,BallObject*& ball);
	void execLaser(vector<vector<Brick*>>& table,BallObject*& ball);
	void setTexture(string sheet);
	void render();
	void update();
	int getStart() { return _start; }
	int getDuration() { return _duration; }
	void execHp(BallObject*& ball);
	void execMissile(vector<vector<Brick*>>& table);
	void updateMissile(vector<vector<Brick*>>& table);
	int getLoot() { return _loot; }
};

