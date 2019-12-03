#include "Brick.h"

Brick::Brick(int empty, const char* brickSheet, int x, int y, int width, int height, string type, int hp, bool loot) {
	brickTexture = textureManager::loadTexture(brickSheet);
	_empty = empty;
	_x = x;
	_y = y;
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