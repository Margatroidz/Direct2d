#include "MenuScene.h"
#include "TestScene.h"
#include "Game.h"

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::OnInitialize()
{
	test = new Bitmap(132);
	test->Scale(5, 5);
	test->SetTopLeftPosition(400, 150);
	test->SetOpacity(0.5);
}

void MenuScene::OnUpdate()
{
	static float c = 0;
	test->Rotate(c++);
	if (c >= 180) {
		GoToScene(new TestScene());
	}
}

void MenuScene::OnDraw()
{
	test->Draw();
}

void MenuScene::OnInput()
{
}

void MenuScene::OnClose()
{
	delete test;
}
