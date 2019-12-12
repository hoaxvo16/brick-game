#include "Skills.h"

Skills::Skills(vector<vector<Brick*>>& table, int loot, int pos) {
	_pos = pos;
	_start = SDL_GetTicks();
	switch (loot) {
	case 1:
		break;
	case 2: // laser
		execLaser(table);
		_duration = 1000;
		break;
	case 3:
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

void Skills::execLaser(vector<vector<Brick*>>& table) {
	setTexture("PNGFile/laser_x.png");
	_x = _pos * 80;
	_y = 0;
	_w = 80;
	_h = 688;

	for (size_t i = 0; i < 5; i++) {
		table[i][_pos] = NULL;
	}
}