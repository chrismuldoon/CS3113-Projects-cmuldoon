#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <random>
#include <string>


#include "Player.h"
#include "enemy.h"


using namespace std;

class GameClass {
public:
	GameClass();
	~GameClass();
	void Init();
	bool UpdateAndRender();
	void Render();
	void Update(float elapsed); 
	bool getInput(float elapsed, int &movDir, bool &shot);
	void gameStart();
	void gameEnd();
	bool getInput(int scancode);

	void updateMenu();
	void updateGO();
	void renderMenu();
	void renderGO();
	void initGameState();
	void resetGame();


	
private:
	bool done;
	float lastFrameTicks;
	float lastMoveTime;
	int moveCount;
	float lastShotTime;
	SDL_Window* displayWindow;
	SDL_Event event;
	Player* p1;
	vector<Enemy*> invaders;
	int state;
	int score;
	GLuint textImg;
	GLuint spriteSheet;

	int moveDir;
	
	bool winner;
	size_t randIndex;
};

void DrawRectanglee(float x, float y, float r1, float r2);
GLuint LoadTexture(const char *image_path);
void DrawText(int fontTexture, string text, float size, float spacing, float x, float y, float r, float g, float b, float a);