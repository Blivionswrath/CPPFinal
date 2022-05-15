#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "VAO.h"
#include "VBO.h"
#include "CollisionEvent.h"


#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
//RenderManager Class?



//I may abstract the sprite to here so I can access both it and the collisions from GameObject

static glm::vec3 defaultPosition = glm::vec3(0.0);
static glm::vec3 defaultScale = glm::vec3(100.0f, 100.0f, 1.0f);


	const GLfloat vertices[] = {
	0.5f, 0.5f, 0.0f,		//Top right vertice
	1.0f, 1.0f,				//Top right UV
	-0.5f, 0.5f, 0.0f,		//Top left vertice
	0.0f, 1.0f,				//Top left UV
	-0.5f, -0.5f, 0.0f,		//Bottom left vertice
	0.0f, 0.0f,				//Bottom left UV
	0.5f, -0.5f, 0.0f,		//Bottom right vertice
	1.0f, 0.0f				//Bottom right UV
	};

	const GLuint indices[] = {
		3, 0, 1,
		1, 2, 3
	};






	class GameObject {
public:

	//Sprite sprite;
	std::string textureFile;
	Collider colliderType;
	//Maps which side has been collided with and what it is touching
	std::multimap<GameObject*, ColliderFlag>* collisions = new multimap<GameObject*, ColliderFlag>;
	glm::vec3* position = new glm::vec3(defaultPosition);
	glm::vec3* scale = new glm::vec3(defaultScale);
	VAO vao;
	VBO vbo;

	float rotation = 0, maxRotation = 2.0f*(360.0f * 2.0f * 3.14);
	


	float maxSpeed = 10.0f;
	float speedX =  float(0.0f);
	float speedY = float(0.0f);
	float* health = new float(100.0f);
	float* maxHealth = new float(100.0f);

	//The amount of damage this object does. COULD DO: create a defense system with other stats. crits..?
	float strength;

	

	GameObject() {
		textureFile = "Default.png";

		colliderType = Collider::object;
		
		vbo = createVBO();
		vao = createVAO();

		
	}

	~GameObject() {
		delete collisions;
//		delete position;
//		delete scale;
		delete health;
		delete maxHealth;
		
	}
	bool update()  {
		//===================
		//Clamp object speeds
		//===================
		if (speedX > 10 || speedX < -10) {
			float unarySign;
			speedX < 0 ? unarySign = -1 : unarySign = 1;
			speedX = unarySign * 10;
		}
		if (speedY > 10 || speedY < -10) {
			float unarySign;
			speedY < 0 ? unarySign = -1 : unarySign = 1;
			speedY = unarySign * 10;
		}
		//===============
		//update position
		//===============
		position->x += speedX;
		position->y += speedY;


		//======================================
		//Bind the player into the drawing space
		//======================================
		if (colliderType == Collider::player) {
			float unary;
			
			if (position->x > 950 || position->x < -950) {
				position->x > 950 ? unary = 1.0f : unary = -1.0f;
				speedX = 0;
				position->x = unary * 950;
			}

			if (position->y > 950 || position->y < -950) {
				position->y > 950 ? unary = 1.0f : unary = -1.0f;
				speedY = 0;
				position->y = unary * 950;
			}
		}
		
		if (position->x > 1050 || position->x < -1050) {
			delete this;
			return false;
		}
		
		if (position->y > 1050 || position->y < -1050) {
			delete this;
			return false;
		}

		if (*health <= 0) {
			delete this;
			return false;
		}
	}

	
	VBO createVBO() {

		GLfloat* verts = new GLfloat[20];
		for (int i = 0; i < 20; i++) {
			verts[i] = vertices[i];

		}
		VBO spriteVBO(verts, sizeof(float) * 20, GL_DYNAMIC_DRAW);
		delete[] verts;
		return spriteVBO;
	}


	VAO createVAO() {
		VAO vao;
		return vao;
	}

	GLuint* getIndices() {
		GLuint* ret = new GLuint[6];
		for (int i = 0; i < 6; i++) {
			ret[i] = indices[i];
		}
		return ret;
	}

	multimap<GameObject*, ColliderFlag>* getCollisions(GameObject* object) {
		if (collisions->count(object) == 0) {
			collisions->insert(std::pair<GameObject*, ColliderFlag>(object, ColliderFlag::none));
		}
		return collisions;
	}
	//I would like to clean this up, maybe with a script system? Further research needed.
	void static objectCollide(GameObject* object1, GameObject* object2) {
		//==================
		//Disabled collisions
		//==================
		if (object1->colliderType == Collider::friendlyBullet && (object2->colliderType == object1->colliderType)) {
			return;
		}
		
		//=================
		//General collision
		//=================
		if (object2->colliderType != Collider::object ) {

			//======================
			//Bulk collision disable
			//======================
			if ((object1->colliderType == Collider::player && object2->colliderType == Collider::friendlyBullet) || //Handles the player hitting the bullet,
				(object1->colliderType == Collider::friendlyBullet && object2->colliderType == Collider::player)) 	//Handles the bullet hitting the player
			{ return; }

			//=========================
			//Friendly Bullet Collision
			//=========================
			if (object1->colliderType == Collider::friendlyBullet) {
				if (object2->colliderType == Collider::object) {
					object2->damage(5.0f);
					object1->damage(5.0f);
				}
			}

			//===========================
			//An object hitting something
			//===========================
			else if (object1->colliderType == Collider::object ){	
				multimap<GameObject*, ColliderFlag>* otherCollisions = object2->getCollisions(object1);
				multimap<GameObject*, ColliderFlag>::iterator otherObjIt = otherCollisions->find(object1);
				
				multimap<GameObject*, ColliderFlag>* gameObjectCollisions = object1->getCollisions(object2);
				multimap<GameObject*, ColliderFlag>::iterator gameObjectIt = gameObjectCollisions->find(object2);
								
				otherObjIt->second = CollisionEvent::opposite(gameObjectIt->second);


				GameObject::objectCollide(object2, object1);
				//prevents collisions with objects happening more than once 
				multimap<GameObject*, ColliderFlag>* cleanupMap1 = object2->getCollisions(object1);
				multimap<GameObject*, ColliderFlag>* cleanupMap2 = object1->getCollisions(object2);

				multimap<GameObject*, ColliderFlag>::iterator it1 = cleanupMap1->find(object1);
				multimap<GameObject*, ColliderFlag>::iterator it2 = cleanupMap2->find(object2);
				it1->second = ColliderFlag::none;
				it2->second = ColliderFlag::none;

			}



		}
		//=================
		//Hitting an object
		//=================
		else {

		
			//===============================================
			//Friendly Bullet Collision for Collider::objects
			//===============================================
			if (object1->colliderType == Collider::friendlyBullet) {
				if (object2->colliderType == Collider::object) {
					object2->damage(5.0f);
					object1->damage(5.0f);
				}
			}


			if (object2->colliderType == Collider::object) {
				multimap<GameObject*, ColliderFlag>* collisions = object1->getCollisions(object2);
				multimap<GameObject*, ColliderFlag>::iterator it = collisions->find(object2);
				if (it == object1->collisions->end()) { return; }
				//Fill an info struct that that I can send to a clamp function
				CollisionInfo info;
				info.position1.x = object1->position->x;
				info.position1.y = object1->position->y;
				info.position1.z = object1->position->z;
				info.scale1.x = object1->scale->x;
				info.scale1.y = object1->scale->y;
				info.scale1.z = object1->scale->z;
				info.position2.x = object2->position->x;
				info.position2.y = object2->position->y;
				info.position2.z = object2->position->z;
				info.scale2.x = object2->scale->x;
				info.scale2.y = object2->scale->y;
				info.scale2.z = object2->scale->z;
				info.speedX1 = object1->speedX;
				info.speedY1 = object1->speedY;
				info.speedX2 = object2->speedX;
				info.speedY2 = object2->speedY;
				info.colliderType1 = object1->colliderType;
				info.colliderType2 = object2->colliderType;

				//The function clamps this objects position so you cannot go further into a collision
				CollisionInfo clamped = CollisionEvent::clamp(info, it->second);

				if (it->second == ColliderFlag::right || it->second == ColliderFlag::left) {
					object1->position->x = clamped.position1.x;
					object1->speedX = clamped.speedX1;
				}
				else {
					object1->position->y = clamped.position1.y;
					object1->speedY = clamped.speedY1;
				}
			//Get rid of the collision flag because we have moved this object slightly over
				multimap<GameObject*, ColliderFlag>* collisionsList = object1->getCollisions(object2);
				multimap<GameObject*, ColliderFlag>::iterator collisionFlag = collisionsList->find(object2);
				collisionFlag->second = ColliderFlag::none;

			}
		}
	}

	void damage(float amount) {
		*health -= amount;
		std::cout << *health << endl;
	}

	void rotate(float amount) {
		
		rotation += amount;
		
		if (rotation >= maxRotation) {
  			float difference = rotation - maxRotation;
			rotation = difference;
		}
	}



};


#endif