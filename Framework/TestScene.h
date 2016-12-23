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
	void OnClose();
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};