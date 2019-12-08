#include "AchievementBoard.h"
SDL_Texture* background_board = NULL;
message* temp = NULL;
void AchievementBoard::Sort()
{
	for (int i = 0; i < score.size()-1; i++)
	{
		for (int j = i + 1; j < score.size(); j++)
			if (score[i] < score[j])
				swap(score[i], score[j]);
	}
}
void AchievementBoard::initScore()
{
	if (CheckEmpty())
	{
		score.resize(0);
		mess.resize(0);
	}
	else
	{
		ifstream filein;
		int x;
		filein.open("PNGFile/savescore.txt");
		while (!filein.eof())
		{
			filein >> x;
			score.push_back(x);
		}
		filein.close();
		delRep();
	}
}
void AchievementBoard::init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen,int savegame)
{
	initScore();
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
	//SDL_Surface* tmpSurface = IMG_Load("PNGFile/title.png");	//Tạo một mặt phẳng để lưu lại hình vẽ trong file
	//SDL_Texture* texture = SDL_CreateTextureFromSurface(AchievementBoard::rendered, tmpSurface);
	background_board = textureManager::loadTexture("PNGFile/title.png");
	mess.resize(score.size());
	for (int i = 0; i < score.size(); i++)
	{
		temp = new message();
		temp->setText(score[i]);
		mess[i] = temp;
	}
}
void AchievementBoard::delRep()
{

	for (int i = 0; i < score.size() - 1; i++)
	{
		for (int j = i + 1; j < score.size(); j++)
			if (score[i] == score[j])
				score.erase(score.begin() + i);
	}
}
void AchievementBoard::add(int x)
{
	score.push_back(x);
	Sort();
	delRep();
	ofstream fileout;
	fileout.open("PNGFile/savescore.txt", ios::trunc);
	int temp = score.size();
	if (score.size() > 5)
		temp = 5;
	for (int i = 0; i < temp; i++)
	{
		fileout << score[i] <<endl;
	}
	fileout.close();
}
bool AchievementBoard::CheckEmpty()
{
	string s;
	ifstream filein;
	filein.open("PNGFile/savescore.txt");
	getline(filein, s);
	filein.close();
	if (s == "")
		return true;
	return false;
}
void AchievementBoard::render()
{
	SDL_RenderClear(rendered);
	SDL_RenderCopy(AchievementBoard::rendered,background_board, NULL, NULL);
	int x = 80, y = 380;
	message* title = new message();
	title->setText("Achievement: ");
	title->render(80, 200, 80, 250);
	message* rank = new message();
	rank->setText("Rank ");
	rank->render(80, 300, 60, 100);
	message* score = new message();
    score->setText("Score ");
	score->render(x+200, 300, 60, 100);
	for (int i = 0; i < mess.size(); i++)
	{  
		message* temp1 = new message();
		temp1->setText(i+1);
		temp1->render(x+20, y,30,20);
		mess[i]->render(x + 220, y-5, 40, 50);
		y = y + 50;
	}
	SDL_RenderPresent(AchievementBoard::rendered);
}
void AchievementBoard::clean()
{
	SDL_DestroyWindow(window);	//Xóa cửa sổ
	SDL_DestroyRenderer(rendered);	//Cửa sổ khồng còn thì render cũng chỉ để trưng
	SDL_Quit();	//Thoát khỏi hoàn toàn việc sử dụng SDL
	std::cout << "Game Cleansed!" << std::endl;
}
void AchievementBoard::handleEvents()
{
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
void AchievementBoard::update()
{
	
}

