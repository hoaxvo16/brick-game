#pragma once
#include "Game.h"
class textureManager {
public:
	static SDL_Texture* loadTexture(const char* file_path);
	//Biến static đọc file ảnh
	//Dùng static để khi sử dụng không cần khởi tạo object của class này
};

