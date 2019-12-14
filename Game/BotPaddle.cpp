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
void BotPaddle::updateBrickBot(BallObject* ball, vector<vector<Brick*>> table)
{
	PaddleObject::updateforbrick();//Cập nhật vị trí thanh như bình thường
	int target = rand() % 152 + 5;
	float yball = ball->getY();
	float xPaddle = getPaddleXpos();
	float closestY = 0;
	float closestX = -1;
	for (size_t i = 0; i < 5; i++) {
		for (size_t j = 0; j < 10; j++) {
			Brick* rew = table[i][j];
			if (rew != NULL && rew->getType() == "reward" && rew->isCollected() && rew->getDesty() > closestY) {
				closestY = rew->getDesty();
				closestX = rew->getDestx();
			}
		}
	}
	if ((closestX != -1 && ball->getVy() < 0) || (ball->getVy() < 2 && ball->getY() < closestY)) {
		if (closestX < xPaddle + 5 && xPaddle > 0)
			moveLeft();
		else if (closestX > xPaddle + PADDLE_HEIGHT - 5 && xPaddle < WINDOW_WIDTH)
			moveRight();
	} else if (yball >= WINDOW_HEIGHT / 2.5) {
		srand(time(NULL));
		float xball = ball->getX() + 10;
		if (xball < xPaddle + target && xPaddle > 0)
			moveLeft();
		else if (xball > xPaddle + PADDLE_HEIGHT - target - 5 && xPaddle < WINDOW_WIDTH)
			moveRight();
	}
}