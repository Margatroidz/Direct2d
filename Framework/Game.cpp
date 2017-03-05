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
	DWORD GameLoop(void);
	static DWORD WINAPI GameLoopWrapper(void* Param);

	HANDLE _gameLoopThreadID;
	Scene* _scene;
	Input _inputBuffer;
	bool _sceneChnageflag;
	bool _gameCloseflag;
};

Game::Impl::Impl() :_scene(nullptr), _sceneChnageflag(false), _gameCloseflag(false){}
Game::Impl::~Impl() {}

DWORD Game::Impl::GameLoop(void) {
	while (true) {
		if (_gameCloseflag) break;

		_sceneChnageflag = false;
		_scene->OnInitialize();
		while (true) {
			_scene->OnUpdate();
			memset(&_inputBuffer, 0, sizeof(Input));

			if (_sceneChnageflag) break;

			Direct2D::Instance()->BeginDraw();
			_scene->OnDraw();
			Direct2D::Instance()->EndDraw();

			Sleep(15);
		}
	}
	return S_OK;
}

DWORD WINAPI Game::Impl::GameLoopWrapper(void* Param) {
	return Game::Instance()->pimpl->GameLoop();
}

Game * Game::Instance() {
	static Game instance;
	return &instance;
}

void Game::Initial() {
	ChangeScene(new INIT_SCENE());
	//用windows API的thread才可以順利使用wicfactory，似乎跟COM元件有關係，COM元件似乎對C++內建的thread支援度很差
	pimpl->_gameLoopThreadID = CreateThread(nullptr, 0, pimpl->GameLoopWrapper, (void*) this, 0, nullptr);
}

void Game::Release() {
	pimpl->_sceneChnageflag = true;
	pimpl->_gameCloseflag = true;

	//最多等待5秒，用無限大太危險
	WaitForSingleObjectEx(pimpl->_gameLoopThreadID, 5000, true);

	if (pimpl->_scene) {
		pimpl->_scene->OnClose();
		delete pimpl->_scene;
	}
}

void Game::ChangeScene(Scene * nextScene) {
	if (pimpl->_scene) {
		pimpl->_scene->OnClose();
		delete pimpl->_scene;
	}
	pimpl->_scene = nextScene;
	pimpl->_sceneChnageflag = true;
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

Game::Game() :pimpl(new Impl) {
	memset(&pimpl->_inputBuffer, 0, sizeof(Input));
	//int i = sizeof(Input);
	//wchar_t buffer[256];
	//wsprintf(buffer, L"%d", i);
	//MessageBox(nullptr, L"constructer", L"constructer", MB_OK);
}

Game::~Game() {
}
