#pragma once
#include <string>
#include <memory>

class Text {
public:
	Text(wchar_t* text);
	~Text();
	void Draw();
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};