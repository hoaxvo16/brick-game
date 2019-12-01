#include "textureManager.h"
#include "SDL_bits.h"
SDL_Texture* textureManager::loadTexture(const char* file_path) {
	SDL_Surface* tmpSurface = IMG_Load(file_path);	//Tạo một mặt phẳng để lưu lại hình vẽ trong file
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::rendered, tmpSurface);
	//Tạo một hình vẽ hoàn chỉnh từ mặt phẳng đó đem vào rendered
	SDL_FreeSurface(tmpSurface);	//Giải phóng cái surface đã sử dụng
	return texture;
}