#include "Skills.h"

Skills::Skills(vector<vector<Brick*>>& table, int loot, int pos, BallObject*& ball) {
	_pos = pos;
	_loot = loot;
	
	switch (loot) {
	case 1:
		_start = SDL_GetTicks();
		execHp(ball);
		_duration = 500;
		break;
	case 2: // laser
		_start = SDL_GetTicks();
		execLaser(table,ball);
		_duration = 1000;
		break;
	case 3:
		execMissile(table);
		_duration = 1000;
		break;
	}
}

void Skills::setTexture(string sheet) {
	skillTexture = textureManager::loadTexture(sheet.c_str());
}

void Skills::render() {
	SDL_RenderCopy(Game::rendered, skillTexture, NULL, &destRect);
}

void Skills::update() {
	destRect.x = _x;
	destRect.y = _y;
	destRect.w = _w;
	destRect.h = _h;
}


void Skills::updateMissile(vector<vector<Brick*>>& table) {
	int targetY;
	size_t targetRow;
	size_t targetCol;
	if (_start == 0) {
		destRect.x = _x;
		destRect.y -= 4;
		destRect.w = _w;
		destRect.h = _h;
	}
	targetY = 0;
	targetRow = 0;
	targetCol = _pos;
	for (size_t i = 0; i < 5; i++) {
		if (table[i][_pos] != NULL && table[i][_pos]->getType() == "rect") {
			targetY = table[i][_pos]->getDesty();
			targetRow = i;
		}
	}
	
	if (_start == 0 && destRect.y <= targetY) {
		_start = SDL_GetTicks();
		destRect.x = _pos * 80 - 10;
		destRect.w = 100;
		destRect.h = 100;
		setTexture("PNGFile/missile_end1.png");
		if (targetY != 0)
			table[targetRow][targetCol] = NULL;
	}
}

void Skills::execLaser(vector<vector<Brick*>>& table,BallObject*& ball) {
	setTexture("PNGFile/laser_x1.png");
	_x = _pos * 80 + 10;
	_y = 0;
	_w = 60;
	_h = 688;

	for (size_t i = 0; i < 5; i++) {
		if (table[i][_pos] != NULL && table[i][_pos]->getType() == "rect")
			ball->setScore(ball->getScore_1() + 10);
		table[i][_pos] = NULL;
	}
}

void Skills::execMissile(vector<vector<Brick*>>& table) {
	setTexture("PNGFile/missile_x1.png"); // mid
	_x = _pos * 80 + 25;
	_y = 688;
	_w = 30;
	_h = 100;
	destRect.x = _x;
	destRect.y = _y;
	destRect.w = _w;
	destRect.h = _h;
	render();
}

void Skills::execHp(BallObject*& ball) {
	int x = ball->getLife() + 1;
	ball->setLife(x);
}