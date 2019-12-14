#include "Reward.h"

int Reward::getX() { return _x; }

int Reward::getY() { return _y; }

int Reward::getW() { return _width; }

int Reward::getH() { return _height; }

//hàm di chuyển vật thưởng
void Reward::updateReward() {
	destRect.x = _x;
	destRect.y += 2;
	destRect.w = _width;
	destRect.h = _height;
}
//Hàm vẽ
void Reward::render() {
	SDL_RenderCopy(Game::rendered, rewardTexture, NULL, &destRect);
}

// kiem tra neu vat pham cham paddle va tra ve loai vat pham
int Reward::isTouchWithPaddle(PaddleObject* paddle) {
	if (_x + _width >= paddle->getPaddleXpos() &&
		_x <= paddle->getPaddleXpos() + PADDLE_HEIGHT &&
		destRect.y + _height >= paddle->getPaddleYpos() &&
		destRect.y <= paddle->getPaddleYpos() + PADDLE_WIDTH) {
		return _loot;
	}
	return 0;
}

//Hàm kiểm tra vật thương ra ngoài màn hình
bool Reward::isOut() {
	if (destRect.y > WINDOW_HEIGHT)
		return true;
	return false;
}

