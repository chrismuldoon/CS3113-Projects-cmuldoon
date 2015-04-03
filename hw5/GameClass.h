#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "defines.h"
#include "common.h"
#include "entity.h"

#include <SDL_mixer.h>

//define for level


using namespace std;

class GameClass {
public:
	GameClass();
	~GameClass();
	void Init();
	bool UpdateAndRender();
	void Render();
	void renderLevel();
	void Update(float elapsed);
	void FixedUpdate();



private:
	bool done;
	float lastFrameTicks;
	float timeLeftOver;
	SDL_Window* displayWindow;
	SDL_Event event;
	GLuint textImg;
	GLuint spriteImg;
	unsigned char levelData[LEVEL_HEIGHT][LEVEL_WIDTH];
	Entity* player;
	//Entity* box;
	vector<Entity*> staticObjects;

	Mix_Music *music;
	Mix_Chunk *someSound;
};