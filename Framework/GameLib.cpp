#include "GameLib.h"
#include "Game.h"

void GoToScene(Scene * nextScene)
{
	Game::Instance()->GoToScene(nextScene);
	Sleep(5000);
	throw "GoToScene ¶W®É !";
}