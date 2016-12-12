#include "Scene.h"
#include "Game.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::GoToScene(Scene* nextScene)
{
	Game::Instance()->ChangeScene(nextScene);
}
