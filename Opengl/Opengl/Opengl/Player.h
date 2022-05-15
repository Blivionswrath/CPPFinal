#ifndef PLAYER_H
#define	PLAYER_H
#define GLFW_INCLUDE_NONE

#include "Sprite.h"
#include "Bullet.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class Player : public Sprite {
public:

	int maxAmmo = 100.0f, ammo;
	bool shooting = false;
	ColliderFlag shootingDirection;

	Player();
	Player(std::string texture);
	Player(glm::vec3 position);
	Player(glm::vec3 position, glm::vec3 scale);


	void shoot(ColliderFlag shootingDirection);
	
	ColliderFlag getShootingDirection();

	void heal(float amount); 

	void inputs(GLFWwindow* window);

};

#endif
