#pragma once
#pragma comment(lib, "d2d1")
#include <d2d1_2.h>
#include "Image.h"
#include "Direct2D.h"

void Image::SetPosition(float x, float y)
{
	_topLeftX = x;
	_topLeftY = y;
}

void Image::Transfer(float x, float y)
{
	_topLeftX += x;
	_topLeftY += y;
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
	Direct2D::Instance()->Draw(_bitmap, _topLeftX, _topLeftY);
}

Animation::Animation(char** resourceName, int number, float interval) : _interval((int)(60.0 * interval)), _counter(0)
{
	//陣列預留一個位置放NULL，判斷animation的結尾
	_bitmaps = new ID2D1Bitmap*[number + 1];
	for (int i = 0; i < number; i++) {
		_bitmaps[i] = Direct2D::Instance()->LoadBitmap(resourceName[i]);
	}
	_bitmaps[number] = NULL;
	_bitmap = _bitmaps;
}

Animation::Animation(int * resourceNumber, int number, float interval) : _interval((int)(60.0 * interval)), _counter(0)
{
	_bitmaps = new ID2D1Bitmap*[number + 1];
	for (int i = 0; i < number; i++) {
		_bitmaps[i] = Direct2D::Instance()->LoadBitmap(resourceNumber[i]);
	}
	_bitmaps[number] = NULL;
	_bitmap = _bitmaps;
}

Animation::~Animation()
{
	ID2D1Bitmap** bitmapItr = _bitmaps;
	do {
		Direct2D::Instance()->DestroyBitmap(*bitmapItr);
	} while (!*(++bitmapItr));
}

void Animation::Draw()
{
	if (++_counter >= _interval) {
		//判斷下一個pointer是否為NULL，如果為NULL則將圖片切到第一張
		if (!*(++_bitmap)) _bitmap = _bitmaps;
		_counter = 0;
	}
	Direct2D::Instance()->Draw(*_bitmap, _topLeftX, _topLeftY);
}
