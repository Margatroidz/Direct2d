#include "Game.h"
#include "Direct2D.h"
#include <Windows.h>

Game * Game::Instance()
{
	static Game instance;
	return &instance;
}

void Game::FixedUpdate()
{
	if (_scene == NULL) {
		Direct2D::Instance()->BeginLoad();
		_scene = new Scene();
		_scene->OnInitialize();
		Direct2D::Instance()->EndLoad();
	}
	_scene->OnUpdate();
	Direct2D::Instance()->BeginDraw();
	_scene->OnDraw();
	Direct2D::Instance()->EndDraw();
}

void Game::Test()
{
	//MessageBox(NULL, L"test", L"test", MB_OK);
}

void Game::Release()
{
	_scene->OnClose();
	delete _scene;
}

Game::Game()
{
	//MessageBox(NULL, L"constructer", L"constructer", MB_OK);
}


Game::~Game()
{
}
