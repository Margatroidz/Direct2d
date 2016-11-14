#pragma once
#include "Image.h"

class Scene
{
public:
	Scene();
	~Scene();
	virtual void OnInitialize();
	virtual void OnUpdate();
	virtual void OnDraw();
	virtual void OnInput();
	virtual void OnClose();
private:
	Image* test;
	float counter;
	float step;
};