#include "Enemy.h"

Enemy::~Enemy() {
}

const bool Enemy::IsActive() {
	return false;
}

const float Enemy::GetPositionX() {
	return 0.0f;
}

const float Enemy::GetPositionY() {
	return 0.0f;
}

const int Enemy::GetPoint() {
	return 0;
}

const int Enemy::GetPower() {
	return 0;
}

const int Enemy::GetBomb() {
	return 0;
}

const int Enemy::GetExtend() {
	return 0;
}

void Enemy::SetItem(int point, int power, int bomb, int extend) {
}

void Enemy::LoadEnemysImage() {
}

void Enemy::Load(int img, float posX, float posY, float angle, float speed, int hp) {
}

void Enemy::LoadPos(int img, float posX, float posY, float posDestX, float posDestY, float speed, float radius, int hp) {
}

void Enemy::Redirect(float angle, float speed) {
}

void Enemy::RedirectPos(float posDestX, float posDestY, float speed) {
}

void Enemy::ReRotation(int frequency, float angle, int maxAngle, float speed) {
}

void Enemy::OnInitialize() {
}

void Enemy::OnUpdate() {
}

void Enemy::OnDraw() {
}
