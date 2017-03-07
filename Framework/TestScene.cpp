#pragma once
#include "TestScene.h"
#include "GameLib.h"

struct TestScene::Impl {
	Image* test;
	int counter;
	float step;
};

TestScene::TestScene() :pimpl(new Impl) {}

void TestScene::OnInitialize()
{
	Audio a;
	char* ttt[6] = { "C:\\Users\\Mystia\\Downloads\\Framework\\Framework\\image\\E_bullet_00.png",
		"C:\\Users\\Mystia\\Downloads\\Framework\\Framework\\image\\E_bullet_01.png",
		"C:\\Users\\Mystia\\Downloads\\Framework\\Framework\\image\\E_bullet_02.png",
		"C:\\Users\\Mystia\\Downloads\\Framework\\Framework\\image\\E_bullet_03.png",
		"C:\\Users\\Mystia\\Downloads\\Framework\\Framework\\image\\E_bullet_04.png",
		"C:\\Users\\Mystia\\Downloads\\Framework\\Framework\\image\\E_bullet_05.png" };
	pimpl->test = new Animation(ttt, 6, (float)0.1);
	pimpl->test->SetTopLeftPosition(150, 150);
	pimpl->test->Scale(3, 3);
	pimpl->test->SetOpacity(0.5);
	pimpl->counter = 0;
	pimpl->step = -2;
}

void TestScene::OnUpdate()
{
	if (pimpl->counter % 360 == 0) pimpl->step = -pimpl->step;

	pimpl->counter += 2;
	pimpl->test->Rotate((float)pimpl->counter);
	pimpl->test->Transfer((float)pimpl->step, (float)pimpl->step);
}

void TestScene::OnDraw()
{
	pimpl->test->Draw();
}

void TestScene::OnClose()
{
	delete pimpl->test;
}