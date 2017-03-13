#include "Bullet.h"
#include "GameLib.h"
#include <math.h>
#include <vector>

struct Bullet::Impl {
	static Bitmap** _bulletPictureCache;
	Bitmap* _bulletPicture;
	bool _isImageBullet;

	int _angle;
	float _trajectoryX;
	float _trajectoryY;
	float _positionX;
	float _positionY;

	int _initAngle;
	int _maxAngle;
	bool _isActive;
	bool _isGraze;
	float _rotation;
	void* _target;

	int _frequency;
	float _anglePer;
	float _speed;
};

Bullet::Bullet() :pimpl(new Impl) {}

Bullet::~Bullet() {}

void Bullet::LoadImageB() {
}

void Bullet::Load(int img, float posX, float posY, float angle, float speed, float radius) {
}

void Bullet::LoadPos(int img, float posX, float posY, float posDestX, float posDestY, float speed, float radius, float offset) {
	float angle = -atan((posDestY - posY) / (posDestX - posX)) * 57.2957795130823208;
	if (posDestX < posX) angle += 180;
	Load(img, posX, posY, angle + offset, speed, radius);
}

void Bullet::Redirect(float angle, float speed) {
	//angle = (angle + 360) % 360;
	float t_cos = cos(angle * 0.01745329251994329);
	float t_sin = sin(angle * 0.01745329251994329);
	pimpl->_trajectoryX = abs(t_cos) < 0.00001 ? 0 : t_cos * speed;
	pimpl->_trajectoryY = abs(t_sin) < 0.00001 ? 0 : t_sin * speed;
	pimpl->_rotation = -angle;
	if (pimpl->_isImageBullet) pimpl->_bulletPicture->SetAngle(pimpl->_rotation);
}

void Bullet::RedirectPos(float posDest, float speed, float offset) {
}

void Bullet::ReRotation(float frequency, float angle, float maxAngle, float speed) {
	pimpl->_frequency = frequency;
	pimpl->_anglePer = angle;
	pimpl->_initAngle = 0;
	pimpl->_maxAngle = maxAngle;
	pimpl->_speed = speed;
}

void Bullet::InActive() {
	pimpl->_isActive = false;
}

void Bullet::OnInitialize() {
}

void Bullet::OnUpdate() {
	pimpl->_positionX += pimpl->_trajectoryX;   //x分量 * 彈速
	pimpl->_positionY -= pimpl->_trajectoryY;   //y分量 * 彈速
	pimpl->_bulletPicture->SetTopLeftPosition(pimpl->_positionX, pimpl->_positionY);
	pimpl->_bulletPicture->SetAngle(pimpl->_rotation);
	if (pimpl->_initAngle < pimpl->_maxAngle) {
		if (pimpl->_initAngle % pimpl->_frequency == 0) {
			Redirect((-pimpl->_rotation) + pimpl->_anglePer, pimpl->_speed);
		}
		pimpl->_initAngle++;
	}
}

void Bullet::OnDraw() {
	if (pimpl->_isActive) {
		pimpl->_bulletPicture->Draw();
	}
}
