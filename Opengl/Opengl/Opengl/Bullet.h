#ifndef BULLET_H
#define BULLET_H

#include "Sprite.h"

class Bullet : public Sprite {
public:
	
	Bullet();
	Bullet(glm::vec3 position);
	Bullet(glm::vec3 position, glm::vec3 scale);
	Bullet(glm::vec3 position, glm::vec3 scale, glm::vec2 speeds);


};

#endif
