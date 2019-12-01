#include "GameBOT.h"
#include "textureManager.h"
#include "PaddleObject.h"
#include "BotPaddle.h"
#include "BallObject.h"
#include "message.h"
//Mọi thứ đều y chang Game.cpp
//Ngoài trừ tên các biến phải thay đổi để không bị lỗi (do là global variable)
//Và hàm update của thanh BOT
PaddleObject* paddlePlayer = NULL;
BotPaddle* paddleBOT = NULL;
BallObject* ball_BOT = NULL;
SDL_Texture* background_BOT = NULL;
//SDL_Renderer* GameBOT::rendered = NULL;
message* scoreShow_Player = NULL;
message* scoreShow_BOT = NULL;
message* resultGame_BOT = NULL;
GameBOT::GameBOT() {

}
GameBOT::~GameBOT() {

}
void GameBOT::init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flag = 0;
	if (fullscreen) {
		flag = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystem Initialised! ..." << std::endl;
		window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flag);

		if (window) {
			std::cout << "Window created!" << std::endl;
		}
		rendered = SDL_CreateRenderer(window, -1, 0);
		if (rendered) {
			SDL_SetRenderDrawColor(rendered, 255, 255, 255, 255);
			std::cout << "Rendered created!" << std::endl;
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}

	paddlePlayer = new PaddleObject("PNGFile/paddle.png", 15, 10);
	paddleBOT = new BotPaddle("PNGFile/paddle.png", WINDOW_WIDTH - 25, 10);
	ball_BOT = new BallObject("PNGFile/Ball.png", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	background_BOT = textureManager::loadTexture("PNGFile/court.png");

	scoreShow_Player = new message();
	scoreShow_BOT = new message();
	resultGame_BOT = NULL;
}
void GameBOT::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_KEYDOWN:
	{
		switch (event.key.keysym.sym)	//Không cần W S cho thanh thứ 2 nữa, do đã được tự động hóa
		{
		case SDLK_UP:
			paddlePlayer->moveUp();
			paddlePlayer->moveUp();
			break;
		case SDLK_DOWN:
			paddlePlayer->moveDown();
			paddlePlayer->moveDown();
			break;
		case SDLK_ESCAPE:
			isRunning = false;
			break;
		default:
			break;
		}
	}
	}
}
void GameBOT::render() {
	SDL_RenderClear(rendered);
	SDL_RenderCopy(GameBOT::rendered, background_BOT, NULL, NULL);
	paddlePlayer->render();
	paddleBOT->render();
	scoreShow_Player->render(300, 50, 50, 25);
	scoreShow_BOT->render(500 - 25, 50, 50, 25);
	ball_BOT->render();
	if (resultGame_BOT != NULL)
	{
		resultGame_BOT->render(300, 300, 50, 200);
	}
	SDL_RenderPresent(GameBOT::rendered);
	if (!isRunning)
	{
		SDL_Delay(2000);
	}
}
void GameBOT::update() {

	paddlePlayer->update();
	paddleBOT->updateBOT(ball_BOT);	//Khác biệt duy nhất với Game.cpp :)))
	ball_BOT->move(paddlePlayer, paddleBOT);
	ball_BOT->update();
	int score_1 = ball_BOT->getScore_1();
	int score_2 = ball_BOT->getScore_2();
	if (score_1 < MAX_SCORE && score_2 < MAX_SCORE)
	{
		scoreShow_Player->setText(score_1);
		scoreShow_BOT->setText(score_2);
	}
	else
	{
		resultGame_BOT = new message();
		if (score_1 == MAX_SCORE)
		{
			resultGame_BOT->setText("P1 WIN");
		}
		else if (score_2 == MAX_SCORE)
		{
			resultGame_BOT->setText("P2 WIN");
		}
		isRunning = false;
	}
}
void GameBOT::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(rendered);
	SDL_Quit();
	std::cout << "Game Cleansed!" << std::endl;
}