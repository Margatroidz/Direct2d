#include "Game.h"
#include "Direct2D.h"
#include "Scene.h"
#include "Config.h"
#include INIT_SCENE_HEADER

struct Input {
	unsigned int _isKeyDown[256];
	unsigned int _isKeyUp[256];
	unsigned int _isRightMouseDown;
	unsigned int _isLeftMouseDown;
	unsigned int _isMiddleMouseDown;
	unsigned int _isRightMouseUp;
	unsigned int _isLeftMouseUp;
	unsigned int _isMiddleMouseUp;
	unsigned int _scroll;
	int _mousePositionX;
	int _mousePositionY;
};

struct Game::Impl {
	Impl();
	~Impl();
	HWND _hWnd;
	HANDLE _gameThread;
	Scene* _scene;
	Scene* _nextScene;
	Input _inputBuffer;
};
Game::Impl::Impl() :_scene(nullptr), _nextScene(nullptr), _gameThread(nullptr) {}
Game::Impl::~Impl() {}

Game * Game::Instance()
{
	static Game instance;
	return &instance;
}

void Game::Initial(unsigned int hWnd)
{
	pimpl->_hWnd = (HWND)hWnd;
	GoToScene(new INIT_SCENE());
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
	if (pimpl->_gameThread) ShutDownThread();
	if (pimpl->_scene) DestoryScene();
}

void Game::GoToScene(Scene * nextScene)
{
	pimpl->_nextScene = nextScene;
	PostMessage(pimpl->_hWnd, WM_SWITCH_SCENE, (WPARAM)0, (LPARAM)0);
}

void Game::SwitchScene()
{
	if (pimpl->_gameThread) ShutDownThread();
	if (pimpl->_scene) DestoryScene();
	if (pimpl->_nextScene) CreateScene();
}

void Game::CreateScene()
{
	pimpl->_scene = pimpl->_nextScene;

}

void Game::DestoryScene()
{
	pimpl->_scene->OnClose();
	delete pimpl->_scene;
}

void Game::ShutDownThread()
{
}

//遊戲主迴圈，會在CreateScene時建立新的thread執行該function
void Game::GameLoop()
{
	Direct2D::Instance()->BeginLoad();
	pimpl->_scene->OnInitialize();
	Direct2D::Instance()->EndLoad();
	while (true) {
		pimpl->_scene->OnUpdate();
		memset(&pimpl->_inputBuffer, 0, sizeof(Input));
		Direct2D::Instance()->BeginDraw();
		pimpl->_scene->OnDraw();
		Direct2D::Instance()->EndDraw();
	}
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
	pimpl->_inputBuffer._isLeftMouseDown++;
}
void Game::MiddleMouseDown()
{
	pimpl->_inputBuffer._isMiddleMouseDown++;
}
void Game::RightMouseDown()
{
	pimpl->_inputBuffer._isRightMouseDown++;
}
void Game::LeftMouseUp()
{
	pimpl->_inputBuffer._isLeftMouseUp++;
}
void Game::MiddleMouseUp()
{
	pimpl->_inputBuffer._isMiddleMouseUp++;
}
void Game::RightMouseUp()
{
	pimpl->_inputBuffer._isRightMouseUp++;
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
	return pimpl->_inputBuffer._isLeftMouseDown;
}
unsigned int Game::GetMiddleMouseDown()
{
	return pimpl->_inputBuffer._isMiddleMouseDown;
}
unsigned int Game::GetRightMouseDown()
{
	return pimpl->_inputBuffer._isRightMouseDown;
}
unsigned int Game::GetLeftMouseUp()
{
	return pimpl->_inputBuffer._isLeftMouseUp;
}
unsigned int Game::GetMiddleMouseUp()
{
	return pimpl->_inputBuffer._isMiddleMouseUp;
}
unsigned int Game::GetRightMouseUp()
{
	return pimpl->_inputBuffer._isRightMouseUp;
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
