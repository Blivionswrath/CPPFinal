#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glad/glad.h>


class Texture {
public:
	std::string fileName;
	GLuint ID;
	GLenum textureSlot;

	Texture();
	Texture(std::string fileName);

	void deleteTexture();



};

#endif
