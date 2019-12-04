﻿#pragma once
#include "Game.h"
#include "PaddleObject.h"
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define BALL_RADIUS 20	//Size của quả banh
#define INIT_SPEED_X 2.9	//Vận tốc x ban đầu
#define INIT_SPEED_Y 1.9	//Vận tộc y ban đầu
#define PI 3.14159
class BallObject
{
private:

	float xpos, ypos;	//Tọa độ đỉnh góc trái của hình chữ nhật chứa hình tròn
	SDL_Texture* ballTexture;	//Hình vẽ của quả banh
	SDL_Rect srcRect,destRect;	//Hình chữ nhật để đọc và vẽ quả banh lên cửa sổ
	float velocityX, velocityY;	//Vận tốc x, y của quả banh
	int score1 = 0;	//Điểm của player 1
	int score2 = 0;	//Điểm của player 2
	int life = 3;
public:
	BallObject(const char* ballsheet, int x, int y);
	~BallObject();
	void update();
	void render();
	void move(PaddleObject* p1, PaddleObject* p2);
	void move(PaddleObject* p);
	//Di chuyển quả banh
	bool isTouch(PaddleObject *paddle1, PaddleObject *paddle2);
	bool isTouch(PaddleObject* paddle);
	float getV();
	void setAngle(float deg);
	void strikeAngle(PaddleObject* paddle);
	int rectCollided(float cx, float cy, float radius, int rx, int ry, int rw, int rh);
	//Xét sự va chạm
	int isOut();
	//Banh ra ngoài chưa?
	int getScore_1()
	{
		return score1;
	}
	int getScore_2()
	{
		return score2;
	}
	int getCenterOfBall()	//Lấy tung độ tại tâm quả banh
	{
		return ypos + BALL_RADIUS / 2;
	}
	int getLife()
	{
		return life;
	}
};

