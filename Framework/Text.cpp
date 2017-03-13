#include "Text.h"
#include "Direct2D.h"
#include <string.h>

struct Text::Impl {
	Impl();
	~Impl();
	wchar_t* _text;
	IDWriteTextFormat* _format;
	ID2D1SolidColorBrush* _brush;
};

Text::Impl::Impl() :_format(nullptr), _brush(nullptr) {}

Text::Impl::~Impl() {
	delete[] _text;
	Direct2D::Instance()->DestroyText(_format, _brush);
}

Text::Text(wchar_t* text) : pimpl(new Impl) {
	pimpl->_format = Direct2D::Instance()->CreateTextFormat("Gabriola", 50);
	pimpl->_brush = Direct2D::Instance()->CreateBrush();
	int length = wcslen(text) + 1;
	pimpl->_text = new wchar_t[length];
	wcscpy_s(pimpl->_text, length, text);
}

Text::~Text() {
}

void Text::Draw()
{
	Direct2D::Instance()->DrawTextD(pimpl->_text, pimpl->_format, pimpl->_brush);
}
