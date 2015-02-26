#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#define BULLETSPEED 2.0
#define PLAYERSPEED 1.1
#define UPPERBOUND 1.0
#define LOWERBOUND -1.0
#define LEFTBOUND -1.33
#define RIGHTBOUND 1.33

class Player
{
public:
	Player(GLuint ss);
	void render();
	void update(float elapsed, int moveDir, bool shot);
	bool bulletPos(float &xPosition, float &yPosition);
	bool killPlayer(float x, float y);
	void killBullet();
	void reset();

	void Player::DrawSprite2(float u, float v, float width, float height);
	//bool isAlive();

	

private:
	float xPos;  //x axsis
	float yPos;
	float xRadius;
	float yRadius;
	bool playerAlive;

	bool bulletAlive;
	float xBulletPos;
	float yBulletPos;
	GLuint spriteSheet;
	//float yPos;


};

void DrawRectangle(float x, float y, float r1, float r2);