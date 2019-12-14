#include "PaddleObject.h"
PaddleObject::PaddleObject(const char* paddlesheet, int x, int y)
{
	paddleTexture = textureManager::loadTexture(paddlesheet);
	//Load file ảnh, lưu vào biến texture
	xpos = x;	
	ypos = y;
}
PaddleObject::~PaddleObject()
{

}
void PaddleObject::update()
{
	destRect.x = xpos;
	destRect.y = ypos;
	//Vị trí nó thay đổi thế nào thì hình chữ nhật chứa nó phải thay đổi theo
	destRect.w = PADDLE_WIDTH;
	destRect.h = PADDLE_HEIGHT;
	//Hình chữ nhật chứa nó cần có độ cao và bề rộng của thanh
}
void PaddleObject::updateforbrick()
{
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = PADDLE_HEIGHT;
	destRect.h = PADDLE_WIDTH;
}
void PaddleObject::render()
{
	SDL_RenderCopy(Game::rendered, paddleTexture, NULL, &destRect);
	//Hàm đọc hết file ảnh và sau đó lưu lại trên reder với kích thước và vị trí của destRect
}
void PaddleObject::moveDown()
{
	if (ypos < WINDOW_HEIGHT - destRect.h - 10)
	{	//Chưa tới đáy cửa sổ thì được xuống
		ypos += SPEED;
	}
}
void PaddleObject::moveUp()
{
	if (ypos > 10)
	{//Chưa tới đỉnh thì được lên
		ypos -= SPEED;
	}
}
int PaddleObject::getPaddleXpos() { return xpos; }
int PaddleObject::getPaddleYpos() { return ypos; }

// Ham di chuyen cho Bot
void PaddleObject::moveLeft() {
	if (xpos > 0) {	//Chưa tới đáy cửa sổ thì được xuống
		xpos -= SPEED;
	}
}
void PaddleObject::moveRight() {
	if (xpos < WINDOW_WIDTH - PADDLE_HEIGHT) {//Chưa tới đỉnh thì được lên
		xpos += SPEED;
	}
}

// Ham di chuyen paddle bang chuot cho Player
void PaddleObject::moveWithMouse(int xMouse) {
	if (xMouse - PADDLE_HEIGHT / 2 > 0 && xMouse + PADDLE_HEIGHT / 2 < WINDOW_WIDTH)
		xpos = xMouse - PADDLE_HEIGHT / 2;
}
