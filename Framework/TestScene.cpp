#pragma once
#include "TestScene.h"
#include "GameLib.h"

struct TestScene::impl {
	Image* test;
	int counter;
	float step;
};

TestScene::TestScene() :pimpl(new impl) {}

void TestScene::OnInitialize()
{
	Audio a;
	int ttt[6] = { 132, 133, 134, 135, 136, 137 };
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

void TestScene::OnInput()
{
}

void TestScene::OnClose()
{
	delete pimpl->test;
}