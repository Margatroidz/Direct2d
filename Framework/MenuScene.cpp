#pragma once
#include "MenuScene.h"
#include "TestScene.h"
#include "GameLib.h"
#include "Game.h"

struct MenuScene::Impl {
	Image* test;
	Text* text;

	Audio *a;
};

MenuScene::MenuScene() :pimpl(new Impl) {}

void MenuScene::OnInitialize()
{
	pimpl->text = new Text(L"¬O");
	pimpl->test = new Bitmap("../Framework/image/E_bullet_00.png");
	pimpl->test->Scale(5, 5);
	pimpl->test->SetTopLeftPosition(400, 150);
	pimpl->test->SetOpacity(0.5);

	pimpl->a = new Audio("../Framework/audio/bgm_stg01.wav");
	pimpl->a->SetVolume(0.05f);
	pimpl->a->Play();
}

void MenuScene::OnUpdate()
{
	static float c = 0;
	pimpl->test->Rotate(c++);
	//if (c >= 180) {
	//	GoToScene(new TestScene());
	//	return;
	//}
	//if (Game::Instance()->GetLeftMouseDown()) pimpl->test->Transfer(-5, 0);
	//if (Game::Instance()->GetRightMouseDown()) pimpl->test->Transfer(5, 0);
}

void MenuScene::OnDraw()
{
	pimpl->test->Draw();
	pimpl->text->Draw();
}

void MenuScene::OnClose()
{
	delete pimpl->a;
	delete pimpl->test;
}
