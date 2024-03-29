﻿#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "AbstractGame.h"
#define WINDOW_HEIGHT 600	//Chiều cao cửa sổ
#define WINDOW_WIDTH 800	//Chiều rộng cửa sổ
#define MAX_SCORE 10	//Điểm tối đa cho mỗi player
class Game : public AbstractGame
{
public:
	Game();
	~Game();
	void init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen,int savegame);
	//Khởi tạo cửa sổ với title là tên Cửa sổ
	//xpos, ypos là nơi đặt cửa sổ trên màn hình
	//width, height là size của cửa sổ
	//fullscreen là có muốn fullsreen hông :))
	void update();	//Điều hành trò chơi, cập nhật vị trí của các object hiện tại
	void render();	//Cập nhật ở trên xong rồi thì vẽ ra
	void handleEvents();	//Giải quyết sự kiện bên ngoài (VD: user đập bàn phím)
    void clean();	//Xóa hết, xóa sạch, xóa tất
};

