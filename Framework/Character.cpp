#include "Character.h"
#include "GameLib.h"

struct Character::Impl {
	Animation* _reiMu;
	Animation* _reiMuTurn;
	Animation* _yuKari;
	Animation* _yuKariTurn;
	Bitmap* _hitPoint;
	Image* _characterPicture;

	float _positionX = 200;
	float _positionY = 400;
	int _immunity;
	int _immovable;
	int _autoMove;
	int _countX;
	int _countY;
	float _moveingX;
	float _moveingY;
	bool _isFire;
	bool _isSlowMode;
	int _interval;
	float _speed;

	//Text* text = nullptr;
};

Character::Character() :pimpl(new Impl) {}

Character::~Character() {}

void Character::Hit() {
	pimpl->_immunity = 300;
	pimpl->_immovable = 90;
	pimpl->_autoMove = 90;
	pimpl->_positionX = 200;
	pimpl->_positionY = 460;
}

void Character::OnLoad() {
	char* reiMu[] = { "../Framework/image/playerm_001.png",
		"../Framework/image/playerm_002.png",
		"../Framework/image/playerm_003.png",
		"../Framework/image/playerm_004.png", };
	pimpl->_reiMu = new Animation(reiMu, 4, 0.1);
	char* yuKari[] = { "../Framework/image/playery_001.png",
		"../Framework/image/playery_002.png",
		"../Framework/image/playery_003.png",
		"../Framework/image/playery_004.png", };
	pimpl->_yuKari = new Animation(yuKari, 4, 0.1);
	pimpl->_hitPoint = new Bitmap("../Framework/image/hitPoint.png");
	pimpl->_characterPicture = pimpl->_reiMu;

	pimpl->_immunity = 0;
	pimpl->_immovable = 0;
	pimpl->_autoMove = 0;
	pimpl->_countX = 0;
	pimpl->_countY = 0;
	pimpl->_moveingX = 0;
	pimpl->_moveingY = 0;
	pimpl->_isFire = false;
	pimpl->_isSlowMode = false;
	pimpl->_interval = 0;
	pimpl->_speed = 1;
}

void Character::OnInput()
{
	//char* format = new char[64];
	//sprintf_s(format, 64, "%f", pimpl->_moveingX);

	//int length = strlen(format) + 1;
	//wchar_t* wFormat = new wchar_t[length];
	//mbstowcs_s(0, wFormat, length, format, _TRUNCATE);

	//if (pimpl->text) delete pimpl->text;
	//pimpl->text = new Text(wFormat);
	//
	//壓住按鍵的時候會連續發送Down的message，怎麼跟我想像的不大一樣，問題 ?
	//
	if (GetKeyDown(KeyCode::KEY_LEFT_ARROW)) pimpl->_moveingX -= 2.5;

	if (GetKeyDown(KeyCode::KEY_RIGHT_ARROW)) pimpl->_moveingX += 2.5;

	if (GetKeyDown(KeyCode::KEY_UP_ARROW)) pimpl->_moveingY -= 2.5;

	if (GetKeyDown(KeyCode::KEY_DOWN_ARROW)) pimpl->_moveingY += 2.5;

	if (GetKeyDown(KeyCode::KEY_SHIFT)) {
		pimpl->_characterPicture = pimpl->_yuKari;
		pimpl->_isSlowMode = true;
	}

	if (GetKeyDown(KeyCode::KEY_Z)) pimpl->_isFire = true;

	if (GetKeyUp(KeyCode::KEY_LEFT_ARROW)) pimpl->_moveingX += 2.5;

	if (GetKeyUp(KeyCode::KEY_RIGHT_ARROW)) pimpl->_moveingX -= 2.5;

	if (GetKeyUp(KeyCode::KEY_UP_ARROW)) pimpl->_moveingY += 2.5;

	if (GetKeyUp(KeyCode::KEY_DOWN_ARROW)) pimpl->_moveingY -= 2.5;

	if (GetKeyUp(KeyCode::KEY_SHIFT)) {
		pimpl->_characterPicture = pimpl->_reiMu;
		pimpl->_isSlowMode = false;
	}

	if (GetKeyUp(KeyCode::KEY_Z)) pimpl->_isFire = false;
}

void Character::OnUpdate() {
	OnInput();

	if (pimpl->_isSlowMode) pimpl->_speed = 0.25;
	else pimpl->_speed = 1;
	if (pimpl->_immovable == 0) {
		pimpl->_positionX += (pimpl->_moveingX * pimpl->_speed);
		pimpl->_positionY += (pimpl->_moveingY * pimpl->_speed);
	}
	if (pimpl->_positionX < 30) pimpl->_positionX = 30;
	if (pimpl->_positionX > 370) pimpl->_positionX = 370;
	if (pimpl->_positionY < 20) pimpl->_positionY = 20;
	if (pimpl->_positionY > 460) pimpl->_positionY = 460;
	if (pimpl->_interval < 0) pimpl->_interval = 10;
	if (pimpl->_isFire) pimpl->_interval--;

	if (pimpl->_immunity > 0) pimpl->_immunity--;
	if (pimpl->_immovable > 0) pimpl->_immovable--;
	if (pimpl->_autoMove > 0) {
		pimpl->_positionY--;
		pimpl->_autoMove--;
	}

	pimpl->_characterPicture->SetTopLeftPosition(pimpl->_positionX, pimpl->_positionY);
	pimpl->_hitPoint->SetTopLeftPosition(pimpl->_positionX, pimpl->_positionY);
	pimpl->_hitPoint->Rotate(0.5);
}

void Character::OnDraw() {
	pimpl->_characterPicture->Draw();
	if (pimpl->_isSlowMode)
		pimpl->_hitPoint->Draw();
	//if (pimpl->text) pimpl->text->Draw();
}
