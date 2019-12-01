#pragma once
#include "Game.h"
#include <string>
#include "SDL_ttf.h"
class message
{
private:
	std::string text = "";	//Chuỗi sẽ in ra trên màn hình
	SDL_Color color = { 255,0,0 };	//Màu của text, đang để màu đỏ
public:
	message();
	~message();
	void setText(const int mark);	//Set text để in ra số
	void setText(const std::string str);	//Set text để in ra chuỗi
	SDL_Texture *showText();	//Tạo hình ảnh của cái text
	void render(int xpos, int ypos, int h, int w);	//Ren lên màn hình theo size và position
};

