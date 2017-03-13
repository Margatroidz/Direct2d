#pragma once
#pragma comment(lib, "d2d1")
#include <d2d1_2.h>
#include "Image.h"
#include "Direct2D.h"

Image::Image() {
	_opacity = 1.0;
	_rotateAngle = 0.0;
}

Image::~Image() {
}

void Image::ResetImage() {
	ResetSize();
	Rotate(0.0);
}

void Image::SetTopLeftPosition(float x, float y) {
	_topLeft.x = x;
	_topLeft.y = y;
}

void Image::Rotate(float angle) {
	_rotateAngle += angle;
}

void Image::SetAngle(float angle) {
	_rotateAngle = angle;
}

void Image::Transfer(float x, float y) {
	_topLeft.x += x;
	_topLeft.y += y;
}

void Image::ResetSize() {
	_size.width = _oriSize.width;
	_size.height = _oriSize.height;
}

void Image::Resize(float width, float high) {
	_size.width = width;
	_size.height = high;
}

void Image::Scale(float scaleX, float scaleY) {
	_size.width *= scaleX;
	_size.height *= scaleY;
}

void Image::SetOpacity(float opacity) {
	_opacity = opacity;
}

void Image::DrawBitmap(ID2D1Bitmap * bitmap) {
	if (_rotateAngle != 0) {
		D2D1_POINT_2F imageCenter = D2D1::Point2F(_topLeft.x + _size.width / 2, _topLeft.y + _size.height / 2);
		Direct2D::Instance()->Rotate(D2D1::Matrix3x2F::Rotation(_rotateAngle, imageCenter));
		Direct2D::Instance()->DrawBitmap(bitmap, D2D1::RectF(_topLeft.x, _topLeft.y, _topLeft.x + _size.width, _topLeft.y + _size.height), _opacity);
		Direct2D::Instance()->Rotate(D2D1::Matrix3x2F::Identity());
	}
	else Direct2D::Instance()->DrawBitmap(bitmap, D2D1::RectF(_topLeft.x, _topLeft.y, _topLeft.x + _size.width, _topLeft.y + _size.height), _opacity);
}

Bitmap::Bitmap(char* path) {
	_bitmap = Direct2D::Instance()->LoadBitmapD(path);
	_oriSize = _bitmap->GetSize();
	_size = _bitmap->GetSize();
}

Bitmap::Bitmap(const Bitmap& sourceBitmap) {
	_bitmap = sourceBitmap._bitmap;
	_oriSize = sourceBitmap._oriSize;
	_size = sourceBitmap._size;
}

Bitmap::~Bitmap() {
	Direct2D::Instance()->DestroyBitmap(_bitmap);
}

void Bitmap::Draw() {
	DrawBitmap(_bitmap);
}

Animation::Animation(char** resourcePath, int number, float interval) : _interval((int)(60.0 * interval)), _counter(0) {
	//陣列預留一個位置放null，判斷animation的結尾
	_bitmaps = new ID2D1Bitmap*[number + 1];
	for (int i = 0; i < number; i++) {
		_bitmaps[i] = Direct2D::Instance()->LoadBitmapD(resourcePath[i]);
	}
	_bitmaps[number] = nullptr;
	_bitmap = _bitmaps;
	_oriSize = (*_bitmap)->GetSize();
	_size = (*_bitmap)->GetSize();
}

Animation::Animation(const Animation& sourceAnimation) :_interval(sourceAnimation._interval), _counter(0) {
	_bitmaps = sourceAnimation._bitmaps;
	_bitmap = _bitmaps;
	_oriSize = sourceAnimation._oriSize;
	_size = sourceAnimation._size;
}

Animation::~Animation() {
	ID2D1Bitmap** bitmapItr = _bitmaps;
	do {
		Direct2D::Instance()->DestroyBitmap(*bitmapItr);
	} while (!*(++bitmapItr));
}

void Animation::Draw() {
	if (++_counter >= _interval) {
		//判斷下一個pointer是否為null，如果為null則將圖片切到第一張
		if (!*(++_bitmap)) _bitmap = _bitmaps;
		_counter = 0;
	}
	DrawBitmap(*_bitmap);
}

void Animation::ResetImage() {
	Image::ResetImage();
	_bitmap = _bitmaps;
	_counter = 0;
}
