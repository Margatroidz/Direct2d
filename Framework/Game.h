#pragma once
#include "Scene.h"

class Game 
{
public:
	static Game* Instance();
	void UpdatePeriodicity();
	void Test();
private:
	Game();
	~Game();
	Scene* scene;
};