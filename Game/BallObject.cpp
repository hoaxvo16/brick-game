#include "BallObject.h"
float random();
float accelerate = 0.1;	//Gia tốc
int count = 0;	//Số lần tăng vận tốc theo gia tốc
BallObject::BallObject(const char* ballsheet, int x, int y)
{
	ballTexture = textureManager::loadTexture(ballsheet);
	//Đọc file hình quả banh
	xpos = x;
	ypos = y;
	velocityX = 0;	
	velocityY = 0;
	//Khởi tạo cho quả banh
}
BallObject::~BallObject()
{

}
void BallObject::update()
{
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.h = BALL_RADIUS;
	srcRect.w = BALL_RADIUS;
	int outSide = isOut();
	//if (outSide != 0)
	//{
	//	//Nếu trái banh đã ra ngoài
	//	if (outSide == 1)
	//	{
	//		score1++;	//Cộng điểm cho player1 
	//	}
	//	else if (outSide == -1)
	//	{
	//		score2++;	//Cộng điểm cho player2
	//	}
	//	xpos = WINDOW_WIDTH / 2;	//Đem trái banh về giữa cửa sổ
	//	ypos = WINDOW_HEIGHT / 2;
	//	count = 0;	//Set số lần tăng gia tốc về ban đầu
	//}
	if (outSide == 1) {
		xpos = WINDOW_WIDTH / 2;	
		ypos = WINDOW_HEIGHT / 2;
	}

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;
	//Biến đổi về hình chữ nhật vẽ quả banh	
}
void BallObject::render()
{
	SDL_RenderCopy(Game::rendered, ballTexture, NULL, &destRect);
}
void BallObject::move(PaddleObject *p1, PaddleObject *p2)
{
	if (velocityX == 0 && velocityY == 0)
	{	//Phat sinh luc bat dau game
		velocityX -= 2.9;
		velocityY -= 2.9;
	}
	xpos += velocityX;	//Cộng theo vận tốc
	ypos += velocityY;
	isTouch(p1, p2);	//Xét sự va chạm

}
bool BallObject::isTouch(PaddleObject *paddle1, PaddleObject *paddle2)
{
	int paddleWidth = PADDLE_WIDTH;
	int paddleHeight = PADDLE_HEIGHT;
	if (ypos <= 0)
	{
		//Đụng trên thì dội ngược lại
		velocityY = -velocityY;
		return true;
	}
	else if (ypos >= WINDOW_HEIGHT - destRect.h)
	{
		//Đụng dưới thì dội ngược lên
		velocityY = -velocityY;
		return true;
	}
	int paddleXpos = paddle1->getPaddleXpos();
	int paddleYpos = paddle1->getPaddleYpos();
	if (xpos <= paddleXpos + paddleWidth && ypos + (destRect.h / 2) <= paddleYpos + paddleHeight && ypos + (destRect.h / 2) >= paddleYpos && xpos >= paddleXpos)
	{
		//Đụng thanh bên trái dội ngược ra bên phải
		xpos = paddleXpos + paddleWidth + 1;	//Điều chỉnh vị trí quả banh cho không bị đè lên thanh
		velocityX = -velocityX;
		if (count <= 30)
		{	//Tăng theo gia tốc, tối đa 30 lần
			velocityX *= 1 + accelerate;
			velocityY *= 1 + accelerate;
			count++;
		}
		return true;
	}
	paddleXpos = paddle2->getPaddleXpos();
	paddleYpos = paddle2->getPaddleYpos();
	if (xpos + destRect.w >= paddleXpos && (ypos + (destRect.h / 2)) <= (paddleYpos + paddleHeight) && (ypos + destRect.h / 2) >= paddleYpos && xpos <= paddleXpos + paddleWidth)
	{	//Tương tự bên trên cho thanh bên phải
		xpos = paddleXpos - destRect.w - 1;
		velocityX = -velocityX;
		if (count <= 30)
		{
			velocityX *= 1 + accelerate;
			velocityY *= 1 + accelerate;
			count++;
		}
		return true;
	}
	return false;
}

void BallObject::move(PaddleObject* p) {
	if (velocityX == 0 && velocityY == 0) {	//Phat sinh luc bat dau game
		velocityX -= 2.9;
		velocityY -= 2.9;
	}
	xpos += velocityX;	//Cộng theo vận tốc
	ypos += velocityY;
	isTouch(p);	//Xét sự va chạm

}
int BallObject::rectCollided(int cx, int cy, float radius, int rx, int ry, int rw, int rh) {
	// temporary variables to set edges for testing
	int testX = cx;
	int testY = cy;
	int edge = -1;
	//0: left edge
	//1: right edge
	//2: top edge
	//3: bottom edge

	// which edge is closest?
	if (cx < rx) { // test left edge
		testX = rx; 
		edge = 0;
	} else if (cx > rx + rw) {  // right edge
		testX = rx + rw;
		edge = 1;
	}  
	if (cy < ry) { // top edge
		testY = ry;
		edge = 2;
	} else if (cy > ry + rh) { // bottom edge
		testY = ry + rh;
		edge = 3;
	}   

	// get distance from closest edges
	int distX = cx - testX;
	int distY = cy - testY;
	float distance = sqrt((distX * distX) + (distY * distY));

	// if the distance is less than the radius, collision!
	if (distance <= radius)
		return edge;
	return -1;
}
bool BallObject::isTouch(PaddleObject* paddle) {
	if (ypos <= 0) {
		//Đụng trên thì dội ngược lại
		velocityY = -velocityY;
		return true;
	} else if (xpos <= 0 || xpos >= WINDOW_WIDTH - destRect.w) {
		velocityX *= -1;
		return true;
	}

	int paddleXpos = paddle->getPaddleXpos();
	int paddleYpos = paddle->getPaddleYpos();
	int edgeRes = rectCollided(xpos, ypos, BALL_RADIUS + 0.0, paddleXpos, paddleYpos, PADDLE_HEIGHT, PADDLE_WIDTH);
	if (edgeRes == 2) {
		velocityY *= -1;
		return true;
	}
	return false;
}
//int BallObject::isOut()
//{
//	if (xpos  < -destRect.w - 5)	//Nếu banh đi khỏi lề trái
//	{
//		velocityX = random();	//Set lại vận tốc trái banh, tính năng vẫn đang update(cần đem về việc random)
//		velocityY = random();
//		return -1;	//Trả về -1 để biết là ra player2 ăn điểm
//	}
//	if (xpos > WINDOW_WIDTH + 5)	//Nếu banh đi khỏi lề phải
//	{
//		velocityX = random();
//		velocityY = random();
//		return 1;	//Trả về 1 để biết là ra player1 ăn điểm
//	}
//	return 0;
//}

int BallObject::isOut() {
	if (ypos > WINDOW_HEIGHT + 5) {
		velocityX = random();
		velocityY = random();
		return 1;
	}
	return 0;
}
float random()
{
	srand(time(NULL));
	float ran = 0;
	int s = 0;
	while (s <= 20 && s >= -20)
	{
		s = rand() % 60 - 30;
		ran = (float)s / 10;
	}
	return ran;
}
