#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

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
	
private:
	bool done;
	float lastFrameTicks;
	float lastShotTime;
	SDL_Window* displayWindow;
	SDL_Event event;
	Player* p1;
	vector<Enemy*> invaders;
	Enemy* testy;
	int state;
};

void DrawRectanglee(float x, float y, float r1, float r2);