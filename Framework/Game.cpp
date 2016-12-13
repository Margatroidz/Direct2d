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

enum SceneState{
	uninitialized,
	run
};

struct Game::Impl {
	Impl();
	~Impl();
	Scene* _scene;
	SceneState _sceneState;
	Input _inputBuffer;
};

Game::Impl::Impl() :_scene(nullptr){}

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
	if (pimpl->_sceneState) {
		pimpl->_scene->OnUpdate();
		Direct2D::Instance()->BeginDraw();
		pimpl->_scene->OnDraw();
		Direct2D::Instance()->EndDraw();
	}
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
	pimpl->_sceneState = uninitialized;
	Direct2D::Instance()->BeginLoad();
	pimpl->_scene->OnInitialize();
	Direct2D::Instance()->EndLoad();
	pimpl->_sceneState = run;
}

Game::Game():pimpl(new Impl)
{
	pimpl->_sceneState = uninitialized;
	//MessageBox(nullptr, L"constructer", L"constructer", MB_OK);
}


Game::~Game()
{
}
