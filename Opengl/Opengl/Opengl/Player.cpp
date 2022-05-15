#include <iostream>
#include "Player.h"

Player::Player(){
	textureFile = "UFO.png";

	ammo = maxAmmo;
	health = maxHealth;
	colliderType = Collider::player;
	speedX = float(0.0f);
	speedY = float(0.0f);
}

Player::Player(std::string textureName) {
	textureFile = textureName;

	ammo = maxAmmo;
	health = maxHealth;
	colliderType = Collider::player;
	speedX = float(0.0f);
	speedY = float(0.0f);
}

Player::Player(glm::vec3 position) {
	textureFile = "UFO.png";
	this->position = &position;
	ammo = maxAmmo;
	health = maxHealth;
	colliderType = Collider::player;
	speedX = float(0.0f);
	speedY = float(0.0f);
}

Player::Player(glm::vec3 position, glm::vec3 scale) {
	textureFile = "UFO.png";
	health = maxHealth;
	ammo = maxAmmo;
	this->position = &position;
	this->scale = &scale;
	colliderType = Collider::player;
	speedX = float(0.0f);
	speedY = float(0.0f);

}

ColliderFlag Player::getShootingDirection() {
	return shootingDirection;
}

void Player::shoot(ColliderFlag shootingDirection) {
	shooting = true;
	this->shootingDirection = shootingDirection;
}


bool upPressed = false;
bool downPressed = false;
bool rightPressed = false;
bool leftPressed = false;
int upKeyCycleCount = 1;
bool canShoot = true;
void Player::inputs(GLFWwindow* window) {
	bool movingX = false;
	bool movingY = false;


	//==============================
	//A simple frame by frame timer
	//==============================
	if (!canShoot) {

		upKeyCycleCount++;
		if (upKeyCycleCount % 60 == 0) {
			upKeyCycleCount = 1;
			canShoot = true;
			
		}
	}

	//=================
	//Up arrow controls
	//=================

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && canShoot) {
		shootingDirection = ColliderFlag::top;
		shooting = true;
		shoot(ColliderFlag::top);
		canShoot = false;
	}


	//===================
	//Down arrow controls
	//===================
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && canShoot) {
		shootingDirection = ColliderFlag::bottom;
		shooting = true;
		shoot(ColliderFlag::bottom);
		canShoot = false;
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && canShoot) {
		shootingDirection = ColliderFlag::right;
		shooting = true;
		shoot(ColliderFlag::right);
		canShoot = false;
	}


	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && canShoot) {
		shootingDirection = ColliderFlag::left;
		shooting = true;
		shoot(ColliderFlag::left);
		canShoot = false;
	}




	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		if (speedX < maxSpeed) {
			speedX += .25f;
		}
		position->x += speedX;
		movingX = true;
	}
	
	
	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		//This if statement checks to see if we are already moving,
		//acceleration could be built faster without it by pressing both keys
		if (speedX < maxSpeed && !movingX) {
			speedX += -.25f;
		}
		movingX = true;

	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !movingY) {
		if (speedY < maxSpeed) {
			speedY += .25f;
		}
		movingY = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (speedY < maxSpeed) {
			speedY += -.25f;
		}
		movingY = true;
	}


	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE && !movingX) {
		speedX = 0;
	}


	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE && !movingX) {
		speedX = 0;
	}
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE && !movingY){
		speedY = 0;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE && !movingY) {
		speedY = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		//create a new gameobject with bullet collidertype. Add it to render list.
		
	}
}


void Player::heal(float amount) {
	
	*health += amount;
	if (health > maxHealth) {
		health = maxHealth;
	}
}