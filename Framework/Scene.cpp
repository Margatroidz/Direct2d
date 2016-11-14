#include "Scene.h"

Scene::Scene()
{
	
}

Scene::~Scene()
{
}

void Scene::OnInitialize()
{
	test = new Bitmap(130);
	test->SetPosition(0, 150);
	counter = 0;
	step = 2;
}

void Scene::OnUpdate()
{
	if (counter > 600 || counter < 0) step = -step;
	counter += step;
	test->Transfer(step, 0);
}

void Scene::OnDraw()
{
	test->Draw();
}

void Scene::OnInput()
{
}

void Scene::OnClose()
{
	delete test;
}
