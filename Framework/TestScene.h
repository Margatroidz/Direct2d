#pragma once
#include "Scene.h"
#include "Image.h"

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();
	void OnInitialize();
	void OnUpdate();
	void OnDraw();
	void OnInput();
	void OnClose();
private:
	Image* test;
	int counter;
	int step;
};