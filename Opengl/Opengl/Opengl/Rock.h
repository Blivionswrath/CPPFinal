#ifndef ROCK
#define ROCK

#include "Sprite.h"

class Rock : public Sprite{
	
public:
	Rock();
	Rock(std::string textureName);
	Rock(glm::vec3 position);
	Rock(glm::vec3 position, glm::vec3 scale);
	Rock(std::string textureName, glm::vec3 position, glm::vec3 scale);
	

};

#endif
