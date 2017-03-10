#pragma once
#include "Audio.h"
#include "Image.h"
#include "Text.h"
#include "Scene.h"
#include "KeyCode.h"

void GoToScene(Scene* nextScene);

unsigned int GetKeyDown(unsigned int key);
unsigned int GetKeyUp(unsigned int key);
int GetMousePositionX();
int GetMousePositionY();
unsigned int GetLeftMouseDown();
unsigned int GetMiddleMouseDown();
unsigned int GetRightMouseDown();
unsigned int GetLeftMouseUp();
unsigned int GetMiddleMouseUp();
unsigned int GetRightMouseUp();