#pragma once
#include <memory>

class Character {
public:
	Character();
	~Character();
	void Hit();
	void OnInput();
	void OnInitialize();
	void OnUpdate();
	void OnDraw();
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};