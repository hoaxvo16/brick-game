#pragma once
#include "PaddleObject.h"
#include "BallObject.h"
class BotPaddle : public PaddleObject
{
public:
	BotPaddle(const char* paddleSheet, int x, int y);
	~BotPaddle();
	void updateBOT(BallObject *ball);
	void updateBrickBot(BallObject* ball, vector<vector<Brick*>> table);
};

