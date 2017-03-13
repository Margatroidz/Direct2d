#pragma once
#include <memory>

class Bullet {
public:
	Bullet();
	~Bullet();
	static void LoadImageB();
	void Load(int img, float posX, float posY, float angle, float speed, float radius);
	void LoadPos(int img, float posX, float posY, float posDestX, float posDestY, float speed, float radius, float offset);
	void Redirect(float angle, float speed);
	void RedirectPos(float posDest, float speed, float offset);
	void ReRotation(float frequency, float angle, float maxAngle, float speed);
	void InActive();
	void OnInitialize();
	void OnUpdate();
	void OnDraw();
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};