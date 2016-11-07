#pragma once
#include "GameBitmap.h"

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
	GameBitmap* test;
};