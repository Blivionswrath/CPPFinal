#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <string>

#include "Sprite.h"

class Background : GameObject{
public:
	Sprite sprite;
	Background();
	Background(int left, int right, int bottom, int top, std::string fileName, int tesselations);
	
	void changeBackground(std::string fileName);
	void changeScale(int left, int right, int bottom, int top);
	VBO createVBO(int left, int right, int bottom, int top, int tesselations);
};
#endif