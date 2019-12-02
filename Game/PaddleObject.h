#pragma once
#include "Game.h"
#include "textureManager.h"
#define PADDLE_WIDTH 13
#define PADDLE_HEIGHT 152
//Cái size của thanh chắn
#define SRC_RECT_X 0
#define SRC_RECT_Y 0
//Đây là tọa độ hình chữ nhật để nhận hình ảnh từ file
#define SPEED 8
//Tốc độ của thanh
class PaddleObject
{
protected:
	int xpos, ypos;	//Thanh có tọa độ
	SDL_Texture* paddleTexture;	//Thanh có hình ảnh, hoa văn
	SDL_Rect destRect;	//Hình chữ nhật mà dựa trên đó để đọc(srcRect) và vẽ(destRect) cái thanh
public:
	PaddleObject() {}
	PaddleObject(const char* paddleSheet, int x, int y);
	//Khởi tạo thanh bằng cách đọc file và tọa độ hình sẽ xuất hiện đầu
	~PaddleObject();
	void moveUp();
	void moveDown();
	void update();
	void updateforbrick();
	void render();
	void moveLeft();
	void moveRight();
	void moveWithMouse(int xMouse);
	int getPaddleXpos();	//Getter lấy tọa độ thanh
	int getPaddleYpos();
};

