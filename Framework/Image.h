#pragma once
#include <d2dbasetypes.h>
struct ID2D1Bitmap;

class Image
{
public:
	Image();
	virtual ~Image() {};
	virtual void Draw() = 0;
	virtual void ResetImage();
	void SetTopLeftPosition(float x, float y);
	void Rotate(float angle);
	void SetAngle(float angle);
	void Transfer(float x, float y);
	void ResetSize();
	void Resize(float width, float high);
	void Scale(float scaleX, float scaleY);
	void SetOpacity(float opacity);
protected:
	void DrawBitmap(ID2D1Bitmap* bitmap);
	D2D_POINT_2F _topLeft;
	D2D_SIZE_F _oriSize;
	D2D_SIZE_F _size;
	float _opacity;
	float _rotateAngle;
};

class Bitmap : public Image
{
public:
	Bitmap(char* path);
	~Bitmap();
	void Draw();
private:
	ID2D1Bitmap* _bitmap;
};

class Animation : public Image
{
public:
	Animation(char** resourcePath, int number, float interval);
	~Animation();
	void Draw();
	void ResetImage();
private:
	ID2D1Bitmap** _bitmaps;
	ID2D1Bitmap** _bitmap;
	const int _interval;
	int _counter;
};