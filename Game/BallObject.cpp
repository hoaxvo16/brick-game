#include "BallObject.h"
#include "Reward.h"
float ranDom();
float accelerate = 0.1;	//Gia tốc	//Số lần tăng vận tốc theo gia tốc
BallObject::BallObject(const char* ballsheet, int x, int y)
{
	ballTexture = textureManager::loadTexture(ballsheet);
	//Đọc file hình quả banh
	xpos = x;
	ypos = y;
	velocity = 0;
	velocityX = 0;	
	velocityY = 0;
	//Khởi tạo cho quả banh
}
BallObject::~BallObject()
{

}
//Hàm xử lý game
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
		//Neus trái banh đi ra ngoài cập nhật lại vị trí trừ mạng đi
		xpos = WINDOW_WIDTH / 2;	
        ypos = WINDOW_HEIGHT - 300;
		speed = 0;
		life--;
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
	xpos += velocityX;	//Cộng theo vận tốc cai con cac
	ypos += velocityY;
	isTouch(p1, p2);	//Xét sự va chạm

}
//Hàm kiểm tra va chạm giữa trái banh với thanh trượt và vật cản
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
	else if (ypos >= WINDOW_HEIGHT - BALL_RADIUS)
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
		if (speed <= 30)
		{	//Tăng theo gia tốc, tối đa 30 lần
			velocityX *= 1 + accelerate;
			velocityY *= 1 + accelerate;
			speed++;
		}
		return true;
	}
	paddleXpos = paddle2->getPaddleXpos();
	paddleYpos = paddle2->getPaddleYpos();
	if (xpos + destRect.w >= paddleXpos && (ypos + (destRect.h / 2)) <= (paddleYpos + paddleHeight) && (ypos + destRect.h / 2) >= paddleYpos && xpos <= paddleXpos + paddleWidth)
	{	//Tương tự bên trên cho thanh bên phải
		xpos = paddleXpos - destRect.w - 1;
		velocityX = -velocityX;
		if (speed <= 30)
		{
			velocityX *= 1 + accelerate;
			velocityY *= 1 + accelerate;
			speed++;
		}
		return true;
	}
	return false;
}
//Hàm di chuyển trái banh
void BallObject::move(PaddleObject* p, vector<vector<Brick*>>& table) {
	if (velocity == 0) {
		float startAngle = 120 * PI / 180;
		velocity = 2.9;
		velocityX = velocity * cos(startAngle);
		velocityY = velocity * sin(startAngle);
	}
	xpos += velocityX;	//Cộng theo vận tốc
	ypos += velocityY;
	isTouch(p);	//Xét sự va chạm
	Brick* target = isTouchWithTarget(table);
	if (target != NULL) {
		if (target->getType() == "reward" && !target->isCollected())
			target->setCollected();
		else if (target->getHp() == 1) {
			score1 += 10;
			int targetX = target->getTableX();
			int targetY = target->getTableY();
			table[(size_t) targetX][(size_t) targetY] = NULL;
			if (target->getLoot() < 4) {
				table[(size_t) targetX][(size_t) targetY] = new Reward(targetY, targetX, 50, 50, target->getLoot(), 0);
				table[(size_t) targetX][(size_t) targetY]->render();
			}
		}
		target->updateHpImg();
	}
}
//Hàm kiểm tra va chạm
int BallObject::rectCollided(float cx, float cy, float radius, int rx, int ry, int rw, int rh) {
	// temporary variables to set edges for testing
	float testX = cx;
	float testY = cy;
	int edge = -1;
	//0: left edge
	//1: right edge
	//2: top edge
	//3: bottom edge

	// which edge is closest?
	if (cx < rx) { // test left edge
		testX = rx;
		edge = 0;
	}
	else if (cx > rx + rw) {  // right edge
		testX = rx + rw;
		edge = 1;
	}
	if (cy < ry) { // top edge
			testY = ry;
			edge = 2;
		}
	    else if (cy > ry + rh) { // bottom edge
			testY = ry + rh;
			edge = 3;
		}

	// get distance from closest edges
	float distX = cx - testX;
	float distY = cy - testY;

	// if the distance is less than the radius, collision!
	if (sqrt((distX * distX) + (distY * distY)) <= BALL_RADIUS)
		return edge;
	return -1;
}
void BallObject::setAngle(float deg) {
	float curV = velocity;
	velocityX = curV * cosf(deg);
	velocityY = curV * sinf(deg);
}
/*
set goc trai banh khi cham vo tung phan tren paddle
|   | strike3
|   | strike2
|mid| strike1
|   | strike2
|   | strike3
*/
void BallObject::strikeAngle(PaddleObject* paddle) {
	float layer1 = 26; float layer2 = 25;
	float ballX = xpos + BALL_RADIUS / 2;
	float mid = paddle->getPaddleXpos() + PADDLE_HEIGHT / 2;
	float halfPI = PI / 2; // when someone ate your pie
	srand(time(NULL));
	float x = rand() % 10 + 0;
	// Goc bat khac nhau cho trai banh
	float strike1 = (14 + x) * PI / 180; float strike2 = (25 + x) * PI / 180; float strike3 = (57 + x) * PI / 180;
	if (mid - layer1 <= ballX && ballX <= mid)
		setAngle(-halfPI - strike1);
	else if (mid < ballX && ballX < mid + layer1)
		setAngle(-halfPI + strike1);

	else if (mid - layer1 - layer2 <= ballX && ballX <= mid - layer1)
		setAngle(-halfPI - strike2);
	else if (mid + layer1 <= ballX && ballX <= mid + layer1 + layer2)
		setAngle(-halfPI + strike2);

	else if (paddle->getPaddleXpos() <= ballX && ballX < mid - layer1 - layer2)
		setAngle(-halfPI - strike3);
	else if (mid + layer1 + layer2 < ballX && ballX <= paddle->getPaddleXpos() + PADDLE_HEIGHT)
		setAngle(-halfPI + strike3);
}
//Hàm kiểm tra chạm thanh trượt
bool BallObject::isTouch(PaddleObject* paddle) {

	if (ypos <= 0) {
		//Đụng trên thì dội ngược lại
		velocityY = -velocityY;
		return true;
	} else if (xpos <= 0 || xpos >= WINDOW_WIDTH - BALL_RADIUS) {
		velocityX = -velocityX;
		return true;
	}
	int paddleXpos = paddle->getPaddleXpos();
	int paddleYpos = paddle->getPaddleYpos();
	int edgeRes = rectCollided(xpos, ypos, BALL_RADIUS + 0.0, paddleXpos, paddleYpos, PADDLE_HEIGHT, PADDLE_WIDTH);
	if (edgeRes == 2) {
		if (speed <= 100) {	//Tăng theo gia tốc, tối đa 100 lần
			velocity *= 1 + accelerate;
			speed++;
		}
		strikeAngle(paddle);
		return true;
	}
	return false;
}
//Hàm trả về trạng thái vật cản sau khi va chạm
Brick* BallObject::isTouchWithTarget(vector<vector<Brick*>> table) {
	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < table[i].size(); j++) {
			Brick* target = table[i][j];
			if (target == NULL || (target->getType() == "reward" && target->isCollected())) continue;
			int edge = rectCollided(xpos + (BALL_RADIUS + 0.0) / 2, ypos + (BALL_RADIUS + 0.0) / 2, (BALL_RADIUS / 2) + 0.0, target->getX(), target->getY(), target->getW(), target->getH());
			if (0 <= edge && edge < 4) {
				if ((target->getType() == "reward" && !target->isCollected()))
					return target;
				else if (edge == 0) {
					if (velocityX < 0) return NULL;
					velocityX = -velocityX;
				} else if (edge == 1) {
					if (velocityX > 0) return NULL;
					velocityX = -velocityX;
				} else if (edge == 2) {
					if (velocityY < 0) return NULL;
					velocityY = -velocityY;
				} else if (edge == 3) {
					if (velocityY > 0) return NULL;
					velocityY = -velocityY;
				}
				return target;
			}	
		}
	}
	return NULL;
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
//Hàm kiểm tra trái banh di ra ngoài
int BallObject::isOut() {
	if (ypos > WINDOW_HEIGHT + 5) {
		srand(time(NULL));
		float A[2] = { 120 * PI / 180 , 60 * PI / 180 };
		int x = rand() % 2;
		velocity = 2.9;
		velocityX = velocity * cos(A[x]);
		velocityY = velocity * sin(A[x]);
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
		ran = (float)s / 20;
	}
	return ran;
}
//Hàm set mạng
void BallObject::setLife(int x)
{
	life = x;
}

