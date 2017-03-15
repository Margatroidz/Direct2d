#include "FirstStage.h"
#include "Character.h"
#include "Bullet.h"

struct FirstStage::Impl {
	Character* _character;
	Bullet** _characterBullet;
};

FirstStage::FirstStage() :pimpl(new Impl) {}

void FirstStage::ShootByCharacter(int img, float posX, float posY, float angle, float speed, float radius) {
	for (int i = 0; i < 100; i++) {
		if (pimpl->_characterBullet[i]->IsActive()) continue;
		pimpl->_characterBullet[i]->Load(img, posX, posY, angle, speed, radius);
		break;
	}
}

void FirstStage::OnInitialize() {
	pimpl->_character = new Character();
	pimpl->_character->OnInitialize();
	pimpl->_characterBullet = new Bullet*[100];
	for (int i = 0; i < 100; i++) {
		pimpl->_characterBullet[i] = new Bullet();
		pimpl->_characterBullet[i]->OnInitialize();
		pimpl->_characterBullet[i]->LoadBulletsImage();
	}
}

void FirstStage::OnUpdate() {
	pimpl->_character->OnUpdate();
	for (int i = 0; i < 100; i++) {
		if (pimpl->_characterBullet[i]->IsActive()) {
			if (pimpl->_characterBullet[i]->GetPositionX() < 10 || pimpl->_characterBullet[i]->GetPositionY() < 0 ||
				pimpl->_characterBullet[i]->GetPositionX() > 390 || pimpl->_characterBullet[i]->GetPositionY() > 480) {
				pimpl->_characterBullet[i]->OnInitialize();
			}
			pimpl->_characterBullet[i]->OnUpdate();
		}
	}

	if (pimpl->_character->IsFire() && pimpl->_character->GetInterval() == 0/* && pimpl->_character->GetImmovable() == 0*/) {
		if (pimpl->_character->IsSlowMode()) {
			ShootByCharacter(2, pimpl->_character->GetPositionX() - 10, pimpl->_character->GetPositionY(), 90, 30, 40);
			ShootByCharacter(2, pimpl->_character->GetPositionX() - 8, pimpl->_character->GetPositionY(), 88, 30, 40);
			ShootByCharacter(2, pimpl->_character->GetPositionX() + 10, pimpl->_character->GetPositionY(), 90, 30, 40);
			ShootByCharacter(2, pimpl->_character->GetPositionX() + 8, pimpl->_character->GetPositionY(), 92, 30, 40);
		}
		else {
			//if (pimpl->_detail.power < 48)
			ShootByCharacter(0, pimpl->_character->GetPositionX(), pimpl->_character->GetPositionY(), 90, 20, 40);
			//else
			//	for (i = 0; i < 3; i++) pimpl->_characterShoot(0, pimpl->_character.position, 90 + (i - 1) * 5, 30, 40);
			//if (pimpl->_detail.power > 8) {
			ShootByCharacter(0, pimpl->_character->GetPositionX(), pimpl->_character->GetPositionY(), 80, 20, 40);
			//	pimpl->_addTimeOut(1, pimpl->_characterBullet[n], 'charactorMissile', 0, 5, true);
			ShootByCharacter(0, pimpl->_character->GetPositionX(), pimpl->_character->GetPositionY(), 100, 20, 40);
			//	pimpl->_addTimeOut(1, pimpl->_characterBullet[n], 'charactorMissile', 0, 5, true);
			//	if (pimpl->_detail.power == 128) {
			ShootByCharacter(1, pimpl->_character->GetPositionX(), pimpl->_character->GetPositionY(), 50, 15, 40);
			//		pimpl->_addTimeOut(1, pimpl->_characterBullet[n], 'charactorMissile', 0, 7.5, true);
			ShootByCharacter(1, pimpl->_character->GetPositionX(), pimpl->_character->GetPositionY(), 130, 15, 40);
			//		pimpl->_addTimeOut(1, pimpl->_characterBullet[n], 'charactorMissile', 0, 7.5, true);
			//	}
			//}
		}
	}
}

void FirstStage::OnDraw() {
	pimpl->_character->OnDraw();
	for (int i = 0; i < 100; i++) {
		pimpl->_characterBullet[i]->OnDraw();
	}
}

void FirstStage::OnClose() {
	delete pimpl->_character;
	for (int i = 0; i < 100; i++) {
		delete pimpl->_characterBullet[i];
	}
}
