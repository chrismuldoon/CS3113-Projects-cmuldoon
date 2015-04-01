#pragma once
#include "Entity.h"
#include "common.h"


#define YGRAVITY 2.5f
#define X_FRIC 0.7f

#define JUMP_SPEED 1.4f
#define MAX_SPEED 0.8f

#define INPUT_ACCEL 2.0f
#define JUMP_ACCEL 0.9f

Entity::Entity(float x, float y, float xr, float yr, float colorR, float colorG, float colorB, bool statc, bool destruct, bool coin)
	:initXpos(x), initYpos(y), xRad(xr), yRad(yr), rIn(colorR), gIn(colorG), bIn(colorB), isStatic(statc), destructable(destruct), isCoin(coin)
{
	collidedBottom = false;
	collidedLeft = false;
	collidedRight = false;
	isVisable = true;
	score = 0;
	r = rIn;
	g = gIn;
	b = bIn;

	//destructale
	eventTime = -50.0f;
	eventSequence = false;

	if (isStatic){
		xPos = initXpos;
		yPos = initYpos;
	}
	else {
		ResetDynamic();
		yGrav = -YGRAVITY;
		xFric = X_FRIC;
	}
}

void Entity::ResetDynamic(){
	static float dir = 1.0f;
	xPos = initXpos;
	yPos = initYpos;
	xAccel = 0.0f;
	yAccel = 0.0f;
	yVel = 0.0f;
	if (isCoin){
		xVel = 1.5f*dir;
		dir *= -1.0;
	}	
	else
		xVel = 0.0f;
		
	
}

void Entity::destroy(bool start){
	float currentTime = SDL_GetTicks() / 1000.0f;  

	//start the sequence
	if (start && !eventSequence){
		eventTime = currentTime;
		eventSequence = true;
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		//return;
	}

	//reset
	else if (eventSequence && currentTime > 6.0f + eventTime){
		isVisable = true;
		eventSequence = false;
		r = rIn;
		g = gIn;
		b = bIn;
	}

	//if timer reaches, then clear platform
	else if (eventSequence && currentTime > 3.0f + eventTime){
		isVisable = false;	
		b = 0.5f;
	}
	

	

}

void Entity::Render(){
	if (isVisable)
		DrawRectangle(xPos, yPos, xRad, yRad);// , r, g, b);
}


void Entity::jump(){
	if (collidedBottom) {
		yVel = JUMP_SPEED;
		collidedBottom = false;
	}
	else if (collidedLeft){
		yVel = 0.86f * JUMP_SPEED;
		xVel = 0.5f * JUMP_SPEED;
		collidedLeft = false;
	}
	else if (collidedRight){
		yVel = 0.86f * JUMP_SPEED;
		xVel = 0.5f * -JUMP_SPEED;
		collidedRight = false;
	}


}



void Entity::FixedUpdate(vector<Entity*> &staticObjects, unsigned char level[][LEVEL_WIDTH], Entity* player){
	//static stuff here -> nothing?
	if (isStatic) return;

	//dynamic stuff 
	//acceleration, gravity, friction etc.

	if (!collidedBottom) xAccel *= 0.2f; 

	//if the max speed is in the range, apply accel
	if (-MAX_SPEED < xVel && xVel < MAX_SPEED) {
			xVel += xAccel *  FIXED_TIMESTEP;
			if (xVel > MAX_SPEED) xVel = MAX_SPEED;
			if (xVel < -MAX_SPEED) xVel = -MAX_SPEED;
	}
	//or if a & v signs dont match, apply accel
	else if ((xVel < 0 && xAccel > 0)||(xVel > 0 && xAccel < 0)) 
		xVel += xAccel *  FIXED_TIMESTEP;

	

	//if player is going up up apply accel
	if (yVel >0)
		yVel += yAccel *  FIXED_TIMESTEP;

	yVel += yGrav * FIXED_TIMESTEP;
	


	//friction alot less if in air
	float adjusedFric = xFric;
	if (!collidedBottom) adjusedFric *= 0.2f;


	//xVel = lerp(xVel, 0.0f, FIXED_TIMESTEP * xFric);

	//friction
	if (xVel > 0){ //moving right
		xVel -= adjusedFric * FIXED_TIMESTEP;
		if (xVel < 0) xVel = 0;
	}
	else if (xVel < 0){ //moving left
		xVel += adjusedFric * FIXED_TIMESTEP;
		if (xVel > 0) xVel = 0;
	}


	//reset once per frame
	collidedBottom = false;
	collidedLeft = false;
	collidedRight = false;
	printf("\nfr: ");

	//move in x direction
	//check for collision with an object
	//if collision, adjust position the proper direction
	//repeat for all object
	//then check x direcion

	vector<Entity*>::iterator staticObj;
	//yPos and collision/y-penetration
	yPos += yVel * FIXED_TIMESTEP;

	//use iterators???? yes!

	for (staticObj = staticObjects.begin();
		staticObj != staticObjects.end(); staticObj++)
	{
		//if (!(*staticObj)->isVisable) break;
		if (isVisable&& (*staticObj)->isVisable && collidesWith(*staticObj)){
			float pen = fabs(fabs(yPos - (*staticObj)->yPos) - yRad - (*staticObj)->yRad);
			if (yPos < (*staticObj)->yPos) {	//if entity is above obj
				yPos -= pen + 0.0001f;
				yVel = 0;
				printf("down");
			}
			else{		//if obj was moving down
				yPos += pen + 0.0000001f; // +0.001;
				if (isCoin) yVel *= -0.75; //coins bounce
				else yVel = 0;
				printf("\\/ ");
				collidedBottom = true;
				if ((*staticObj)->destructable)
					(*staticObj)->destroy(true);
				

			}
		}//end if

	}//end for



	//xPos and collions
	xPos += xVel * FIXED_TIMESTEP;


	for (staticObj = staticObjects.begin();
		staticObj != staticObjects.end(); staticObj++)
	{
	  //if (!(*staticObj)->isVisable) 
		if ((*staticObj)->isVisable && collidesWith(*staticObj)) {
			float pen = fabs(fabs(xPos - (*staticObj)->xPos) - xRad - (*staticObj)->xRad);
			if (xPos < (*staticObj)->xPos) {	//if obj was moving right
				xPos -= pen + 0.0000001f;
				if (isCoin) xVel *= -1.0; //coins bounce
				else xVel = 0;
				collidedRight = true;
				printf("-->");
			}
			else{		//if obj was moving left
				xPos += pen + 0.0000001f;
				if (isCoin) xVel *= -1.0; //coins bounce
				else xVel = 0;
				collidedLeft = true;
				printf("<--");
			}
		}//end if

		//move later to dynamic looop
		if ((*staticObj)->destructable)
			(*staticObj)->destroy(false);

	}//end for
	

	//if ur a coin, check collision with player
	if (isCoin &&isVisable && player)
		if (collidesWith(player)){
			player->score++;
			ResetDynamic();
		}

	//if fall below screen
	if (yPos < -1.5f){
		ResetDynamic();
		score = 0;
	}

	//end collision stuf

	//move later
	
	
}


void Entity::playerInput(){
	
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	//extra lift if holding space
	if (keys[SDL_SCANCODE_SPACE])
		yAccel = JUMP_ACCEL;
	else yAccel = 0.0f;

	//x-movement
	if (keys[SDL_SCANCODE_LEFT]) {
		// go left!
		xAccel = -INPUT_ACCEL;
	}
	else if (keys[SDL_SCANCODE_RIGHT]) {
		// go right!
		xAccel = INPUT_ACCEL;
	}
	else {
		xAccel = 0;
	}


}

bool Entity::collidesWith(Entity *entity){
	if ((xPos + xRad ) > (entity->xPos - entity->xRad) &&
		(xPos - xRad ) < (entity->xPos + entity->xRad) &&
		(yPos + yRad ) > (entity->yPos - entity->yRad) &&
		(yPos - yRad ) < (entity->yPos + entity->yRad))
	{	return true; }
	return false;
}

float lerp(float v0, float v1, float t) {
	return (1.0 - t)*v0 + t*v1;
}

void worldToTileCoordinates(float worldX, float worldY, int *gridX, int *gridY) {
	*gridX = (int)((worldX + (WORLD_OFFSET_X)) / TILE_SIZE);
	*gridY = (int)((-worldY + (WORLD_OFFSET_Y)) / TILE_SIZE);
}