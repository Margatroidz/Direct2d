#pragma once
#include "Scene.h"

class Game 
{
public:
	static Game* Instance();
	void FixedUpdate();
	void Test();
	void Release();
private:
	Game();
	~Game();
	Scene* _scene;
};