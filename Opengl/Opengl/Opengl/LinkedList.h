#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "GameObject.h"

struct listNode {
	GameObject* object;
	listNode* next;
	listNode* previous;
};

class LinkedList {
public:
	listNode* head;


	LinkedList() {
		head = NULL;

	}

	//This method can be replaced with a binary search
	
	GameObject* traverse(int index) {
		listNode* p = head;
		listNode* ret;

		for (int i = 0; i < index; i++) {

			p = p->next;

		}
		ret = p;
		return ret->object;
	}

	void insert(GameObject* object) {
		std::string textureName = object->textureFile;

		if (head == NULL) {
			listNode* newNode = new listNode; 
			newNode->next = NULL;
			newNode->object = object;
			newNode->previous = NULL;
			head = newNode;
			return;
		}

		if (textureName < head->object->textureFile) {
			listNode* newNode = new listNode;
			newNode->next = head;
			newNode->previous = NULL;
			head = newNode;
			return;
		}
		
		listNode* currentNode = head;
		listNode* nextNode = head->next;
		if (nextNode == NULL) {
			listNode* newNode = new listNode;
			newNode->object = object;
			newNode->previous = currentNode;
			currentNode->next = newNode;
			newNode->next = NULL;
			nextNode = currentNode->next;
		}
		if (textureName >= currentNode->object->textureFile && textureName < nextNode->object->textureFile) {
			listNode* newNode = new listNode;
			newNode->object = object;
			newNode->previous = currentNode;
			currentNode->next = newNode;

			newNode->next = nextNode;
			nextNode->previous = newNode;
		}

	}
	void remove(GameObject* object) {
		listNode* p = head;
		while (p) {

			if (object == p->object) {
				listNode* previous = p->previous;
				listNode* next = p->next;
				if (p->next == NULL) {
					next = NULL;
				}
				if (p->previous != NULL) {
					previous->next = next;
				}
				else if (p == head) {
					head = p->next;
					head->previous = NULL;
				}
				
				if (next != NULL) {
					next->previous = previous;
				}
				return;
				delete p;
			}

			p = p->next;
		}
	}

	GameObject* operator[](int n) {
		return traverse(n);
	}

};

#endif
