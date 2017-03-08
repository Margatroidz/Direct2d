#pragma once
#include "Scene.h"
#include <memory>

class FirstStage : public Scene {
public:
	FirstStage();
	void OnInitialize();
	void OnUpdate();
	void OnDraw();
	void OnClose();
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};