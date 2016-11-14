#pragma once
#pragma comment(lib, "d2d1")
#include <d2d1_2.h>
#include "Image.h"
#include "Direct2D.h"

void Image::SetPosition(float x, float y)
{
	_topLeft.x = x;
	_topLeft.y = y;
}

void Image::Transfer(float x, float y)
{
	_topLeft.x += x;
	_topLeft.y += y;
}

Bitmap::Bitmap(char* resourceName)
{
	_bitmap = Direct2D::Instance()->LoadBitmap(resourceName);
}

Bitmap::Bitmap(int resourceNumber)
{
	_bitmap = Direct2D::Instance()->LoadBitmap(resourceNumber);
}

Bitmap::~Bitmap()
{
	Direct2D::Instance()->DestroyBitmap(_bitmap);
}

void Bitmap::Draw()
{
	Direct2D::Instance()->Draw(this);
}

Animation::Animation(char** resourceName, int number, float interval)
{
}

Animation::Animation(int * resourceNumber, int number, float interval)
{
}

Animation::~Animation()
{
}

void Animation::Draw()
{
}
