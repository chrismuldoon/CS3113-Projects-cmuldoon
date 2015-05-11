#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "matrix.h"

class Entity {

public:
	Entity();

	Entity(const float &x,
		const float &y,
		const int &i,
		const int &c,
		const float &r,
		const float &s,
		const float &rot,
		const float &vlctyX,
		const float &vlctyY,
		GLuint t);

	void Draw();



private:
	// data members
	float x;
	float y;
	float u;
	float v;
	float w;
	float h;
	float s;
	float rot;
	float spd;
	float vlctyX;
	float vlctyY;
	Matrix mtrx;
	Vector vctr;
	GLuint t;

};
