#include "friendlyBullet.h"

FriendlyBullet::FriendlyBullet() {
	colliderType = Collider::friendlyBullet;
	textureFile = "Default.png";
}

FriendlyBullet::FriendlyBullet(glm::vec3 position, glm::vec3 scale) {
	colliderType = Collider::friendlyBullet;
	this->position = &position;
	this->scale = &scale;
	textureFile = "Default.png";
}

FriendlyBullet::FriendlyBullet(glm::vec3 position, glm::vec3 scale, glm::vec2 speeds) {
	colliderType = Collider::friendlyBullet;
	this->position = &position;
	this->scale = &scale;
	textureFile = "Default.png";
	speedX = speeds.x;
	speedY = speeds.y;
}

/*
void GameObject::update() {
	//======================
	//Normal update function
	//======================
	//Clamp object speeds
	//======================
		
	if (speedX > 10 || speedX < -10) {
		float unarySign;
		speedX < 0 ? unarySign = -1 : unarySign = 1;
		speedX = unarySign * 10;
	}
	if (speedY > 10 || speedY < -10) {
		float unarySign;
		speedY < 0 ? unarySign = -1 : unarySign = 1;
		speedY = unarySign * 10;
	}
	//===============
	//update position
	//===============
	position.x += speedX;
	position.y += speedY;
	//Special check to delete this bullet
	

}
*/
