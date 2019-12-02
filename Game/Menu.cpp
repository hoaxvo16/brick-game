#include "Menu.h"
int drawMenu(AbstractGame* gameWindow, const int FPS)
{
	SDL_Texture* title = textureManager::loadTexture("PNGFile/title.png");
	SDL_Texture* player_select_1 = textureManager::loadTexture("PNGFile/player1.png");
	SDL_Texture* player_select_2 = textureManager::loadTexture("PNGFile/player2.png");
	SDL_Texture* player_select_3 = textureManager::loadTexture("PNGFile/player1.png");
	SDL_Texture* quit_select = textureManager::loadTexture("PNGFile/quit.png");
	SDL_Texture* selection = textureManager::loadTexture("PNGFile/select.png");
	SDL_Rect select_1, select_2, select_3, select_4, select_0;
	select_1.w = select_2.w = select_3.w = select_4.w = 200;
	select_1.h = select_2.h = select_3.h = select_4.h = 50;
	select_1.x = select_2.x = select_3.x = select_4.x = 300;
	select_1.y = 300;
	select_2.y = select_1.y + 2 * select_1.h;
	select_3.y = select_2.y + 2 * select_1.h;
	select_4.y = 200;
	bool wasSelected = false;
	select_0 = select_4;
	int decision = 0;
	int frameStart, frameTime;
	const int frameDelay = 1000 / FPS;
	bool stop = false;
	SDL_RenderClear(gameWindow->rendered);
	SDL_RenderCopy(gameWindow->rendered, title, NULL, NULL);
	SDL_RenderCopy(gameWindow->rendered, player_select_1, NULL, &select_1);
	SDL_RenderCopy(gameWindow->rendered, player_select_2, NULL, &select_2);
	SDL_RenderCopy(gameWindow->rendered, player_select_3, NULL, &select_4);
	SDL_RenderCopy(gameWindow->rendered, quit_select, NULL, &select_3);
	SDL_RenderCopy(gameWindow->rendered, selection, NULL, &select_0);
	while (!wasSelected)
	{
		frameStart = SDL_GetTicks();
		stop = false;
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
			{
				stop = true;
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
				{
					if (decision > 0)
					{
						decision--;
					}
					if (decision == 0) select_0 = select_4;
					else if (decision == 1) select_0 = select_1;
					else if (decision == 2)select_0 = select_2;
					else select_0 = select_3;
					break;
				}
				break;
				case SDLK_DOWN:
				{
					if (decision < 3)
					{
						decision++;
					}
					if (decision == 0) select_0 = select_4;
					else if (decision == 1) select_0 = select_1;
					else if (decision == 2)select_0 = select_2;
					else select_0 = select_3;
					break;
				}
				break;
				case SDLK_RETURN:
				case SDLK_ESCAPE:
				{
					wasSelected = true;
					break;
				}
				break;
				default:
					break;
				}
			}
		}
		SDL_RenderClear(gameWindow->rendered);
		SDL_RenderCopy(gameWindow->rendered, title, NULL, NULL);
		SDL_RenderCopy(gameWindow->rendered, player_select_1, NULL, &select_1);
		SDL_RenderCopy(gameWindow->rendered, player_select_2, NULL, &select_2);
		SDL_RenderCopy(gameWindow->rendered, quit_select, NULL, &select_3);
		SDL_RenderCopy(gameWindow->rendered, selection, NULL, &select_0);
		SDL_RenderCopy(gameWindow->rendered, player_select_3, NULL, &select_4);
		SDL_RenderPresent(gameWindow->rendered);
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	return decision;
}
int drawSubMenu(AbstractGame* gameWindow, const int FPS)
{
	SDL_Texture* title = textureManager::loadTexture("PNGFile/title.png");
	SDL_Texture* player_select_1 = textureManager::loadTexture("PNGFile/player1.png");
	SDL_Texture* player_select_2 = textureManager::loadTexture("PNGFile/player2.png");
	SDL_Texture* quit_select = textureManager::loadTexture("PNGFile/quit.png");
	SDL_Texture* selection = textureManager::loadTexture("PNGFile/select.png");
	SDL_Rect select_1, select_2, select_3, select_0;
	select_1.w = select_2.w = select_3.w = 200;
	select_1.h = select_2.h = select_3.h = 50;
	select_1.x = select_2.x = select_3.x = 300;
	select_1.y = 300;
	select_2.y = select_1.y + 2 * select_1.h;
	select_3.y = select_2.y + 2 * select_1.h;
	bool wasSelected = false;
	select_0 = select_1;
	int decision = 0;
	int frameStart, frameTime;
	const int frameDelay = 1000 / FPS;
	bool stop = false;
	SDL_RenderClear(gameWindow->rendered);
	SDL_RenderCopy(gameWindow->rendered, title, NULL, NULL);
	SDL_RenderCopy(gameWindow->rendered, player_select_1, NULL, &select_1);
	SDL_RenderCopy(gameWindow->rendered, player_select_2, NULL, &select_2);
	SDL_RenderCopy(gameWindow->rendered, quit_select, NULL, &select_3);
	SDL_RenderCopy(gameWindow->rendered, selection, NULL, &select_0);
	while (!wasSelected)
	{
		frameStart = SDL_GetTicks();
		stop = false;
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
			{
				stop = true;
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
				{
					if (decision > 0)
					{
						decision--;
					}
					if (decision == 0) select_0 = select_1;
					else if (decision == 1) select_0 = select_2;
					else select_0 = select_3;
					break;
				}
				break;
				case SDLK_DOWN:
				{
					if (decision < 2)
					{
						decision++;
					}
					if (decision == 0) select_0 = select_1;
					else if (decision == 1)select_0 = select_2;
					else select_0 = select_3;
					break;
				}
				break;
				case SDLK_RETURN:
				case SDLK_ESCAPE:
				{
					wasSelected = true;
					break;
				}
				break;
				default:
					break;
				}
			}
		}
		SDL_RenderClear(gameWindow->rendered);
		SDL_RenderCopy(gameWindow->rendered, title, NULL, NULL);
		SDL_RenderCopy(gameWindow->rendered, player_select_1, NULL, &select_1);
		SDL_RenderCopy(gameWindow->rendered, player_select_2, NULL, &select_2);
		SDL_RenderCopy(gameWindow->rendered, quit_select, NULL, &select_3);
		SDL_RenderCopy(gameWindow->rendered, selection, NULL, &select_0);
		SDL_RenderPresent(gameWindow->rendered);
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	return decision;
}