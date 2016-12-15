#include "GameLib.h"
#include "Game.h"

void GoToScene(Scene * nextScene)
{
	Game::Instance()->ChangeScene(nextScene);
}