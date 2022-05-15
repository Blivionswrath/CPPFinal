#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

class EBO {
public:
	GLuint ID;
	GLsizei size;
	
	EBO();
	EBO(GLuint* indices, GLsizeiptr size);

	void bind();
	void unbind();
	void deleteEBO();

	EBO& operator=(EBO& b) {
		ID = b.ID; 
		size = b.size;
		return *this;
	}

};


#endif

