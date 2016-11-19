#pragma once

struct ID2D1Bitmap;

class Image
{
public:
	virtual ~Image() {};
	virtual void Draw() = 0;
	void SetPosition(float x, float y);
	void Transfer(float x, float y);
	friend class Direct2D;
protected:
	float _topLeftX;
	float _topLeftY;
};

class Bitmap : public Image
{
public:
	Bitmap(char* resourceName);
	Bitmap(int resourceNumber);
	virtual ~Bitmap();
	void Draw();
private:
	ID2D1Bitmap* _bitmap;
};

class Animation : public Image
{
public:
	Animation(char** resourceName, int number, float interval);
	Animation(int* resourceNumber, int number, float interval);
	virtual ~Animation();
	void Draw();
private:
	ID2D1Bitmap** _bitmaps;
	ID2D1Bitmap** _bitmap;
	const int _interval;
	int _counter;
};