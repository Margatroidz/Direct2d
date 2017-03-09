#pragma once
#include <memory>

class Character {
public:
	Character();
	~Character();
	void Hit();
	void OnLoad();
	void OnInput();
	void OnUpdate();
	void OnDraw();
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};