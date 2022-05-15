#define _USE_MATH_DEFINES
#include "Renderer.h"

#include "EBO.h"

#include <math.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/common.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include <stb/stb_image.h>




GLuint* eboIndices = new GLuint[6];
EBO ebo;
Renderer::Renderer() {
	glm::mat4 temp(1.0f);
	temp = glm::ortho(-1000.0f, 1000.0f, -1000.0f, 1000.0f);
	projectionMatrix = temp;

}

bool firstDraw = true;
void Renderer::drawAll(vector<Shader*> shaders, LinkedList* objects) {
	
	if (firstDraw) {

		for (int i = 0; i < 6; i++) {
			eboIndices[i] = objects->head->object->getIndices()[i];
		}
		EBO temp(eboIndices, sizeof(float) * 6);
		ebo = temp;
		firstDraw = false;
	}
	shaders[0]->activateShader();
	//Rotation, scale, translation and projection are the matrices I wanna upload
	GLuint projectionMatLoc = glGetUniformLocation(shaders[0]->ID, "projection");
	//Uniform finding 
	GLuint textureSampler = glGetUniformLocation(shaders[0]->ID, "textureSampler");
	GLuint scaleMatrixLoc = glGetUniformLocation(shaders[0]->ID, "scale");
	GLuint translationMatrixLoc = glGetUniformLocation(shaders[0]->ID, "translation");
	//Upload to those uniforms
	glm::vec4 rotationVector(1.0f);

	glm::mat4 translationMatrix(1.0f);
	glm::mat4 scaleMatrix(1.0f);
	GLfloat textureSlot = (GLfloat)findTexSlot(backGround.sprite.texture.fileName);
	translationMatrix = glm::translate(glm::vec3(0.0));
	//Upload texture slot

	//Upload shader uniforms
	
	glUniform1i(textureSampler, textureSlot);
	glUniformMatrix4fv(projectionMatLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniformMatrix4fv(translationMatrixLoc, 1, GL_FALSE, &translationMatrix[0][0]);
	glUniformMatrix4fv(scaleMatrixLoc, 1, GL_FALSE, &scaleMatrix[0][0]);
	
	//Draw the background
	backGround.sprite.vao.bind();
	ebo.unbind();
	ebo.bind();
	glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);
	backGround.sprite.vao.unbind();
	ebo.unbind();

	if (objects->head != NULL) {
		listNode* p = objects->head;
		listNode* nextNode = p->next;
		while (p != NULL) {

			GameObject* object = p->object;

			//Create matrices for shader
			shaders[1]->activateShader();
			textureSampler = glGetUniformLocation(shaders[1]->ID, "textureSampler");
			glm::vec3 eulerAngles(0, 0, object->rotation / (180 * M_PI));
			GLuint rotationMatrixLoc = glGetUniformLocation(shaders[1]->ID, "rotation");
			translationMatrixLoc = glGetUniformLocation(shaders[1]->ID, "translation");
			scaleMatrixLoc = glGetUniformLocation(shaders[1]->ID, "scale");
			//The z axis is the only one that gets rotated because we are in 2d
			rotationVector.x = 0.0f;
			rotationVector.y = 0.0f;
			rotationVector.z = 1.0f;
			rotationVector.w = cos(object->rotation / (2 * M_PI));
			glm::quat quaternion;
			//quaternion = glm::quat(rotationVector.w, rotationVector.x, rotationVector.y, rotationVector.w);
			quaternion = glm::quat(eulerAngles);
			//Create the rest of the matrices
			glm::mat4 rotationMatrix = glm::toMat4(quaternion);
			
			scaleMatrix = glm::scale(*object->scale);
			translationMatrix = glm::translate(*object->position);

	
			
			
			
			textureSlot = (GLfloat)findTexSlot(object->textureFile);
			//Upload to shader

			glUniform1i(textureSampler, textureSlot);
			glUniformMatrix4fv(rotationMatrixLoc, 1, GL_FALSE, &rotationMatrix[0][0]);
			glUniformMatrix4fv(translationMatrixLoc, 1, GL_FALSE, &translationMatrix[0][0]);
			glUniformMatrix4fv(scaleMatrixLoc, 1, GL_FALSE, &scaleMatrix[0][0]);
			glUniformMatrix4fv(projectionMatLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
			
			object->vao;
			//Bind for drawing
			object->vao.bind();

			ebo.unbind();
			ebo.bind();
			glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);

			object->vao.unbind();
			ebo.unbind();

			p = nextNode;
			if (p != NULL) {

				nextNode = p->next;
			}
		}
	}
}



void Renderer::addBackGround(Background& b) {
	backGround = b;
	createTexture(backGround.sprite.texture.fileName);
}


int currentTexture = 0;
float Renderer::findTexSlot(std::string fileName) {
	
	float ret = GL_TEXTURE0;
	int offset, newTexEnum;
	if (currentTexture != 0 && textureSlots->count(fileName) != 0) {
		multimap<std::string, int>::iterator it = textureSlots->find(fileName);
		
		offset = it->second;
		ret = offset - ret;
	}
	else {
		if (textureSlots->count(fileName) != 0) {
			multimap<std::string, int>::iterator it = textureSlots->find(fileName);
			offset = it->second;
			ret = offset - ret;
		}
		else {

			createTexture(fileName);
			newTexEnum = GL_TEXTURE0 + currentTexture;
			ret = currentTexture;
			
		}
		currentTexture++;


	}
	
	return ret;
}



void Renderer::createTexture(std::string fileName) {
	multimap<std::string, int>::iterator it;
	
	int newTexEnum = currentTexture + GL_TEXTURE0;
	
	textureSlots->insert(std::pair<string, int>(fileName, newTexEnum));
	
	
	imageLoad_stb(fileName.c_str(), 64, 64, 4, newTexEnum);

}

void Renderer::checkCollision(LinkedList* objects){
	listNode* currentNode = objects->head;
	int iteration = 0;
	while (currentNode != NULL) {
		iteration++;
		listNode* sweepingNode = objects->head;
		
		if (iteration > 1) {
			currentNode = currentNode->next;
		}
		listNode* nextNode = currentNode->next;
		while (sweepingNode != NULL) {

			if (currentNode->next != NULL) {
				if (sweepingNode->object == currentNode->object) {
					sweepingNode = sweepingNode->next;
					continue;
				}
			}
			else if (currentNode->next == NULL) {
				currentNode = currentNode->next;
				break;
			}

			if (sweepingNode == currentNode && nextNode == NULL) {
				currentNode = currentNode->next;
				continue;
			}
			else if (sweepingNode == currentNode) {
				sweepingNode = sweepingNode->next;
				continue;

			}
			float middleX1, middleY1, middleX2, middleY2;
			float middleOffset1, middleOffset2;
			middleOffset1 = 0.5f * currentNode->object->scale->x;
			middleX1 = currentNode->object->position->x;
			middleY1 = currentNode->object->position->y;

			middleX2 = sweepingNode->object->position->x;
			middleY2 = sweepingNode->object->position->y;
			middleOffset2 = 0.5f * sweepingNode->object->scale->x;

			bool vertical = false;
			bool horizontal = false;

			float bottom1 = middleY1 - middleOffset1;
			float bottom2 = middleY2 - middleOffset2;
			float top1 = middleY1 + middleOffset1;
			float top2 = middleY2 + middleOffset2;
			float right1 = middleX1 + middleOffset1;
			float right2 = middleX2 + middleOffset2;
			float left1 = middleX1 - middleOffset1;
			float left2 = middleX2 - middleOffset2;
			float distanceX;
			float distanceY;
			//Check the bottom of sprite 1 to the top of sprite 2, and then check the top of sprite one against  bottom of 2

			if (middleY1 >= middleY2) {
				vertical = (bottom1 <= top2);
				if (vertical) {
					distanceY = abs(currentNode->object->position->y - sweepingNode->object->position->y);
				}
			}
			else {
				vertical = (top1 >= bottom2);
				if (vertical) {
					distanceY = abs(sweepingNode->object->position->y - currentNode->object->position->y);
				}
			}

			//Check the left of sprite one against the right of 2, and then check the right of sprite 1 against left of 2
			//If there is an intersection for that axis, calculate the distance from center to center of the sprites.
			//This allows me to know if we need to clamp to the horizontal or vertical axis
			if (middleX1 >= middleX2) {
				horizontal = (left1 <= right2);
				if (horizontal) {
					distanceX = abs(currentNode->object->position->x - sweepingNode->object->position->x);
				}
			}
			else {
				horizontal = (right1 >= left2);
				if (horizontal) {
					distanceX = abs(currentNode->object->position->x - sweepingNode->object->position->x);
				}
			}

			if (vertical && horizontal) {
				//Flag a collision for this object on it's right side

				bool verticalClamp = distanceY >= distanceX;
				if (right1 >= left2 && left1 < left2 && !verticalClamp) {
					if (currentNode->object->collisions->count(sweepingNode->object)) {
						multimap<GameObject*, ColliderFlag>::iterator it = currentNode->object->collisions->find(sweepingNode->object);
						it->second = ColliderFlag::right;
					}
					else {
						currentNode->object->collisions->insert(std::pair<GameObject*, ColliderFlag>(sweepingNode->object, ColliderFlag::right));
					}
				}
				else if (left1 <= right2 && right1 > right2 && !verticalClamp) {
					if (currentNode->object->collisions->count(sweepingNode->object)) {
						multimap<GameObject*, ColliderFlag>::iterator it = currentNode->object->collisions->find(sweepingNode->object);
						it->second = ColliderFlag::left;
					}
					else {
						currentNode->object->collisions->insert(std::pair<GameObject*, ColliderFlag>(sweepingNode->object, ColliderFlag::left));
					}
				}
				else if (bottom1 <= top2 && top1 > top2) {
					if (currentNode->object->collisions->count(sweepingNode->object)) {
						multimap<GameObject*, ColliderFlag>::iterator it = currentNode->object->collisions->find(sweepingNode->object);
						it->second = ColliderFlag::bottom;
					}
					else {
						currentNode->object->collisions->insert(std::pair<GameObject*, ColliderFlag>(currentNode->object, ColliderFlag::bottom));
					}
				}
				else if (top1 >= bottom2 && bottom2 > bottom1) {
					if (currentNode->object->collisions->count(sweepingNode->object)) {
						multimap<GameObject*, ColliderFlag>::iterator it = currentNode->object->collisions->find(sweepingNode->object);
						it->second = ColliderFlag::top;
					}
					else {
						currentNode->object->collisions->insert(std::pair<GameObject*, ColliderFlag>(sweepingNode->object, ColliderFlag::top));
					}
				}

				GameObject::objectCollide(currentNode->object, sweepingNode->object);
			}

			sweepingNode = sweepingNode->next;
		}

	}
}


GLuint Renderer::imageLoad_stb(const char* fileName, int width, int height, int numChannels, int textureSlot) {
	stbi_set_flip_vertically_on_load(true);
	int testWidth, testHeight, channels;
	unsigned char* image = stbi_load(fileName, &testWidth, &testHeight, &channels, 0);

	GLuint textureID;
	GLenum error = glGetError();
	glGenTextures(1, &textureID);
	glActiveTexture(textureSlot);
	glBindTexture(GL_TEXTURE_2D, textureID);
	error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cout << error << endl;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cout << error << endl;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cout << error << endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, testWidth, testHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cout << error << endl;
	}

	
	//Free the image from memory
	stbi_image_free(image);

	return textureID;
}
