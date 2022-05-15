#include <stb/stb_image.h>
#include "Texture.h"

//I need to do the texture management system. The flow will be 
/*
* if (renderer.textureNotBound) { //bind texture to empty slot
* else { 
* Glenum slot = renderer.getEmptySlot(fileName);
* imageLoad(fileName, //rest of file stuff//, slot);
* 
* 
*/

Texture::Texture(){
	fileName = "Default.png";
}

Texture::Texture(std::string fileName) {
	this->fileName = fileName;
}




void Texture::deleteTexture() {
	glDeleteTextures(1, &ID);
}

