#ifndef RENDERER_H
#define RENDERER_H
#include <vector>
#include <map>
#include <stb/stb_image.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"
#include "Background.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Player.h"
#include "Rock.h"
#include "LinkedList.h"



class Renderer {
public:
	Background backGround;
	
	std::vector<GameObject*>* objects = new vector<GameObject*>;
	std::multimap<std::string, int>* textureSlots = new std::multimap<std::string, int>;
	glm::mat4 projectionMatrix;
	Renderer();
	//Add a sprite to the render list
	void addBackGround(Background &backGround);
	//returns the rest of the sprites to draw them seperately
	void drawAll(vector<Shader*> shaderProgram, LinkedList* objects);
	float findTexSlot(std::string fileName);
	
	void createTexture(std::string fileName);
	GLuint imageLoad_stb(const char* fileName, int width, int height, int numChannels, int textureSlot);
	void checkCollision(LinkedList* objects);


};

#endif