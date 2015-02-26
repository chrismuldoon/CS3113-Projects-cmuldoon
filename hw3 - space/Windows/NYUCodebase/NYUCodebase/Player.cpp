#include "Player.h"

Player::Player(GLuint ss){
	xRadius = 0.08;
	yRadius = 0.05;
	xPos = 0.0;
	yPos = yRadius - 1.0;
	bulletAlive = false;
	playerAlive = true;
	spriteSheet = ss;
	

}void Player::reset(){
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
		DrawSprite2(0 / 256.0, 115.0 / 256.0, 104.0 / 256.0, 64.0 / 256.0);
		//DrawRectangle(xPos, yPos, xRadius, yRadius);
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







void Player::DrawSprite2(float u, float v, float width, float height) {
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

//void DrawSprite(float scale) {
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	GLfloat quad[] = { -width * scale, height * scale, -width * scale, -height * scale,
//		width * scale, -height * scale, width * scale, height * scale };
//	GLfloat quadUVs[] = { u, v, u, v + height, u + width, v + height, u + width, v };
//	// draw arrays
//}