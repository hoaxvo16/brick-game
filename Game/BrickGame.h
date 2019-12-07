#pragma once
#include "AbstractGame.h"
#include <vector>
#include<fstream>
#include "Brick.h"
using namespace std;
#define WINDOW_HEIGHT 650	//Chiều cao cửa sổ
#define WINDOW_WIDTH 800	//Chiều rộng cửa sổ
#define MAX_SCORE 10	//Điểm tối đa cho mỗi player
class BrickGame : public AbstractGame
{
private:
	vector<vector<Brick*>> table;
public:
	BrickGame();
	~BrickGame();
	void initTable();
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

