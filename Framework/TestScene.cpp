#pragma once
#include "TestScene.h"
#include "Audio.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::OnInitialize()
{
	Audio a;
	int ttt[6] = { 132, 133, 134, 135, 136, 137 };
	test = new Animation(ttt, 6, (float)0.1);
	test->SetTopLeftPosition(150, 150);
	test->Scale(3, 3);
	test->SetOpacity(0.5);
	counter = 0;
	step = -2;
}

void TestScene::OnUpdate()
{
	if (counter % 360 == 0) step = -step;

	counter += 2;
	test->Rotate((float)counter);
	test->Transfer((float)step, (float)step);
}

void TestScene::OnDraw()
{
	test->Draw();
}

void TestScene::OnInput()
{
}

void TestScene::OnClose()
{
	delete test;
}