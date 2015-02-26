#include "enemy.h"
#define BULLETSPEED 0.30f


Enemy::Enemy(float x, float y, GLuint ss){
	xPos = x;
	yPos = y;
	xRadius = 0.05;
	yRadius = 0.05;
	enemyAlive = true;

	bulletAlive = false;
	xBulletPos = 0.0;
	yBulletPos = 0.0;

	spriteSheet = ss;


}

void Enemy::reset(float x, float y){
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
		DrawSprite2(0, 0, 150.0 / 256.0, 115.0 / 256.0);
		//DrawRectang(xPos, yPos, xRadius, yRadius);
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



void Enemy::DrawSprite2(float u, float v, float width, float height) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spriteSheet);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat quad[] = { (xPos - xRadius), (yPos + yRadius),
		(xPos - xRadius), (yPos - yRadius),
		(xPos + xRadius), (yPos - yRadius),
		(xPos + xRadius), (yPos + yRadius) };


	GLfloat quadUVs[] = { u, v, u, v + height, u + width, v + height, u + width, v };

	//GLfloat quad[] = { -0.4f*xOverY, 0.4f * 1, -0.4f*xOverY, -0.4f * 1, 0.4f*xOverY, -0.4f * 1, 0.4f*xOverY, 0.4f * 1 };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);
	//GLfloat quadUVs[] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };
	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);

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