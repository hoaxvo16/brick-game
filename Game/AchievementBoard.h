#pragma once
#include"message.h"
#include"textureManager.h"
#include"AbstractGame.h"
#include<fstream>
#include<vector>
using namespace std;
class AchievementBoard:public AbstractGame
{
	vector<int>score;
	vector<message*>mess;
public:
	void Sort();
	void init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen, int savegame);
	void update();
	void render();
	void handleEvents();
	void clean();
	void add(int x);
	bool CheckEmpty();
	void initScore();
	void delRep();
};

