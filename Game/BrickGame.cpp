#include "Rect.h"
#include"Reward.h"
#include "textureManager.h"
#include "PaddleObject.h"
#include "BallObject.h"
#include "message.h"
PaddleObject* paddle_brick = NULL;
BallObject* ball_brick = NULL;
SDL_Texture* background_brick = NULL;
SDL_Texture* life = NULL;
SDL_Texture* scoretext = NULL;
Skills* skillExe = NULL;
//SDL_Renderer* Game::rendered = NULL;
//Biến rendered được dùng để render(lưu lại những hình vẽ và vị trí của mỗi object, chờ cơ hội để bộc phát)
message* scoreShow_brick = NULL;	//Cái tỉ số bên tay trái á
	//Này bên tay phải
message* resultGame_brick = NULL;		//Cái này nếu thua hay thắng thì nó sẽ hiện lên

float xball = WINDOW_WIDTH / 2;
float yball = WINDOW_HEIGHT - 300;
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
		int loot = rand() % 10 + 1;
		Brick* brick = new Rect("PNGFile/rect3.png", ranX, ranY, 80, 60, "rect", 3, loot);
		if (table[ranY][ranX] == NULL) {
			table[ranY][ranX] = brick;
			i++;
		}
	}
}
void BrickGame::initSave(){
	int newlife;
	int newscore;
	int vx, vy;
	char c;
	int x, y, hp, loot,collected;
	string type;
	ifstream filein;
	filein.open("PNGFile/savegame.txt");
	filein >> newlife >> newscore >> xball >> yball>>vx>>vy >> xpaddle >> ypaddle;
	table.resize(5);
	for (size_t i = 0; i < 5; i++)
		table[i].resize(10);
	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < table[i].size(); j++) {
			filein >> x >> c >> y >> c >> hp >> c >> loot >> c >> collected >> c;
			getline(filein, type,' ');
			if (type == "reward")
			{
				if (collected == 1)
				{
					Brick* brick = new Reward(x, y, 50, 50, loot,collected);
					brick->setCollected();
					table[i][j] = brick;
				}
				else
				{
					x = x / 80;
					y = y / 60 - 1;
					Brick* brick = new Reward(x, y, 50, 50, loot,collected);
					table[i][j] = brick;
				}
			}
			else if (type=="rect")
			{
				x = x / 80;
				y = y / 60 - 1;
				string path;
				if(hp==3)
				    path = "PNGFile/rect3.png";
				else if(hp==2)
					path= "PNGFile/rect2.png";
				else if (hp == 1)
					path = "PNGFile/rect1.png";
				Brick* brick = new Rect(path, x, y, 80, 60, "rect", hp, loot);
				table[i][j] = brick;
			}
		}
	}
	filein.close();
	paddle_brick = new PaddleObject("PNGFile/paddlebrick.png", xpaddle, ypaddle);
	ball_brick = new BallObject("PNGFile/Ball.png", xball, yball);
	ball_brick->setLife(newlife);
	ball_brick->setScore(newscore);
	background_brick = textureManager::loadTexture("PNGFile/brick.jpg");
	life = textureManager::loadTexture("PNGFile/life.png");
	scoretext = textureManager::loadTexture("PNGFile/score.png");//Truy cập vào file hình chứa background
	scoreShow_brick = new message();
	lifenum = new message();
	resultGame_brick = NULL;
	ball_brick->setVx(vx);
	ball_brick->setVy(vy);
}
void BrickGame::init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen,int savegame) {
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
	if (savegame == 1)
	{
		initSave();
	}
	else
	{
		paddle_brick = new PaddleObject("PNGFile/paddlebrick.png", xpaddle, ypaddle);
		ball_brick = new BallObject("PNGFile/Ball.png", xball, yball);
		ball_brick->setLife(3);
		/*Truy cập file hình ở bên ngoài thư mục chứa project
		2 tham số sau chỉ vị trí sẽ xuất hình trên cửa sổ*/
		background_brick = textureManager::loadTexture("PNGFile/brick.jpg");
		life = textureManager::loadTexture("PNGFile/life.png");
		scoretext = textureManager::loadTexture("PNGFile/score.png");//Truy cập vào file hình chứa background
		initTable();
		scoreShow_brick = new message();
		lifenum = new message();
		resultGame_brick = NULL;
		ball_brick->setVx(-1.8);
		ball_brick->setVy(1.8);
	}
	/*Khởi tạo các biến để ghi dạng text lên cửa sổ*/
}

void BrickGame::update() {
	paddle_brick->updateforbrick();	//Khác biệt duy nhất với Game.cpp :)))
	ball_brick->move(paddle_brick, table);
	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < table[i].size(); j++) {
			if (table[i][j] != NULL) {
				if (table[i][j]->getType() == "reward" && table[i][j]->isCollected() == 1) {
					table[i][j]->updateReward();
					int loot = table[i][j]->isTouchWithPaddle(paddle_brick);
					if (loot != 0) {
						skillExe = new Skills(table, loot, j);
						table[i][j] = NULL;
					} else if (table[i][j]->isOut())
						table[i][j] = NULL;
				}
				else table[i][j]->update();
			}
		}
	}
	ball_brick->update();
	if (skillExe != NULL) {
		skillExe->update();
		if (SDL_GetTicks() - skillExe->getStart() > skillExe->getDuration())
			skillExe = NULL;
	}

	int x = ball_brick->getScore_1();
	scoreShow_brick->setText(x);
	int new_life = ball_brick->getLife();
	if (isWin())
	{
		cleanSave();
		board.initScore();
		board.add(ball_brick->getScore_1());
		resultGame_brick = new message();
		resultGame_brick->setText("You Win");
		isRunning = false;
	}
	if (new_life == 0)
	{
		cleanSave();
		board.initScore();
		board.add(ball_brick->getScore_1());
		resultGame_brick = new message();
		resultGame_brick->setText("You Lost");
		isRunning = false;
	}
	lifenum->setText(new_life);
}
void BrickGame::render() {
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
	SDL_RenderCopy(BrickGame::rendered, background_brick, NULL, NULL);
	SDL_RenderCopy(BrickGame::rendered, life, NULL, &lifepic);
	SDL_RenderCopy(BrickGame::rendered, scoretext, NULL, &scorepic);
	paddle_brick->render();
	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < table[i].size(); j++) {
			if (table[i][j] != NULL)
				table[i][j]->render();
		}
	}
	ball_brick->render();
	if (skillExe != NULL) skillExe->render();
	scoreShow_brick->render(100, 0, 50,40);
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
			saveGame();
			isRunning = false;
			break;
		default:
			break;
		}
	}
}
void BrickGame::saveGame()
{
	ofstream fileout;
	fileout.open("PNGFile/savegame.txt");
	fileout << ball_brick->getLife() << endl;
	fileout << ball_brick->getScore_1() << endl;
	fileout << ball_brick->getX() << endl;
	fileout << ball_brick->getY() << endl;
	fileout << ball_brick->getVx() << endl;
	fileout << ball_brick->getVy() << endl;
	fileout << paddle_brick->getPaddleXpos()<< endl;
	fileout << paddle_brick->getPaddleYpos() << endl;
	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < table[i].size(); j++) {
			Brick* temp = table[i][j];
			if (temp == NULL)
				fileout << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "," << "No ";
			else
			{
				if (temp->getType() == "reward")
					 fileout << temp->getDestx() << "," << temp->getDesty() << "," << temp->getHp() << "," << temp->getLoot() << "," << temp->isCollected() << "," << temp->getType() << " ";
				else
					fileout << temp->getX() << "," << temp->getY() << "," << temp->getHp() << "," << temp->getLoot() << "," << temp->isCollected() << "," << temp->getType() << " ";
			}
		}
		fileout << endl;
	}
	fileout.close();
}
void BrickGame::cleanSave()
{
	ofstream fileout;
	fileout.open("PNGFile/savegame.txt",ios::trunc);
	fileout << "";
	fileout.close();
}
bool BrickGame::isWin()
{
	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < table[i].size(); j++) {
			if (table[i][j] != NULL&&table[i][j]->getType()=="rect")
				return false;
		}
	}
	return true;
}
void BrickGame::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(rendered);
	SDL_Quit();
	std::cout << "Game Cleansed!" << std::endl;
}
