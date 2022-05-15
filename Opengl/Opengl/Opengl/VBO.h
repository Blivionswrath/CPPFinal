#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO {
public : 

	GLuint ID;
	//This is the constructer that will be used to generate a new VBO
	VBO();
	VBO(GLfloat* vertices, GLsizeiptr size, GLenum drawType);

	//Unbind and bind the VBO to 
	void bind();

	void unbind();

	void deleteVBO();


	VBO& operator&(VBO& b) {
		ID = b.ID;
	}
};

#endif 

