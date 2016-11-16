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
	Direct2D::Instance()->Draw(this);
}

Animation::Animation(char** resourceName, int number, float interval) : _size(number), _interval((int)(60.0 * interval)), _counter(0), _position(0)
{
	_bitmaps = new ID2D1Bitmap*[_size];
	for (int i = 0; i < _size; i++) {
		_bitmaps[i] = Direct2D::Instance()->LoadBitmap(resourceName[i]);
	}
	_bitmap = _bitmaps[0];
}

Animation::Animation(int * resourceNumber, int number, float interval) : _size(number), _interval((int)(60.0 * interval)), _counter(0), _position(0)
{
	_bitmaps = new ID2D1Bitmap*[_size];
	for (int i = 0; i < _size; i++) {
		_bitmaps[i] = Direct2D::Instance()->LoadBitmap(resourceNumber[i]);
	}
	_bitmap = _bitmaps[0];
}

Animation::~Animation()
{
	for (int i = 0; i < _size; i++) Direct2D::Instance()->DestroyBitmap(_bitmaps[i]);
}

void Animation::Draw()
{
	if (++_counter >= _interval) {
		if (++_position >= _size) _bitmap = *_bitmaps;
		else {
			_position = (_position + 1) % _size;
			_bitmap = _bitmaps[_position];
		}
		_counter = 0;
	}
	Direct2D::Instance()->Draw(this);
}
