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
	SDL_FRect destRect;
	float _x, _y;
	int _w, _h;
	int _loot;
	int _pos;
	int _missile = -1; // 0 mid, 1 left, 2 right, -1 none
public:
	Skills(vector<vector<Brick*>>& table, int loot, int pos, int missile_num, BallObject*& ball);
	void execLaser(vector<vector<Brick*>>& table,BallObject*& ball);
	void setTexture(string sheet);
	void render();
	void update();
	int getStart() { return _start; }
	int getDuration() { return _duration; }
	void execHp(BallObject*& ball);
	void execMissile(vector<vector<Brick*>>& table);
	int getLoot() { return _loot; }
	void updateMissile(vector<vector<Brick*>>& table, BallObject*& ball);
	void renderExplosion(int x, int y);
	bool isTouchWithTarget(Brick* target);
};

