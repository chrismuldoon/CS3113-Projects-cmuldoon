#pragma once
#include "Entity.h"
#include "common.h"

Entity::Entity(float x, float y, float xr, float yr, bool statc)
	:xPos(x), yPos(y), xRad(xr), yRad(yr), isStatic(statc)
{
	collidedBottom = false;



	if (isStatic){
	
	}
	else {
		xVel = 0.20f;
		yVel = 0.0f;
		xAccel = 0.0f;
		yAccel = 0.0f;
		yGrav = -.90f;
		xFric = 0.59f;
	}
}

void Entity::Render(){
	DrawRectangle(xPos, yPos, xRad, yRad);
}

void Entity::jump(){
	if (collidedBottom) {
		yVel = 1.0f;
		collidedBottom = false;
	}

}

void Entity::FixedUpdate(vector<Entity*> &staticObjects){
	//static stuff here -> nothing?
	if (isStatic) return;

	//dynamic stuff
	
	//acceleration, gravity, friction etc.
	if (fabs(xVel) < .50f){ //only of the max speed is under, apply accel
		if (collidedBottom)
			xVel += xAccel *  FIXED_TIMESTEP;
		else
			xVel += xAccel * 0.4 *  FIXED_TIMESTEP;
		if (xVel > .50f) xVel = 0.5f;
		if (xVel < -.50f) xVel = -0.5f;
	}


	yVel += yAccel *  FIXED_TIMESTEP;
	yVel += yGrav * FIXED_TIMESTEP;
	

	//friction
	if (collidedBottom && xVel > 0){ //moving right
		xVel -= xFric * FIXED_TIMESTEP;
		if (xVel < 0) xVel = 0;
	}
	else if (collidedBottom && xVel < 0){ //moving left
		xVel += xFric * FIXED_TIMESTEP;
		if (xVel > 0) xVel = 0;
	}


	//reset once per frame
	collidedBottom = false;
	printf("\nfr: ");



	vector<Entity*>::iterator staticObj;
	//yPos and collision/y-penetration
	yPos += yVel * FIXED_TIMESTEP;

	//use iterators????
	//for ()

	for (staticObj = staticObjects.begin();
		staticObj != staticObjects.end(); staticObj++)
	{
		if (collidesWith(*staticObj)){
			float pen = fabs(fabs(yPos - (*staticObj)->yPos) - yRad - (*staticObj)->yRad);
			if (yPos < (*staticObj)->yPos) {	//if entity is above obj
				yPos -= pen + 0.0001f;
				yVel = 0;
				printf("down");
			}
			else{		//if obj was moving down
				yPos += pen + 0.0000001f; // +0.001;
				yVel = 0;
				printf("up ");
				collidedBottom = true;

			}
		}//end if

	}//end for



	//xPos and collions
	xPos += xVel * FIXED_TIMESTEP;


	for (staticObj = staticObjects.begin();
		staticObj != staticObjects.end(); staticObj++)
	{
		if (collidesWith(*staticObj)){
			float pen = fabs(fabs(xPos - (*staticObj)->xPos) - xRad - (*staticObj)->xRad);
			if (xPos < (*staticObj)->xPos) {	//if obj was moving right
				xPos -= pen + 0.0001f;
				xVel = 0;
				printf("left ");
			}
			else{		//if obj was moving left
				xPos += pen + 0.0001f;
				xVel = 0;
				printf("right ");
			}
		}//end if
		
	}//end for

	//end collision stuf


	
}

bool Entity::collidesWith(Entity *entity){
	if ((xPos + xRad ) > (entity->xPos - entity->xRad) &&
		(xPos - xRad ) < (entity->xPos + entity->xRad) &&
		(yPos + yRad ) > (entity->yPos - entity->yRad) &&
		(yPos - yRad ) < (entity->yPos + entity->yRad))
	{	return true; }
	return false;
}