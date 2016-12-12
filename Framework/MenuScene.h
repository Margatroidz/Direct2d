#pragma once
#include "Scene.h"
#include "Image.h"

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();
	void OnInitialize();
	void OnUpdate();
	void OnDraw();
	void OnInput();
	void OnClose();
private:
	Image* test;
};
