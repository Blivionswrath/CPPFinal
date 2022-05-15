	/*
	I could not get the shader read to work, this code is by
	Victor Gordon of freeCodeCam.Org. All of shaderClass is his work
	*/
#include "shaderClass.h"
#include <iostream>
std::string readFile(const char* fileName) {


	std::ifstream in(fileName, std::ios::binary);
	if(in){
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);

		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(std::string programName, const char* vertexFile, const char* fragmentFile) {
	name = programName;
	GLint testval;
	GLint abort = 0;
	std::string vertexString = readFile(vertexFile);
	std::string fragmentString = readFile(fragmentFile);

	const char* vertexSource = vertexString.c_str();
	const char* fragmentSource = fragmentString.c_str();
	

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);


	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &testval);
	if (testval == GL_FALSE)
	{
		abort = 1;
		char infolog[1024];
		glGetShaderInfoLog(vertexShader, 1024, NULL, infolog);
		std::cout << "The vertex shader failed to compile with the error:" << std::endl << infolog << std::endl;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &testval);
	if (testval == GL_FALSE)
	{
		abort = 1;
		char infolog[1024];
		glGetShaderInfoLog(fragmentShader, 1024, NULL, infolog);
		std::cout << "The fragment shader failed to compile with the error:" << std::endl << infolog << std::endl;
	}

	glGetProgramiv(ID, GL_LINK_STATUS, &testval);
	if (testval == GL_FALSE)
	{
		abort = 1;
		char infolog[1024];
		glGetProgramInfoLog(ID, 1024, NULL, infolog);
		std::cout << "The program failed to compile with the error:" << std::endl << infolog << std::endl;
	}
	if (abort)
	{
		std::cout << "errors occured, cannot continue, aborting." << std::endl;
		exit(-1);
	}

	//Since the program is made we can free the memory of the individual shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::activateShader() {
	glUseProgram(ID);
}

void Shader::deleteShader() {
	glDeleteProgram(ID);
}