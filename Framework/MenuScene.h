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
	void OnClose();
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};
