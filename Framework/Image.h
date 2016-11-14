#pragma once
#include <vector>

struct ID2D1Bitmap;
struct Point {
	float x;
	float y;
};

class Image
{
public:
	virtual ~Image() {};
	virtual void Draw() = 0;
	void SetPosition(float x, float y);
	void Transfer(float x, float y);
	friend class Direct2D;
protected:
	ID2D1Bitmap* _bitmap;
	Point _topLeft;
};

class Bitmap : public Image
{
public:
	Bitmap(char* resourceName);
	Bitmap(int resourceNumber);
	virtual ~Bitmap();
	void Draw();
};

class Animation : public Image
{
public:
	Animation(char** resourceName, int number, float interval);
	Animation(int* resourceNumber, int number, float interval);
	virtual ~Animation();
	void Draw();
private:
	std::vector<ID2D1Bitmap*> _bitmap[];
};