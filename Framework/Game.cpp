#include "Game.h"
#include <Windows.h>

Game * Game::Instance()
{
	static Game instance;
	return &instance;
}

void Game::Test()
{
	//MessageBox(NULL, L"test", L"test", MB_OK);
}

Game::Game()
{
	//MessageBox(NULL, L"constructer", L"constructer", MB_OK);
}


Game::~Game()
{
}
