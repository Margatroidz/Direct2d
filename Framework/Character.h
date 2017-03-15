#pragma once
#include <memory>

class Character {
public:
	Character();
	~Character();
	void Hit();
	const bool IsSlowMode();
	const bool IsFire();
	const int GetInterval();
	const int GetImmovable();
	const float GetPositionX();
	const float GetPositionY();
	void OnInput();
	void OnInitialize();
	void OnUpdate();
	void OnDraw();
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};