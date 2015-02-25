#include "enemy.h"
#define BULLETSPEED 0.30f


Enemy::Enemy(float x, float y){
	xPos = x;
	yPos = y;
	xRadius = 0.05;
	yRadius = 0.05;
	enemyAlive = true;

	bulletAlive = false;
	xBulletPos = 0.0;
	yBulletPos = 0.0;


}

void Enemy::render(){
	if (enemyAlive)
		DrawRectang(xPos, yPos, xRadius, yRadius);
	if (bulletAlive)
		DrawRectang(xBulletPos, yBulletPos, .01, .015);
	}

bool Enemy::kill(float x, float y){ //try to kill enemy with bullet at x,y
	if (enemyAlive == false) return false;

	if (x > xPos - xRadius &&
		x < xPos + xRadius &&
		y > yPos - yRadius &&
		y < yPos + yRadius) 
	{
		enemyAlive = false;
		return true;
	}
	return false;
}

void Enemy::shoot(){
	if (!enemyAlive) return;
	if (bulletAlive) return;
	bulletAlive = true;
	xBulletPos = xPos;
	yBulletPos = yPos - yRadius;
}

bool Enemy::bulletPos(float &xPosition, float &yPosition){
	xPosition = xBulletPos;
	yPosition = yBulletPos;
	return bulletAlive;
}

void Enemy::update(float elapsed){
	if (bulletAlive){
		yBulletPos -= elapsed * BULLETSPEED;
		if (yBulletPos < LOWERBOUND) bulletAlive = false;
	}


}

void DrawRectang(float x, float y, float r1, float r2){
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