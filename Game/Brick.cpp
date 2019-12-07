#include "Brick.h"

Brick::Brick(string brickSheet, int x, int y, int width, int height, string type, int hp, bool loot) {
	brickTexture = textureManager::loadTexture(brickSheet.c_str());
	_sheet = brickSheet;
	_x = x * 80;
	_y = (y + 1) * 60;
	_tableX = y; //row is y
	_tableY = x; //column is x
	_width = width;
	_height = height;
	_type = type;
	_hp = hp;
	_loot = loot;
}

void Brick::update() {
	destRect.x = _x;
	destRect.y = _y;
	destRect.w = _width;
	destRect.h = _height;
}

void Brick::render() {
	SDL_RenderCopy(Game::rendered, brickTexture, NULL, &destRect);
}