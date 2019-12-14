#include "BotPaddle.h"
BotPaddle::BotPaddle(const char* paddleSheet, int x, int y)
{
	//Khởi tạo thanh BOT tương tự thanh bình thường
	paddleTexture = textureManager::loadTexture(paddleSheet);
	xpos = x;
	ypos = y;
}
void BotPaddle::updateBOT(BallObject *ball)
{
	PaddleObject::update();	//Cập nhật vị trí thanh như bình thường
	int centerBall = ball->getCenterOfBall();
	if (centerBall < ypos + 20)	//Nếu banh đi xuống phía trên thanh
	{
		moveDown();
		moveUp();
		moveUp();	//Thì đi lên theo :))
	}
	else if (centerBall > ypos + PADDLE_HEIGHT - 20)	//Ngược lại
	{
		moveUp();
		moveDown();
		moveDown();
	}
}	//Điều kiện trong if là để điều chỉnh việc di chuyển của BOT sao cho hợp lí
void BotPaddle::updateBrickBot(BallObject* ball)
{
	PaddleObject::updateforbrick();//Cập nhật vị trí thanh như bình thường
	int centerBall = ball->getCenterOfBallOx();
	if (centerBall < xpos + PADDLE_WIDTH / 2 + 20)	//Nếu banh đi xuống phía trên thanh
	{
		moveLeft();
	}
	else if (centerBall > xpos - PADDLE_WIDTH / 2 - 20)	//Ngược lại
	{
		moveRight();
	}
}