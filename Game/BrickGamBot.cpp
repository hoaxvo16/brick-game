#include "BrickGamBot.h"
#include "Rect.h"
#include"Reward.h"
#include "textureManager.h"
#include "BotPaddle.h"
#include "BallObject.h"
#include "message.h"
BotPaddle* paddle_brickBOT = NULL;
BallObject*  ball_brickBOT = NULL;
SDL_Texture* background_brickBOT = NULL;
SDL_Texture* lifeBOT = NULL;
SDL_Texture* scoretextBOT = NULL;
Skills* skillExe1BOT = NULL;
Skills* skillExe2BOT = NULL; // 2 more for missile skill
Skills* skillExe3BOT = NULL;
//SDL_Renderer* Game::rendered = NULL;
//Biến rendered được dùng để render(lưu lại những hình vẽ và vị trí của mỗi object, chờ cơ hội để bộc phát)
message* scoreShow_brickBOT = NULL;	//Cái tỉ số bên tay trái á
	//Này bên tay phải
message* resultGame_brickBOT = NULL;		//Cái này nếu thua hay thắng thì nó sẽ hiện lên

float xballBOT = WINDOW_WIDTH / 2;
float yballBOT = WINDOW_HEIGHT - 350;
message* lifenumBOT = NULL;

int xpaddleBOT = WINDOW_WIDTH / 2 - 80;
int ypaddleBOT = WINDOW_HEIGHT - 10;

BrickGameBot::BrickGameBot() {

}
BrickGameBot::~BrickGameBot() {

}
void BrickGameBot::initTable() {
	srand(time(NULL));
	table.resize(5);
	for (size_t i = 0; i < 5; i++)
		table[i].resize(10);
	for (size_t i = 0; i < 30;) {
		size_t ranX = rand() % 10;
		size_t ranY = rand() % 5;
		int loot = rand() % 10 + 1;
		Brick* brick = new Rect("PNGFile/rect3.png", ranX, ranY, 80, 60, "rect", 3, loot);
		if (table[ranY][ranX] == NULL) {
			table[ranY][ranX] = brick;
			i++;
		}
	}
}
void BrickGameBot::init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen, int savegame) {
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
	}
	else {
		isRunning = false; //Nếu tất cả mọi thử ở trên thất bại thì thôi nghỉ game
	}
	paddle_brickBOT = new BotPaddle("PNGFile/paddlebrick.png", xpaddleBOT, ypaddleBOT);
	 ball_brickBOT = new BallObject("PNGFile/Ball.png", xballBOT, yballBOT);
	 ball_brickBOT->setLife(3);
	/*Truy cập file hình ở bên ngoài thư mục chứa project
	2 tham số sau chỉ vị trí sẽ xuất hình trên cửa sổ*/
	background_brickBOT = textureManager::loadTexture("PNGFile/brick.jpg");
	lifeBOT = textureManager::loadTexture("PNGFile/life.png");
	scoretextBOT = textureManager::loadTexture("PNGFile/score.png");//Truy cập vào file hình chứa background
	initTable();
	scoreShow_brickBOT = new message();
	lifenumBOT = new message();
	resultGame_brickBOT = NULL;
	 ball_brickBOT->setVx(-1.8);
	 ball_brickBOT->setVy(1.8);
	/*Khởi tạo các biến để ghi dạng text lên cửa sổ*/
}

void BrickGameBot::update() {
	paddle_brickBOT->updateBrickBot( ball_brickBOT);//Khác biệt duy nhất với Game.cpp :)))
	 ball_brickBOT->move(paddle_brickBOT, table);
	 for (size_t i = 0; i < table.size(); i++) {
		 for (size_t j = 0; j < table[i].size(); j++) {
			 if (table[i][j] != NULL) {
				 if (table[i][j]->getType() == "reward" && table[i][j]->isCollected() == 1) {
					 table[i][j]->updateReward();
					 int loot = table[i][j]->isTouchWithPaddle(paddle_brickBOT);
					 if (loot != 0) {
						 if (loot == 3) {
							 skillExe1BOT = new Skills(table, loot, j, 1, ball_brickBOT);
							 skillExe2BOT = new Skills(table, loot, j, 2, ball_brickBOT);
							 skillExe3BOT = new Skills(table, loot, j, 3, ball_brickBOT);
						 }
						 else skillExe1BOT = new Skills(table, loot, j, -1, ball_brickBOT);

						 table[i][j] = NULL;
					 }
					 else if (table[i][j]->isOut())
						 table[i][j] = NULL;
				 }
				 else table[i][j]->update();
			 }
		 }
	 }
	 ball_brickBOT->update();
	 if (skillExe1BOT != NULL) {
		 if (skillExe1BOT->getLoot() == 3)
			 skillExe1BOT->updateMissile(table,ball_brickBOT);
		 else
			 skillExe1BOT->update();
		 if (skillExe1BOT->getStart() != 0 && SDL_GetTicks() - skillExe1BOT->getStart() > skillExe1BOT->getDuration())
			 skillExe1BOT = NULL;
	 }
	 if (skillExe2BOT != NULL) {
		 skillExe2BOT->updateMissile(table,ball_brickBOT);
		 if (skillExe2BOT->getStart() != 0 && SDL_GetTicks() - skillExe2BOT->getStart() > skillExe2BOT->getDuration())
			 skillExe2BOT = NULL;
	 }
	 if (skillExe3BOT != NULL) {
		 skillExe3BOT->updateMissile(table,ball_brickBOT);
		 if (skillExe3BOT->getStart() != 0 && SDL_GetTicks() - skillExe3BOT->getStart() > skillExe3BOT->getDuration())
			 skillExe3BOT = NULL;
	 }

	 int x = ball_brickBOT->getScore_1();
	 scoreShow_brickBOT->setText(x);
	 int new_life = ball_brickBOT->getLife();
	 if (isWin())
	 {
		 resultGame_brickBOT = new message();
		 resultGame_brickBOT->setText("Bot Win");
		 isRunning = false;
	 }
	 if (new_life == 0)
	 {
		 resultGame_brickBOT = new message();
		 resultGame_brickBOT->setText("Bot Lose");
		 isRunning = false;
	 }
	 lifenumBOT->setText(new_life);
}
void BrickGameBot::render() {
	SDL_RenderClear(rendered);
	SDL_Rect scorepic;
	SDL_Rect lifepic;
	lifepic.w = 80;
	lifepic.h = 40;
	lifepic.x = WINDOW_WIDTH - lifepic.w;;
	lifepic.y = 0;
	scorepic.w = 100;
	scorepic.h = 40;
	scorepic.x = scorepic.y = 0;
	SDL_RenderCopy(BrickGameBot::rendered, background_brickBOT, NULL, NULL);
	SDL_RenderCopy(BrickGameBot::rendered, lifeBOT, NULL, &lifepic);
	SDL_RenderCopy(BrickGameBot::rendered, scoretextBOT, NULL, &scorepic);
	paddle_brickBOT->render();
	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < table[i].size(); j++) {
			if (table[i][j] != NULL)
				table[i][j]->render();
		}
	}
	 ball_brickBOT->render();
	 if (skillExe1BOT != NULL) skillExe1BOT->render();
	 if (skillExe2BOT != NULL) skillExe2BOT->render();
	 if (skillExe3BOT != NULL) skillExe3BOT->render();
	scoreShow_brickBOT->render(100, 0, 50, 40);
	lifenumBOT->render(lifepic.x - 10, 0, 40, 20);
	if (resultGame_brickBOT != NULL) {
		resultGame_brickBOT->render(300, 300, 50, 200);
	}
	SDL_RenderPresent(BrickGameBot::rendered);
	if (!isRunning) {
		SDL_Delay(2000);
	}
}
void BrickGameBot::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
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
bool BrickGameBot::isWin()
{
	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < table[i].size(); j++) {
			if (table[i][j] != NULL && table[i][j]->getType() == "rect")
				return false;
		}
	}
	return true;
}
void BrickGameBot::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(rendered);
	SDL_Quit();
	std::cout << "Game Cleansed!" << std::endl;
}
