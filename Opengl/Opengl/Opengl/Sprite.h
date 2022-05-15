#ifndef SPRITE_H
#define SPRITE_H
using namespace std;


#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "VBO.h"
#include "VAO.h"
#include "GameObject.h"


class Sprite : public GameObject {
public:

	//A string to the texture file.
	Texture texture;



	bool isStatic = false;
	
	Sprite();
	Sprite(std::string textureFile);
	Sprite(std::string textureFile, glm::vec4 position);
	Sprite(std::string textureFile, glm::vec4 position, glm::vec3 scale);
	
	~Sprite();

	Sprite& operator=(Sprite& b) {
		texture = b.texture;
		vao = b.vao;
		vbo = b.vbo;
		return *this;
	}
	

};
#endif