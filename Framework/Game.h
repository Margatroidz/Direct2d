#include <memory>
#define WM_SWITCH_SCENE (WM_USER + 0x0001)

class Scene;
class Game 
{
public:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	static Game* Instance();
	void Initial();
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
	struct Impl;
	std::unique_ptr<Impl> pimpl;
	Game();
	~Game();
};