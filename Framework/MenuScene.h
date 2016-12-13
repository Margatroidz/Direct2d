#pragma once
#include "Scene.h"
#include <memory>

class MenuScene : public Scene
{
public:
	MenuScene();
	void OnInitialize();
	void OnUpdate();
	void OnDraw();
	void OnInput();
	void OnClose();
private:
	struct impl;
	std::unique_ptr<impl> pimpl;
};
