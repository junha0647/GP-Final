#define WIDTH (600)
#define HEIGHT (400)

#include "Game.h"
#include "InputHandler.h"

#include "Walker.h"

Game* Game::s_pInstance = 0;

bool Game::setup()
{
	bool result;

	result = init("Nature of Code", 660, 340, WIDTH, HEIGHT, false);

	//_walker = new Walker(WIDTH/2,HEIGHT/2);
	_walker = new Walker();


	return result;
}

void Game::update()
{
	_walker->update();

	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	_walker->draw(m_pRenderer);


	SDL_RenderPresent(m_pRenderer);


	// ?¬ê°??ê·¸ë¦¬ê¸?
	/*

	SDL_Rect rect[2];
	rect[0].x = 250;
	rect[0].y = 150;
	rect[0].w = 200;
	rect[0].h = 200;

	rect[1].x = 50;
	rect[1].y = 150;
	rect[1].w = 200;
	rect[1].h = 200;


	SDL_RenderDrawRects(renderer, rect,2);
	*/
}

void Game::clean()
{
	delete _walker;

	TheInputHandler::Instance()->clean();

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);

	m_pWindow = NULL;
	m_pRenderer = NULL;

	SDL_Quit();
}

//==================================================

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_OPENGL);

	if (m_pWindow != NULL)
	{
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
		SDL_RenderClear(m_pRenderer);
	}
	else
	{
		return false; // ?ˆë„???ì„¤ ?¤íŒ¨ l
	}

	m_bRunning = true;

	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

	return true;
}

bool Game::running()
{
	return m_bRunning;
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
}