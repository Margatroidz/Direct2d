#pragma once
#include <memory>

class Scene;
class Game 
{
public:
	static Game* Instance();
	void Initial();
	void FixedUpdate();
	void Release();
	void ChangeScene(Scene* nextScene);

#pragma region InputMethod
	void KeyDown(unsigned int key);
	void KeyUp(unsigned int key);
	void SetMousePosition(int x, int y);
	void LeftMouseDown();
	void MiddleMouseDown();
	void RightMouseDown();
	void LeftMouseUp();
	void MiddleMouseUp();
	void RightMouseUp();

	unsigned int GetKeyDown(unsigned int key);
	unsigned int GetKeyUp(unsigned int key);
	int GetMousePositionX();
	int GetMousePositionY();
	unsigned int GetLeftMouseDown();
	unsigned int GetMiddleMouseDown();
	unsigned int GetRightMouseDown();
	unsigned int GetLeftMouseUp();
	unsigned int GetMiddleMouseUp();
	unsigned int GetRightMouseUp();
#pragma endregion

private:
	Game();
	~Game();
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};