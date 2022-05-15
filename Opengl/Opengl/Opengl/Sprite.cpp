#include "Sprite.h"



Sprite::~Sprite() {
	vao.deleteVAO();
	vbo.deleteVBO();
}
Sprite::Sprite() {
	texture.fileName = "Default.png";

	VAO temp1 = createVAO();
	vao = temp1;
	VBO temp2 = createVBO();
	vbo = temp2;
	
	vao.linkAttrib(vbo, 0, 3, sizeof(float) * 5, 0);
	vao.linkAttrib(vbo, 1, 2, sizeof(float) * 5, sizeof(float) * 3);
}

Sprite::Sprite(std::string textureFile) {
	texture.fileName = textureFile;

	VAO temp1 = createVAO();
	vao = temp1;
	VBO temp2 = createVBO();
	vbo = temp2;
	vao.linkAttrib(vbo, 0, 3, sizeof(float) * 5, 0);
	vao.linkAttrib(vbo, 1, 2, sizeof(float) * 5, sizeof(float) * 3);
}

Sprite::Sprite(std::string textureFile, glm::vec4 position) {
	texture.fileName = textureFile;
	VAO temp1 = createVAO();
	vao = temp1;
	VBO temp2 = createVBO();
	vbo = temp2;
	vao.linkAttrib(vbo, 0, 3, sizeof(float) * 5, 0);
	vao.linkAttrib(vbo, 1, 2, sizeof(float) * 5, sizeof(float) * 3);
}


Sprite::Sprite(std::string textureFile, glm::vec4 position, glm::vec3 scale) {
	texture.fileName = textureFile;
	VAO temp1 = createVAO();
	vao = temp1;
	VBO temp2 = createVBO();
	vbo = temp2;
	vao.linkAttrib(vbo, 0, 3, sizeof(float) * 5, 0);
	vao.linkAttrib(vbo, 1, 2, sizeof(float) * 5, sizeof(float) * 3);
}
