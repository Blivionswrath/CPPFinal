#ifndef FRIENDLYBULLET_H
#define FRIENDLYBULLET

#include "Bullet.h"

class FriendlyBullet : public Bullet {
public:
	FriendlyBullet();
	FriendlyBullet(std::string);
	FriendlyBullet(glm::vec3 position, glm::vec3 scale);
	FriendlyBullet(glm::vec3 position, glm::vec3 scale, glm::vec2 speeds);
	
};



#endif