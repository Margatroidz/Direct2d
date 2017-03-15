#include "Bullet.h"
#include "GameLib.h"
#include <math.h>
#include <vector>

struct Bullet::Impl {
	Bitmap** _bulletPictureCache;
	Bitmap* _bulletPicture;
	bool _isImageBullet;

	int _angle;
	float _trajectoryX;
	float _trajectoryY;
	float _positionX;
	float _positionY;
	float _radius;

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

const bool Bullet::IsActive()
{
	return pimpl->_isActive;
}

const float Bullet::GetPositionX()
{
	return pimpl->_positionX;
}

const float Bullet::GetPositionY()
{
	return pimpl->_positionY;
}

void Bullet::LoadBulletsImage() {
	pimpl->_bulletPictureCache = new Bitmap*[8];
	pimpl->_bulletPictureCache[0] = new Bitmap("../Framework/image/C_bullet_00.png");
	pimpl->_bulletPictureCache[1] = new Bitmap("../Framework/image/C_bullet_01.png");
	pimpl->_bulletPictureCache[2] = new Bitmap("../Framework/image/C_bullet_02.png");
	pimpl->_bulletPictureCache[3] = new Bitmap("../Framework/image/C_bullet_03.png");
	pimpl->_bulletPictureCache[4] = new Bitmap("../Framework/image/E_bullet_00.png");
	pimpl->_bulletPictureCache[5] = new Bitmap("../Framework/image/E_bullet_01.png");
	pimpl->_bulletPictureCache[6] = new Bitmap("../Framework/image/E_bullet_02.png");
	pimpl->_bulletPictureCache[7] = new Bitmap("../Framework/image/E_bullet_03.png");
}

void Bullet::Load(int img, float posX, float posY, float angle, float speed, float radius) {
	//angle = (angle + 360) % 360;
	//pimpl->_trajectoryX;
	//pimpl->_trajectoryY;
	float t_cos = cos(angle * 0.01745329251994329f);
	float t_sin = sin(angle * 0.01745329251994329f);
	pimpl->_trajectoryX = abs(t_cos) < 0.00001 ? 0 : t_cos * speed;
	pimpl->_trajectoryY = abs(t_sin) < 0.00001 ? 0 : t_sin * speed;
	pimpl->_bulletPicture = new Bitmap(*(pimpl->_bulletPictureCache[img]));

	pimpl->_positionX = posX;
	pimpl->_positionY = posY;
	pimpl->_radius = radius;
	pimpl->_maxAngle = 0;
	pimpl->_isActive = true;
	pimpl->_isGraze = false;
	pimpl->_rotation = -angle;
	pimpl->_target = nullptr;

	pimpl->_bulletPicture->SetTopLeftPosition(pimpl->_positionX, pimpl->_positionY);
	pimpl->_bulletPicture->SetAngle(pimpl->_rotation);
}

void Bullet::LoadPos(int img, float posX, float posY, float posDestX, float posDestY, float speed, float radius, float offset) {
	float angle = -atan((posDestY - posY) / (posDestX - posX)) * 57.2957795130823208f;
	if (posDestX < posX) angle += 180;
	Load(img, posX, posY, angle + offset, speed, radius);
}

void Bullet::Redirect(float angle, float speed) {
	//angle = (angle + 360) % 360;
	float t_cos = cos(angle * 0.01745329251994329f);
	float t_sin = sin(angle * 0.01745329251994329f);
	pimpl->_trajectoryX = abs(t_cos) < 0.00001 ? 0 : t_cos * speed;
	pimpl->_trajectoryY = abs(t_sin) < 0.00001 ? 0 : t_sin * speed;
	pimpl->_rotation = -angle;
	if (pimpl->_isImageBullet) pimpl->_bulletPicture->SetAngle(pimpl->_rotation);
}

void Bullet::RedirectPos(float posDestX, float posDestY, float speed, float offset) {
}

void Bullet::ReRotation(int frequency, float angle, int maxAngle, float speed) {
	pimpl->_frequency = frequency;
	pimpl->_anglePer = angle;
	pimpl->_initAngle = 0;
	pimpl->_maxAngle = maxAngle;
	pimpl->_speed = speed;
}

void Bullet::OnInitialize() {
	pimpl->_isActive = false;
	pimpl->_angle = 0;
	pimpl->_initAngle = 0;
	pimpl->_maxAngle = 0;
	pimpl->_isGraze = false;
	pimpl->_rotation = 0.0f;

	pimpl->_frequency = 0;
	pimpl->_anglePer = 0.0f;
	pimpl->_speed = 0.0f;
}

void Bullet::OnUpdate() {
	pimpl->_positionX += pimpl->_trajectoryX;   //x分量 * 彈速
	pimpl->_positionY -= pimpl->_trajectoryY;   //y分量 * 彈速
	pimpl->_bulletPicture->SetTopLeftPosition(pimpl->_positionX, pimpl->_positionY);
	//pimpl->_bulletPicture->SetAngle(pimpl->_rotation);
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
