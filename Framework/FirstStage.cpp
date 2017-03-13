#include "FirstStage.h"
#include "Character.h"

struct FirstStage::Impl {
	Character* _character;
};

FirstStage::FirstStage() :pimpl(new Impl) {}

void FirstStage::OnInitialize() {
	pimpl->_character = new Character();
	pimpl->_character->OnInitialize();
}

void FirstStage::OnUpdate() {
	pimpl->_character->OnUpdate();
}

void FirstStage::OnDraw() {
	pimpl->_character->OnDraw();
}

void FirstStage::OnClose() {
	delete pimpl->_character;
}
