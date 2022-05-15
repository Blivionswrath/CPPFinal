#include "Rock.h"

Rock::Rock() {
	textureFile = "Default.png";

	*health = 5;
	colliderType = Collider::object;
	
}

Rock::Rock(std::string textureName) {
	textureFile = textureName;

	*health = 5;
	colliderType = Collider::object;
}

Rock::Rock(glm::vec3 positionSet) {
	textureFile = "Default.png";
	*position = positionSet;
	*health = 5;
	colliderType = Collider::object;
}
Rock::Rock(glm::vec3 positionSet, glm::vec3 scaleSet) {
	textureFile = "Default.png";
	*position = positionSet;
	*scale = scaleSet;
	*health = 5;
	colliderType = Collider::object;
}

Rock::Rock(std::string textureName, glm::vec3 positionSet, glm::vec3 scaleSet) {
	textureFile = textureName;
	*position = positionSet;
	*scale = scaleSet;
	*health = 5;
	colliderType = Collider::object;
}