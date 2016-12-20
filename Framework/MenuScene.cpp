#pragma once
#include "MenuScene.h"
#include "TestScene.h"
#include "GameLib.h"
#include "Direct2D.h"

struct MenuScene::impl {
	Image* test;
};

MenuScene::MenuScene() :pimpl(new impl) {}

void MenuScene::OnInitialize()
{
	//pimpl->test = new Bitmap(132);
	//pimpl->test->Scale(5, 5);
	//pimpl->test->SetTopLeftPosition(400, 150);
	//pimpl->test->SetOpacity(0.5);
}

void MenuScene::OnUpdate()
{
	//static float c = 0;
	//pimpl->test->Rotate(c++);
	//if (c >= 180) {
	//	GoToScene(new TestScene());
	//	return;
	//}
}

void MenuScene::OnDraw()
{
	//pimpl->test->Draw();
	Direct2D::Instance()->Test();
}

void MenuScene::OnClose()
{
	//delete pimpl->test;
}
