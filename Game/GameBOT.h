#pragma once
#include "AbstractGame.h"
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
#define MAX_SCORE 10
//Tương tự Game.cpp không khác gì hết
class GameBOT : public AbstractGame
{
public:
	GameBOT();
	~GameBOT();
	void init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen,int savegame);
	void update();
	void render();
	void handleEvents();
	void clean();
};

