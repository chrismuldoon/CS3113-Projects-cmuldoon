#include "Player.h"

Player::Player(){
	xRadius = 0.08;
	yRadius = 0.05;
	xPos = 0.0;
	yPos = yRadius - 1.0;
	bulletAlive = false;
	playerAlive = true;
	

}

bool Player::bulletPos(float &xPosition, float &yPosition){
	xPosition = xBulletPos;
	yPosition = yBulletPos;
	return bulletAlive;
}

void Player::killBullet() { bulletAlive = false; }

void Player::render(){ 
	if (playerAlive)
		DrawRectangle(xPos, yPos, xRadius, yRadius);
	if (bulletAlive)
		DrawRectangle(xBulletPos, yBulletPos, .01, .01);
}

void Player::update(float elapsed, int moveDir, bool shot){
	if (moveDir > 0)		xPos += elapsed *PLAYERSPEED;
	else if (moveDir < 0)	xPos += elapsed *-PLAYERSPEED;

	if (xPos >(RIGHTBOUND - xRadius)){ xPos = RIGHTBOUND - xRadius; }
	else if (xPos <(LEFTBOUND + xRadius)) xPos = LEFTBOUND + xRadius;

	yBulletPos += BULLETSPEED * elapsed;
	if (bulletAlive && (yBulletPos > UPPERBOUND) ) bulletAlive = false;

	if (!bulletAlive && shot){ //if bullet is dead and new one is shot
		bulletAlive = true;
		xBulletPos = xPos;
		yBulletPos = yPos + yRadius;	
	}

}

bool Player::killPlayer(float x, float y){ //try to kill player with bullet at x,y
	if (playerAlive == false) return false;

	if (x > xPos - xRadius &&
		x < xPos + xRadius &&
		y > yPos - yRadius &&
		y < yPos + yRadius)
	{
		playerAlive = false;
		return true;
	}
	return false;
}




void DrawRectangle(float x, float y, float r1, float r2){
	GLfloat quad[] = { (x - r1), (y + r2),
		(x - r1), (y - r2),
		(x + r1), (y - r2),
		(x + r1), (y + r2) };

	glLoadIdentity();
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	//glEnd();

}