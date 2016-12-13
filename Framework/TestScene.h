#pragma once
#include "Scene.h"
#include <memory>

class TestScene : public Scene
{
public:
	TestScene();
	void OnInitialize();
	void OnUpdate();
	void OnDraw();
	void OnInput();
	void OnClose();
private:
	struct impl;
	std::unique_ptr<impl> pimpl;
};