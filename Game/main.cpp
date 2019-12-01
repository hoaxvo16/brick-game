#include "Game.h"
#include "GameBOT.h"
#include "AbstractGame.h"
#include "Menu.h"
#include"BrickGame.h"
using namespace std;
int main(int argc, char* argv[]) {	//Ham main can phai co tham so nay no moi chay nhen!!! Do thu vien SDL quy dinh
	const int FPS = 120;	//Ti so khung hinh moi giay
	const int frameDelay = 1000 / FPS;	//Tinh toan do delay sao cho trung voi ti so khung hinh
	int frameStart, frameTime;
	int decision = 0;
	while (decision != 3)
	{
		system("cls");
		AbstractGame* menu = new Game();
		menu->init("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);
		decision = drawMenu(menu, FPS);
		menu->clean();
		if (decision == 2)
		{
			AbstractGame* game = new Game();	//Khoi tao game de choi
		// Chi can thay GameBOT <-> Game de doi che do choi
			game->init("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);
			//Khoi tao cua so tro choi, cua so se nam giua man hinh
			//WINDOW_WIDTH la do rong cua cua so
			//WINDOW_HEIGHT la chieu cao cua cua so
			//Bien false cuoi cung de nhan biet choi o che do cua so hay fullscreen, thu thay doi thanh True di roi biet :v
			while (game->running()) {	//Vong lap cua tro choi
				frameStart = SDL_GetTicks();	//Lay thoi gian he thong luc bat dau vong lap
				game->handleEvents();	//Giai quyet nhung tac dong tu user den game
				game->update();	//Game se tiep tuc chay theo nhung bien doi tren cung nhu van se tiep tuc chay neu khong co gi
				game->render();	//Chay o tren chi la chay ve mat bien so, ham nay la ve cac object len cua so
				frameTime = SDL_GetTicks() - frameStart; //Lay thoi gian chay ke tu khi bat dau chu ki
				if (frameDelay > frameTime) {
					SDL_Delay(frameDelay - frameTime);
					//Neu thoi gian nay van con ngan hon thoi gian delay minh muon (de thoa FPS) thi delay them
				}
			}
			game->clean();	//Xoa sach, xoa het, xoa tat!!
		}
		else if (decision == 1)
		{
			AbstractGame* game = new GameBOT();//Khoi tao game de choi
	// Chi can thay GameBOT <-> Game de doi che do choi
			game->init("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);
			//Khoi tao cua so tro choi, cua so se nam giua man hinh
			//WINDOW_WIDTH la do rong cua cua so
			//WINDOW_HEIGHT la chieu cao cua cua so
			//Bien false cuoi cung de nhan biet choi o che do cua so hay fullscreen, thu thay doi thanh True di roi biet :v
			while (game->running()) {	//Vong lap cua tro choi
				frameStart = SDL_GetTicks();	//Lay thoi gian he thong luc bat dau vong lap
				game->handleEvents();	//Giai quyet nhung tac dong tu user den game
				game->update();	//Game se tiep tuc chay theo nhung bien doi tren cung nhu van se tiep tuc chay neu khong co gi
				game->render();	//Chay o tren chi la chay ve mat bien so, ham nay la ve cac object len cua so
				frameTime = SDL_GetTicks() - frameStart; //Lay thoi gian chay ke tu khi bat dau chu ki
				if (frameDelay > frameTime) {
					SDL_Delay(frameDelay - frameTime);
					//Neu thoi gian nay van con ngan hon thoi gian delay minh muon (de thoa FPS) thi delay them
				}
			}
			game->clean();	//Xoa sach, xoa het, xoa tat!!
		}
		else if(decision==0)
		{
			/*system("cls");
			AbstractGame* submenu = new Game();
			submenu->init("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);
			int savegame = drawSubMenu(submenu, FPS);
			submenu->clean();
			if (savegame == 2)
				break;*/
			AbstractGame* game = new BrickGame();//Khoi tao game de choi
	// Chi can thay GameBOT <-> Game de doi che do choi
			game->init("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);
			//Khoi tao cua so tro choi, cua so se nam giua man hinh
			//WINDOW_WIDTH la do rong cua cua so
			//WINDOW_HEIGHT la chieu cao cua cua so
			//Bien false cuoi cung de nhan biet choi o che do cua so hay fullscreen, thu thay doi thanh True di roi biet :v
			while (game->running()) {	//Vong lap cua tro choi
				frameStart = SDL_GetTicks();	//Lay thoi gian he thong luc bat dau vong lap
				game->handleEvents();	//Giai quyet nhung tac dong tu user den game
				game->update();	//Game se tiep tuc chay theo nhung bien doi tren cung nhu van se tiep tuc chay neu khong co gi
				game->render();	//Chay o tren chi la chay ve mat bien so, ham nay la ve cac object len cua so
				frameTime = SDL_GetTicks() - frameStart; //Lay thoi gian chay ke tu khi bat dau chu ki
				if (frameDelay > frameTime) {
					SDL_Delay(frameDelay - frameTime);
					//Neu thoi gian nay van con ngan hon thoi gian delay minh muon (de thoa FPS) thi delay them
				}
			}
			game->clean();	//Xoa sach, xoa het, xoa tat!!
		}
	}
	return 0;
}
