#pragma once
#include <memory>

class Enemy {
public:
	Enemy();
	~Enemy();
	const bool IsActive();
	const float GetPositionX();
	const float GetPositionY();
	const int GetPoint();
	const int GetPower();
	const int GetBomb();
	const int GetExtend();
	void SetItem(int point, int power, int bomb, int extend);
	void LoadEnemysImage();
	void Load(int img, float posX, float posY, float angle, float speed, int hp);
	void LoadPos(int img, float posX, float posY, float posDestX, float posDestY, float speed, float radius, int hp);
	void Redirect(float angle, float speed);
	void RedirectPos(float posDestX, float posDestY, float speed);
	void ReRotation(int frequency, float angle, int maxAngle, float speed);
	void OnInitialize();
	void OnUpdate();
	void OnDraw();
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};