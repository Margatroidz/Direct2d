#include "GameLib.h"
#include "Game.h"

void GoToScene(Scene * nextScene) {
	return Game::Instance()->ChangeScene(nextScene);
}

unsigned int GetKeyDown(unsigned int key) {
	return Game::Instance()->GetKeyDown(key);
}

unsigned int GetKeyUp(unsigned int key) {
	return Game::Instance()->GetKeyUp(key);
}

int GetMousePositionX() {
	return Game::Instance()->GetMousePositionX();
}

int GetMousePositionY() {
	return Game::Instance()->GetMousePositionY();
}

unsigned int GetLeftMouseDown() {
	return Game::Instance()->GetLeftMouseDown();
}

unsigned int GetMiddleMouseDown() {
	return Game::Instance()->GetMiddleMouseDown();
}

unsigned int GetRightMouseDown() {
	return Game::Instance()->GetRightMouseDown();
}

unsigned int GetLeftMouseUp() {
	return Game::Instance()->GetLeftMouseUp();
}

unsigned int GetMiddleMouseUp() {
	return Game::Instance()->GetMiddleMouseUp();
}

unsigned int GetRightMouseUp() {
	return Game::Instance()->GetRightMouseUp();
}
