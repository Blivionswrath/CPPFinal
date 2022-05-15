#ifndef	VAO_CLASS_H
#define	VAO_CLASS_H

#include "VBO.h"
#include <glad/glad.h>

class VAO {
public:
	//ID number for this vao
	GLuint ID;
	
	//Constructor
	VAO();

	void linkAttrib(VBO& VBO, GLuint layout, GLuint size, GLuint stride, GLuint offset);
	//Binds vao to the current context for rendering
	void bind();

	void unbind();

	void deleteVAO();
};


#endif
