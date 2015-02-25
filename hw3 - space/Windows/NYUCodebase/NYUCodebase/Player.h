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
	Player();
	void render();
	void update(float elapsed, int moveDir, bool shot);
	bool bulletPos(float &xPosition, float &yPosition);
	bool killPlayer(float x, float y);
	void killBullet();

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
	//float yPos;


};

void DrawRectangle(float x, float y, float r1, float r2);