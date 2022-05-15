#include "VBO.h"

VBO::VBO() {
	ID = -1;
}

VBO::VBO(GLfloat* vertices, GLsizeiptr size, GLenum drawType) {
	//This creates the buffer and assigns it to ID
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	//Will likely be adding the ability to change draw types in the future
	//Currently this sets vertices to a static draw array though
	glBufferData(GL_ARRAY_BUFFER, size, vertices, drawType);

}

void VBO::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::deleteVBO() {
	glDeleteBuffers(1, &ID);
}