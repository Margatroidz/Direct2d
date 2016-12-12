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
private:
	Game();
	~Game();
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};