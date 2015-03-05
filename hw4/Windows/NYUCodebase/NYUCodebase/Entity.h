#pragma once

#include "defines.h"
#include <vector>

using namespace std;

class Entity {
public:
	Entity(float x, float y, float xr, float yr, bool statc = false);
	void Update(float elapsed);
	void Render();
	bool collidesWith(Entity *entity);
	void FixedUpdate(vector<Entity*> &staticObjects);
	void jump();

	float xPos;
	float yPos;
	float xRad;
	float yRad;
	float xVel;
	float yVel;

	float yGrav;
	float xAccel;
	float yAccel;
	float xFric;
	//float yFric;
	

	bool isStatic;
	//bool enableCollisions;

	//bool collidedTop;
	bool collidedBottom;
	//bool collidedLeft;
	//bool collidedRight;
};