#pragma once

class Scene
{
public:
	Scene();
	~Scene();
	virtual void OnInitialize() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnDraw() = 0;
	virtual void OnInput() = 0;
	virtual void OnClose() = 0;
protected:
	void GoToScene(Scene* nextScene);
};