#include "Background.h"

Background::Background() {
	VBO vbo = createVBO(-100, 100, -100, 100, 5);
	textureFile = "Desert.png";
	sprite.vbo = vbo;
	sprite.vao.linkAttrib(sprite.vbo, 0, 3, sizeof(float) * 5, 0);
	sprite.vao.linkAttrib(sprite.vbo, 1, 2, sizeof(float) * 5, sizeof(float) * 3);
	sprite.texture.fileName = "Desert.png";
}
Background::Background(int left, int right, int bottom, int top, std::string fileName, int tesselations) {
	VBO vbo = createVBO(left, right, bottom, top, tesselations);
	textureFile = fileName;
	sprite.vbo = vbo;
	sprite.vao.linkAttrib(sprite.vbo, 0, 3, sizeof(float) * 5, 0);
	sprite.vao.linkAttrib(sprite.vbo, 1, 2, sizeof(float) * 5, sizeof(float) * 3);
	sprite.texture.fileName = fileName;
}

VBO Background::createVBO(int left, int right, int bottom, int top, int tesselations) {
	GLfloat* verts = new GLfloat[20];
	//Top right
	verts[0] = right;
	verts[1] = top;
	verts[2] = -1.0;
	verts[3] = tesselations;
	verts[4] = tesselations;
	//Top left
	verts[5] = left;
	verts[6] = top;
	verts[7] = -1.0;
	verts[8] = 0.0;
	verts[9] = tesselations;
	
	//Bottom left
	verts[10] = left;
	verts[11] = bottom;
	verts[12] = -1.0f;
	verts[13] = 0.0;
	verts[14] = 0.0;
	//Bottom right
	verts[15] = right;
	verts[16] = bottom;
	verts[17] = -1.0;
	verts[18] = tesselations;
	verts[19] = 0.0;

	VBO vbo(verts, sizeof(float) * 20, GL_STATIC_DRAW);
	
	return vbo;
}

void Background::changeBackground(std::string fileName) {

}