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

	void KeyDown(unsigned int key);
	void KeyUp(unsigned int key);
	void SetMousePosition(int x, int y);
	void LButtonDown();
	void MButtonDown();
	void RButtonDown();
	void LButtonUp();
	void MButtonUp();
	void RButtonUp();

	unsigned int GetKeyDown(unsigned int key);
	unsigned int GetKeyUp(unsigned int key);
	int GetMousePositionX();
	int GetMousePositionY();
	unsigned int IsLButtonDown();
	unsigned int IsMButtonDown();
	unsigned int IsRButtonDown();
	unsigned int IsLButtonUp();
	unsigned int IsMButtonUp();
	unsigned int IsRButtonUp();

private:
	Game();
	~Game();
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};