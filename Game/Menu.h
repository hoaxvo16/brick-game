#pragma once
#include"AbstractGame.h"
#include"textureManager.h"
#include<fstream>
#include<string>
using namespace std;
int drawMenu(AbstractGame* gameWindow, const int FPS);
int drawSubMenu(AbstractGame* gameWindow, const int FPS);
int drawSubMenuNotSave(AbstractGame* gameWindow, const int FPS);
bool isSaveGame();
void highScore();

