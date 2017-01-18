#pragma once
#include "MenuScene.h"
#include "TestScene.h"
#include "GameLib.h"
#include "Game.h"

struct MenuScene::Impl {
	Image* test;
};

MenuScene::MenuScene() :pimpl(new Impl) {}

void MenuScene::OnInitialize()
{
	pimpl->test = new Bitmap(132);
	pimpl->test->Scale(5, 5);
	pimpl->test->SetTopLeftPosition(400, 150);
	pimpl->test->SetOpacity(0.5);
}

void MenuScene::OnUpdate()
{
	/*static float c = 0;
	pimpl->test->Rotate(c++);
	if (c >= 180) {
		GoToScene(new TestScene());
		return;
	}*/
	if (Game::Instance()->GetLeftMouseDown()) pimpl->test->Transfer(-5, 0);
	if (Game::Instance()->GetRightMouseDown()) pimpl->test->Transfer(5, 0);
}

void MenuScene::OnDraw()
{
	pimpl->test->Draw();
}

void MenuScene::OnClose()
{
	delete pimpl->test;
}
