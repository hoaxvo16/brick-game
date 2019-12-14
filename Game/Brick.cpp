#include "Brick.h"
//Phương thức khởi tạo cho 2 kiểu brick rect và reward
Brick::Brick(string brickSheet, int x, int y, int width, int height, string type, int hp, int loot) {
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
//Hàm cập nhật vị trí hình vẽ
void Brick::update() {
	destRect.x = _x;
	destRect.y = _y;
	destRect.w = _width;
	destRect.h = _height;
}
//Hàm cập nhật vị trí vật thưởng
void Brick::updateReward() {}
//Hàm kiểm tra va chạm với thanh trượt
int Brick::isTouchWithPaddle(PaddleObject* paddle) { return 0; }
