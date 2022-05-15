#include "Bullet.h"

Bullet::Bullet() {
	colliderType = Collider::bullet;
	speedX = 10.0f;
	*health = 5.0f;
}

Bullet::Bullet(glm::vec3 position) {
	this->position = &position;
	scale = &defaultScale;

	speedX = 10.0f;
	*health = 5.0f;
}

Bullet::Bullet(glm::vec3 position, glm::vec3 scale) {
	this->position = &position;
	this->scale = &scale;

	speedX = 10.0f;
	*health = 5.0f;
}

Bullet::Bullet(glm::vec3 position, glm::vec3 scale, glm::vec2 speeds) {

	speedX = speeds.x;
	speedY = speeds.y;
	*health = 5.0f;
}