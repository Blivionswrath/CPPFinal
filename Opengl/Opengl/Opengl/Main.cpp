#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Texture.h"
#include "Sprite.h"
#include "Background.h"
#include "shaderClass.h"
#include "CollisionEvent.h"
#include "GameObject.h"
#include "LinkedList.h"


#include "Player.h"
#include "Renderer.h"
#include "Bullet.h"
#include "friendlyBullet.h"
#include "Rock.h"

#include <iostream>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/common.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

void updateAll(LinkedList* objects);

int main() {
	//This is the window setup
	glfwInit();
	//Indicate the version of gl we are using 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(900, 900, "UFO Joe", NULL, NULL);
	glfwMakeContextCurrent(window);
	
	if (window == NULL) {
		std::cout << "ERROR: Could not initialize glfw window.\nExiting...";
		return 0;
	}
	//Glad init
	gladLoadGL();
	glViewport(0, 0, 900, 900);

	
	vector<Shader*> shaders;
	Shader shaderProgram("default", "vertexShader.txt", "fragmentShader.txt");
	Shader entityShader("entity","entityVertex.txt", "fragmentShader.txt");
	

	shaders.push_back(&shaderProgram);
	shaders.push_back(&entityShader);

	Renderer* renderer = new Renderer;

	LinkedList* objects = new LinkedList;


	Background backGround(-1000, 1000, -1000, 1000, "Desert.png", 10);
	
	


	Rock* rock = new Rock(glm::vec3(200.0f, 100.0f, 1.0f));
	Player* player = new Player();
	objects->insert(rock);
	objects->insert(player);
	renderer->addBackGround(backGround);

	/*
	Bullet* bullet1= new Bullet(glm::vec3(3.0f, 3.0f, 3.0f));
	Bullet* bullet2 = new Bullet(glm::vec3(1300.0f, 1300.0f, 1.0f));
	Bullet* bullet3 = new Bullet(glm::vec3(1350.0f, 1350.0f, 1.0f));
	objects.push_back(bullet1);
	objects.push_back(bullet2);
	objects.push_back(bullet3); 
	*/


	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//I will have to convert back to vector as an extra step or implement linked list into renderer
		renderer->drawAll(shaders, objects);

		glfwSwapBuffers(window);

		player->inputs(window);

		if (player->shooting) {
			glm::vec3 position(*player->position);
			glm::vec3 scale(*player->scale);
			float xAdjust;
			float yAdjust;
			ColliderFlag shootingDirection = player->getShootingDirection();
			glm::vec2 speeds(player->speedX, player->speedY);
			
			if (shootingDirection == ColliderFlag::bottom || shootingDirection == ColliderFlag::top) {
				shootingDirection == ColliderFlag::top ? yAdjust = 1.0f : yAdjust = -1.0f;
				scale.x = scale.x / 3;
				float yTemp = position.y;
				position.y =   yTemp + yAdjust * ((0.5f * player->scale->y) + ( 0.5f * scale.y));
				speeds.y = yAdjust * (player->speedY + 10.0f);
			}
			else if (shootingDirection != ColliderFlag::none){
				shootingDirection == ColliderFlag::right ? xAdjust = 1.0f : xAdjust = -1.0f;
				scale.y = scale.y / 3;

				position.x = position.x + xAdjust * (( 0.5f * player->scale->x) + (0.5f * scale.x));
				speeds.x = xAdjust * (player->speedX + 10.0f);
			}
			Bullet* bullet = new FriendlyBullet(position, scale, speeds);
			 
			objects->insert(bullet);
			player->shooting = false;
		}
		player->rotate(10.0f);
		
		listNode* p = objects->head;
		while (p) {

			if (p->object->update()) {
				//Successfully updated, do nothing (The object didnt get deleted)
			}
			else {
				listNode* p2 = p;
				p = p->next;
				objects->remove(p2->object);
			}
			p = p->next;
		}

		renderer->checkCollision(objects);
		glfwPollEvents();

		
		
	}



	shaderProgram.deleteShader();
	//TODO: delete all objects
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}

void updateAll(LinkedList* objects) {
	listNode* currentNode = objects->head;
	listNode* nextNode = currentNode->next;
	while (currentNode != NULL) {
		
		currentNode->object->update();

		currentNode = nextNode;
		if (currentNode != NULL) {
			nextNode = currentNode->next;
		}
	}


}