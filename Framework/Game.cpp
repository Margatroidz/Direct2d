#include "Game.h"
#include "Direct2D.h"
#include "Scene.h"
#include "Config.h"
#include INIT_SCENE_HEADER

struct Input {
	unsigned int _isKeyDown[256];
	unsigned int _isKeyUp[256];
	unsigned int _isRightButtonDown;
	unsigned int _isLeftButtonDown;
	unsigned int _isMiddleButtonDown;
	unsigned int _isRightButtonUp;
	unsigned int _isLeftButtonUp;
	unsigned int _isMiddleButtonUp;
	unsigned int _scroll;
	int _mousePositionX;
	int _mousePositionY;
};

struct Game::Impl {
	Impl();
	~Impl();
	Scene* _scene;
	Input _inputBuffer;
};



Game::Impl::Impl() :_scene(nullptr) {}

Game::Impl::~Impl() {}

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
	memset(&pimpl->_inputBuffer, 0, sizeof(Input));
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

#pragma region InputMethod
void Game::KeyDown(unsigned int key)
{
	pimpl->_inputBuffer._isKeyDown[key]++;
}
void Game::KeyUp(unsigned int key)
{
	pimpl->_inputBuffer._isKeyUp[key]++;
}
void Game::SetMousePosition(int x, int y)
{
	pimpl->_inputBuffer._mousePositionX = x;
	pimpl->_inputBuffer._mousePositionY = y;
}
void Game::LeftMouseDown()
{
	pimpl->_inputBuffer._isLeftButtonDown++;
}
void Game::MiddleMouseDown()
{
	pimpl->_inputBuffer._isMiddleButtonDown++;
}
void Game::RightMouseDown()
{
	pimpl->_inputBuffer._isRightButtonDown++;
}
void Game::LeftMouseUp()
{
	pimpl->_inputBuffer._isLeftButtonUp++;
}
void Game::MiddleMouseUp()
{
	pimpl->_inputBuffer._isMiddleButtonUp++;
}
void Game::RightMouseUp()
{
	pimpl->_inputBuffer._isRightButtonUp++;
}


unsigned int Game::GetKeyDown(unsigned int key)
{
	return pimpl->_inputBuffer._isKeyDown[key];
}

unsigned int Game::GetKeyUp(unsigned int key)
{
	return pimpl->_inputBuffer._isKeyUp[key];
}

int Game::GetMousePositionX()
{
	return pimpl->_inputBuffer._mousePositionX;
}

int Game::GetMousePositionY()
{
	return pimpl->_inputBuffer._mousePositionY;
}
unsigned int Game::GetLeftMouseDown()
{
	return pimpl->_inputBuffer._isLeftButtonDown;
}
unsigned int Game::GetMiddleMouseDown()
{
	return pimpl->_inputBuffer._isMiddleButtonDown;
}
unsigned int Game::GetRightMouseDown()
{
	return pimpl->_inputBuffer._isRightButtonDown;
}
unsigned int Game::GetLeftMouseUp()
{
	return pimpl->_inputBuffer._isLeftButtonUp;
}
unsigned int Game::GetMiddleMouseUp()
{
	return pimpl->_inputBuffer._isMiddleButtonUp;
}
unsigned int Game::GetRightMouseUp()
{
	return pimpl->_inputBuffer._isRightButtonUp;
}
#pragma endregion

Game::Game() :pimpl(new Impl)
{
	memset(&pimpl->_inputBuffer, 0, sizeof(Input));
	//int i = sizeof(Input);
	//wchar_t buffer[256];
	//wsprintf(buffer, L"%d", i);
	//MessageBox(nullptr, L"constructer", L"constructer", MB_OK);
}

Game::~Game()
{
}
