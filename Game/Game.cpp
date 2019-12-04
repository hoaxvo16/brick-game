#include "Game.h"
#include "textureManager.h"
#include "PaddleObject.h"
#include "BallObject.h"
#include "message.h"
/*Đây là những biến global đại diện cho các object của trò chơi
paddle1 là cái thanh bên trái
paddle2 là cái thanh bên phải
ball là trái banh, of course
background chính là cái nền đằng sau mà nhìn thấy có hơi bê đê ẻo lả đó!*/
PaddleObject* paddle1 = NULL;
PaddleObject* paddle2 = NULL;
BallObject* ball = NULL;
SDL_Texture* background = NULL;
SDL_Renderer* Game::rendered = NULL;
//Biến rendered được dùng để render(lưu lại những hình vẽ và vị trí của mỗi object, chờ cơ hội để bộc phát)
message* scoreShow_1 = NULL;	//Cái tỉ số bên tay trái á
message* scoreShow_2 = NULL;	//Này bên tay phải
message* resultGame = NULL;		//Cái này nếu thua hay thắng thì nó sẽ hiện lên
Game::Game() {
	//Hông biết ghi gì hết nên để đó chơi
}
Game::~Game() {
	//Này cũng vậy
}
void Game::init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen,int savegame) {
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
	paddle1 = new PaddleObject("PNGFile/paddle.png", 15, 10);
	paddle2 = new PaddleObject("PNGFile/paddle.png", WINDOW_WIDTH - 25, 10);
	ball = new BallObject("PNGFile/Ball.png", WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	/*Truy cập file hình ở bên ngoài thư mục chứa project
	2 tham số sau chỉ vị trí sẽ xuất hình trên cửa sổ*/
	background = textureManager::loadTexture("PNGFile/court.png");	//Truy cập vào file hình chứa background
	scoreShow_1 = new message();
	scoreShow_2 = new message();
	resultGame = NULL;
	/*Khởi tạo các biến để ghi dạng text lên cửa sổ*/
}
void Game::handleEvents() {
	SDL_Event event;	//Tạo biến sử lý các biến cố
	while(SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_KEYDOWN:	//Đây là biến cố cho việc có người bấm vào keyboard
		{
			switch (event.key.keysym.sym)	//Đọc kí tự bấm vào
			{
			case SDLK_UP:	//Mũi tên đi lên
				paddle1->moveUp();
				paddle1->moveUp();
				break;
			case SDLK_DOWN:	//Mũi tên đi xuống
				paddle1->moveDown();
				paddle1->moveDown();
				break;
			case SDLK_w:	//Chữ W trên keyboard
				paddle2->moveUp();
				paddle2->moveUp();
				break;
			case SDLK_s:	//Chữ S trên keyboard
				paddle2->moveDown();
				paddle2->moveDown();
				break;
			case SDLK_ESCAPE:	//Bấm ESCAPE để thoát khỏi trò chơi
				isRunning = false;
				break;
			default:
				break;
			}
		}
		}
	}
}
void Game::render() {
	SDL_RenderClear(rendered);
	//Bên trong render đang lưu các object và vị trí các object cũ nên cần phải clear
	SDL_RenderCopy(Game::rendered, background, NULL, NULL);
	/*Rendered lưu lại hình ảnh của background
	NULL đầu tiên để biết rằng sẽ đọc hết file hình, không chưa pixel nào
	NULL sau cho biết rằng rendered sẽ scale cái hình sao cho lắp đầy cửa sổ*/
	paddle1->render();
	paddle2->render();
	//Tương tự trên
	scoreShow_1->render(300, 50, 50, 25);
	scoreShow_2->render(500 - 25, 50, 50, 25);
	//Tương tự nhưng có thêm tham số để lưu ví trí x,y cũng như kích thước để ren
	ball->render();
	if (resultGame != NULL)
	{
		//Nếu Game đã xong thì in lên cửa sổ xem ai thắng
		resultGame->render(300, 300, 50, 200);
	}
	SDL_RenderPresent(rendered);	//Tất cả những thứ trong render sẽ được vẽ lên cửa sổ thông qua hàm này
	if (!isRunning)
	{
		//Nếu game đã kết thúc thì cho 2s để nhìn nhận người thắng cuộc
		SDL_Delay(2000);
	}
}
void Game::update() {
	paddle1->update();
	paddle2->update();
	ball->move(paddle1,paddle2);
	ball->update();
	//Xử lí các diễn biến trong game
	int score_1 = ball->getScore_1();
	int score_2 = ball->getScore_2();
	//Lấy điểm của 2 người chơi
	if (score_1 < MAX_SCORE && score_2 < MAX_SCORE)
	{
		//Điều chỉnh nội dụng của tỉ số
		scoreShow_1->setText(score_1);
		scoreShow_2->setText(score_2);
	}
	else 
	{
		//Nếu có người đạt được MAX_SCORE thì trò chơi end
		resultGame = new message();
		if (score_1 == MAX_SCORE)
		{
			//In ra người 1 thắng
			resultGame->setText("P1 WIN");
		}
		else if (score_2 == MAX_SCORE)
		{
			//In ra người 2 thắng
			resultGame->setText("P2 WIN");
		}
		isRunning = false;	//Ngưng trò chơi lại
	}
}
void Game::clean() {
	SDL_DestroyWindow(window);	//Xóa cửa sổ
	SDL_DestroyRenderer(rendered);	//Cửa sổ khồng còn thì render cũng chỉ để trưng
	SDL_Quit();	//Thoát khỏi hoàn toàn việc sử dụng SDL
	std::cout << "Game Cleansed!" << std::endl;
}
