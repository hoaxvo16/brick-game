#include "message.h"
message::message()
{
}
message::~message()
{
}
void message::setText(const int mark)
{
	text = std::to_string(mark);	//Đổi số thành chuỗi rồi gán cho text
}
void message::setText(const std::string str)
{
	text = str;
}
SDL_Texture* message::showText()
{
	
	TTF_Font* Sans = TTF_OpenFont("Fonts/goodtimes.ttf", 32);	//Lấy font có sẵn trong mục project và set cỡ chữ
	if (Sans == NULL)
	{
		std::cout << TTF_GetError() << std::endl;	//Không lấy được thì in ra lỗi
		return NULL;
	}
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans,text.c_str(), color);	//In chữ đó lên mặt phẳng
	SDL_Texture* mess= SDL_CreateTextureFromSurface(AbstractGame::rendered, surfaceMessage);	//Lấy mặt phẳng đó vào render
	SDL_FreeSurface(surfaceMessage);	//Giải phóng cái surface đi
	TTF_CloseFont(Sans);	//Giải phóng font!
	return mess;
}
void message::render(int xpos, int ypos, int h, int w)
{
	if (TTF_Init() == -1)	//Để làm việc với font thì cần hàm này để khởi tạo trước
	{
		std::cout << TTF_GetError() << std::endl;	//Nếu không được thì xuất ra lí do
		return;
	}
	SDL_Rect destRec;	//Hình chữ nhật chứa chữ để vẽ lên cửa sổ
	destRec.x = xpos;
	destRec.y = ypos;
	destRec.h = h;
	destRec.w = w;
	SDL_RenderCopy(Game::rendered, showText(), NULL, &destRec);	//Quăng cái hình đó vô render
}
