#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string readFile(const char* fileName);

class Shader
{
public:
	GLuint ID;
	std::string name;
	Shader(std::string programName, const char* vertexFile, const char* fragmentFile);

	void activateShader();
	void deleteShader();

};
#endif