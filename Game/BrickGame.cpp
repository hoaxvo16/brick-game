#include "Rect.h"
#include "textureManager.h"
#include "PaddleObject.h"
#include "BallObject.h"
#include "message.h"
PaddleObject* paddle_brick = NULL;
BallObject* ball_brick = NULL;
SDL_Texture* background_brick = NULL;
SDL_Texture* life = NULL;
SDL_Texture* scoretext = NULL;
//SDL_Renderer* Game::rendered = NULL;
//Biến rendered được dùng để render(lưu lại những hình vẽ và vị trí của mỗi object, chờ cơ hội để bộc phát)
message* scoreShow_brick = NULL;	//Cái tỉ số bên tay trái á
	//Này bên tay phải
message* resultGame_brick = NULL;		//Cái này nếu thua hay thắng thì nó sẽ hiện lên

float xball = WINDOW_WIDTH / 2;
float yball = WINDOW_HEIGHT - 100;
message* lifenum = NULL;

int xpaddle = WINDOW_WIDTH / 2 - 80;
int ypaddle = WINDOW_HEIGHT - 10;
BrickGame::BrickGame() {

}
BrickGame::~BrickGame() {

}
void BrickGame::initTable() {
	srand(time(NULL));
	table.resize(5);
	for (size_t i = 0; i < 5; i++)
		table[i].resize(10);
	for (size_t i = 0; i < 30;) {
		size_t ranX = rand() % 10;
		size_t ranY = rand() % 5;
		Brick* brick = new Rect(0, "PNGFile/rect.png", ranX * 80, (ranY + 1) * 60, 80, 60, "rect", 1, true);
		if (table[ranY][ranX] == NULL) {
			table[ranY][ranX] = brick;
			i++;
		}
	}
}
void BrickGame::init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flag = 0;	//flag = 0 báo hiệu cho việc chúng ta sẽ sử dụng cửa sổ chứ không phải fullscreen
	if (fullscreen) {
		//Còn nếu user cứ thích đòi fullscreen thì chỉnh lại thôi (mặc dù chương trình không cho hỏi :v)
		flag = SDL_WINDOW_FULLSCREEN;	// <=> flag = 1;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		//Hàm khởi tạo cho việc sử dụng thư viện SDL
		//Nó trả về 0 tức là ta được phép sử dụng, không thì thôi bỏ!
		//SDL_INIT_EVERTHING là tham số để khởi tạo mọi thứ từ rendered, surface, ...
		std::cout << "Subsystem Initialised! ..." << std::endl;
		//Này in ra để coi SDL có khởi tạo thành công khônng
		window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flag);
		//Bắt đầu khởi tạo cửa sổ (hàm này chỉ có nhiệm vụ vẽ ra cái cửa sổ thôi)
		//Những tham số y chanh ở trên
		if (window) {
			//Nếu khởi tạo thành công thì nó khác NULL
			std::cout << "Window created!" << std::endl;	//In ra chơi thôi
		}
		rendered = SDL_CreateRenderer(window, -1, 0);
		//Trên cửa sổ cần có một công cụ là một biến SDL_Rendered để lo việc vẽ vời ong bướm
		//Không có hàm này thì cửa sổ chỉ có mỗi cái khung thôi
		if (rendered) {
			//Nếu khởi tạo công cụ thành công thì nó sẽ khác NULL
			SDL_SetRenderDrawColor(rendered, 255, 255, 255, 255); //Vẽ toàn bộ nền bên trong cửa sổ thành màu trắng (theo mã màu RGB)
			std::cout << "Rendered created!" << std::endl;
		}
		isRunning = true;	//Biến sẽ kiểm tra rằng trò chơi có đang chạy hay không
	} else {
		isRunning = false; //Nếu tất cả mọi thử ở trên thất bại thì thôi nghỉ game
	}
	//if (savegame == 1)
	//{
	//	ifstream save;
	//	save.open("savegame.txt");
	//	save >> xball;
	//	save >> yball;
	//	save >> xpaddle;
	//	save >> ypaddle;
	//}
	paddle_brick = new PaddleObject("PNGFile/paddlebrick.png", xpaddle, ypaddle);
	ball_brick = new BallObject("PNGFile/Ball.png", xball, yball);
	/*Truy cập file hình ở bên ngoài thư mục chứa project
	2 tham số sau chỉ vị trí sẽ xuất hình trên cửa sổ*/
	background_brick = textureManager::loadTexture("PNGFile/brick.jpg");
	life = textureManager::loadTexture("PNGFile/life.png");	
	scoretext = textureManager::loadTexture("PNGFile/score.png");//Truy cập vào file hình chứa background
	initTable();
	
	scoreShow_brick = new message();
	lifenum = new message();
	resultGame_brick = NULL;
	lifenum->setText(3);
	/*Khởi tạo các biến để ghi dạng text lên cửa sổ*/
	
}
void BrickGame::update() {
	paddle_brick->updateforbrick();	//Khác biệt duy nhất với Game.cpp :)))
	ball_brick->move(paddle_brick, table);
	ball_brick->update();
	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < table[i].size(); j++) {
			if (table[i][j] != NULL) 
				table[i][j]->update();
		}
	}
}
void BrickGame::render() {
	SDL_RenderClear(rendered);
	SDL_Rect scorepic;
	SDL_Rect lifepic;
	lifepic.w = 80;
	lifepic.h = 40;
	lifepic.x = WINDOW_WIDTH - lifepic.w;;
	lifepic.y = 0;
	scorepic.w = 80;
    scorepic.h = 25;
	scorepic.x = scorepic.y = 0;
	SDL_RenderCopy(BrickGame::rendered, background_brick, NULL, NULL);
	SDL_RenderCopy(BrickGame::rendered, life, NULL, &lifepic);
	SDL_RenderCopy(BrickGame::rendered, scoretext, NULL, &scorepic);
	paddle_brick->render();
	ball_brick->render();
	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < table[i].size(); j++) {
			if (table[i][j] != NULL)
				table[i][j]->render();
		}
	}

	scoreShow_brick->render(300, 50, 50, 25);
	lifenum->render(lifepic.x - 10, 0, 40, 20);
	if (resultGame_brick != NULL) {
		resultGame_brick->render(300, 300, 50, 200);
	}

	
	SDL_RenderPresent(BrickGame::rendered);
	if (!isRunning) {
		SDL_Delay(2000);
	}
}
void BrickGame::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	int xMouse, yMouse;
	switch (event.type) {
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&xMouse, &yMouse);
		paddle_brick->moveWithMouse(xMouse);
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			isRunning = false;
			break;
		default:
			break;
		}
	}
}
void BrickGame::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(rendered);
	SDL_Quit();
	std::cout << "Game Cleansed!" << std::endl;
}
