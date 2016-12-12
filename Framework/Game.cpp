#include "Game.h"
#include "Direct2D.h"
#include "Scene.h"
#include <Windows.h>
#include "Config.h"
#include INIT_SCENE_HEADER

struct Input {
	bool _isRightButtonDown;
	bool _isLeftButtonDown;
	bool _isMiddleButtonDown;
	bool _isRightButtonUp;
	bool _isLeftButtonUp;
	bool _isMiddleButtonUp;
	unsigned int _scroll;
};

struct Game::Impl {
	Impl();
	~Impl();
	Scene* _scene;
	Input InputBuffer;
};

Game::Impl::Impl() :_scene(NULL){}

Game::Impl::~Impl(){}

Game * Game::Instance()
{
	static Game instance;
	return &instance;
}

void Game::Initial()
{
	ChangeScene(new INIT_SCENE());
}

void Game::FixedUpdate()
{
	pimpl->_scene->OnUpdate();
	Direct2D::Instance()->BeginDraw();
	pimpl->_scene->OnDraw();
	Direct2D::Instance()->EndDraw();
}

void Game::Release()
{
	if (pimpl->_scene) {
		pimpl->_scene->OnClose();
		delete pimpl->_scene;
	}
}

void Game::ChangeScene(Scene * nextScene)
{
	if (pimpl->_scene) {
		pimpl->_scene->OnClose();
		delete pimpl->_scene;
	}
	pimpl->_scene = nextScene;
	Direct2D::Instance()->BeginLoad();
	pimpl->_scene->OnInitialize();
	Direct2D::Instance()->EndLoad();
}

Game::Game():pimpl(new Impl)
{
	//MessageBox(nullptr, L"constructer", L"constructer", MB_OK);
}


Game::~Game()
{
}
