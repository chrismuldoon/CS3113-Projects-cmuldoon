#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#define UPPERBOUND 1.0
#define LOWERBOUND -1.0
#define LEFTBOUND -1.0
#define RIGHTBOUND 1.0

class Enemy
{
public:
	Enemy(float x, float y, GLuint ss);
	void render();
	//void update();
	void shoot();
	void move(int dir, bool downMove);
	bool kill(float x, float y); //try to kill enemy with bullet at x,y
	bool bulletPos(float &xPosition, float &yPosition);
	void update(float elapsed);
	void reset(float x, float y);
	void DrawSprite2(float u, float v, float width, float height);

private:
	float xPos;
	float yPos;
	float xRadius;
	float yRadius;
	bool enemyAlive;
	
	bool bulletAlive;
	float xBulletPos;
	float yBulletPos;
	GLuint spriteSheet;

};

void DrawRectang(float x, float y, float r1, float r2);