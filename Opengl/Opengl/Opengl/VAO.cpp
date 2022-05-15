#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void VAO::linkAttrib(VBO& VBO, GLuint layout, GLuint size, GLuint stride, GLuint offset) {
	//Binds the VBO and VAO so we are working with it
	bind();
	VBO.bind();
	//Defines what this specific VBO represents and how the GPU should read each set of data.
	//Param 1: This parameter specifies which layout in the shader it is
	//Param 2: this paramater specifies how many numbers per vertice are used (3 for x, y, z)
	//Param 3: This parameter specifies the data type
	//Param 4: Represents whether our data has been normalized, mine has not
	//Param 5: Stride defines whether there is a byte offset between each data point, this will change as I add textures
	//and other things that change the data size of each vertice
	//Param 6: This specifies where the the data for this attrib begins.
	
	//This creates and enables the location aspect of the vertices
	glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(layout);
	
	//Unbind the VAO and VBO as cleanup
	
	unbind();
	VBO.unbind();
}

void VAO::bind() {
	glBindVertexArray(ID);
}

void VAO::unbind() {
	glBindVertexArray(0);
}

void VAO::deleteVAO() {
	glDeleteVertexArrays(1, &ID);
}