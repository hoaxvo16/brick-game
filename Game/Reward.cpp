#include "Reward.h"

int Reward::getX() { return _x; }

int Reward::getY() { return _y; }

int Reward::getW() { return _width; }

int Reward::getH() { return _height; }

void Reward::updateReward() {
	destRect.x = _x;
	destRect.y += 2;
	destRect.w = _width;
	destRect.h = _height;
}

void Reward::render() {
	SDL_RenderCopy(Game::rendered, rewardTexture, NULL, &destRect);
}

//void Reward::isTouchWithPaddle(PaddleObject paddle) {
//	if (destRect.y + _height >= paddle.getPaddleYpos() && paddle.getPaddleXpos() <= _x && _x + _width <= paddle.getPaddleXpos() + PADDLE_HEIGHT) {}
//}

bool Reward::isOut() {
	if (destRect.y > WINDOW_HEIGHT)
		return true;
	return false;
}

