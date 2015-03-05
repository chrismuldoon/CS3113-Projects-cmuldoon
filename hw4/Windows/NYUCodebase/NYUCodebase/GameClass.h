#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "defines.h"
#include "common.h"
#include "Entity.h"

using namespace std;

class GameClass {
public:
	GameClass();
	~GameClass();
	void Init();
	bool UpdateAndRender();
	void Render();
	void Update(float elapsed);
	void FixedUpdate();
	void playerInput(Entity* player);

	void buildLevel();

private:
	bool done;
	float lastFrameTicks;
	float timeLeftOver;
	SDL_Window* displayWindow;
	SDL_Event event;
	GLuint textImg;

	//game objects
	Entity* player;
	//Entity* box;
	vector<Entity*> staticObjects;

};