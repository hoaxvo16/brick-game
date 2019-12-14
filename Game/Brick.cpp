#include "Brick.h"

Brick::Brick(string brickSheet, int x, int y, int width, int height, string type, int hp, int loot) {
	brickTexture = textureManager::loadTexture(brickSheet.c_str());
	_sheet = brickSheet;
	_x = x * 80; // chuyen toa do tren table thanh toa do cua pixel
	_y = (y + 1) * 60; // chuyen toa do tren table thanh toa do cua pixel
	_tableX = y; // toa do row tren table
	_tableY = x; // toa do col tren table
	_width = width;
	_height = height;
	_type = type;
	_hp = hp; // mau cua gach
	_loot = loot; // loai vat pham
}

// kiem tra loai vat pham ma vien gach dang chua, khi vo thi render vat pham
Brick::Brick(int x, int y, int width, int height, int loot,int collected) {
	string rewardSheet;
	switch (loot) {
	case 1:
		rewardSheet = "PNGFile/hp.png";
		break;
	case 2:
		rewardSheet = "PNGFile/laser.png";
		break;
	case 3:
		rewardSheet = "PNGFile/missile.png";
		break;
	}
	rewardTexture = textureManager::loadTexture(rewardSheet.c_str());
	if (collected == 0)
	{
		_x = x * 80 + 15;
		_y = (y + 1) * 60 + 5;
	}
	else
	{
		_x = x;
		_y = y;
		destRect.y = y;
	}
	_width = width;
	_height = height;
	_type = "reward";
	_loot = loot;
}

void Brick::update() {
	destRect.x = _x;
	destRect.y = _y;
	destRect.w = _width;
	destRect.h = _height;
}

void Brick::updateReward() {}

int Brick::isTouchWithPaddle(PaddleObject* paddle) { return 0; }
