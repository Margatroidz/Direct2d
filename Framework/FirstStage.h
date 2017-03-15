#pragma once
#include "Scene.h"
#include <memory>

class FirstStage : public Scene {
public:
	FirstStage();
	void ShootByCharacter(int img, float posX, float posY, float angle, float speed, float radius);
	void OnInitialize();
	void OnUpdate();
	void OnDraw();
	void OnClose();
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};