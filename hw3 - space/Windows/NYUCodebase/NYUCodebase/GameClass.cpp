#pragma once

#include "GameClass.h"

enum GameState { STATE_MENU, STATE_GAME, STATE_GAMEOVER };

GameClass::GameClass() {
	Init();
	done = false;
	lastFrameTicks = 0.0f;
	lastShotTime = -100.0f;
	state = STATE_MENU;
}
void GameClass::Init() {
	
	//video stuff
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	//move later

	p1 = new Player();
	testy = new Enemy(0.0, 0.0);

	//place enemies in a grid
	for (int i = 0; i < 4; i++){ //i = number of rows
		float y = 0.8 - i*(.2);
		for (int j = 0; j < 8; j++){
			float x = -0.6 + j*(.2);
			invaders.push_back(new Enemy(x,y));
		}
	}//end for loops
}

GameClass::~GameClass() {
	delete p1;
	delete testy;
	for (size_t i = 0; i < invaders.size(); i++){
		delete invaders[i];
	}
	SDL_Quit();
}

bool GameClass::UpdateAndRender() {  //aka "main"
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

	switch (state)
	{
	case STATE_MENU:
		updateMenu();
		renderMenu();
		break;
	case STATE_GAME:
		Update(elapsed);
		Render();
		break;
	case STATE_GAMEOVER:
		updateGO();
		renderGO();
		break;
	}

	/*if (state == STATE_MENU){ updateMenu(); }
	else if (state == STATE_GAME){ Update(elapsed); }
	else{
		updateGO();
	
	
	}
*/

	//updateMenu();
	//Update(elapsed);
	//renderMenu();
	//Render();


	return done;
}

void GameClass::updateMenu(){

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
	}

	if (getInput(SDL_SCANCODE_RETURN))
		state = STATE_GAME;
}

void GameClass::updateGO(){

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
	}


	if (getInput(SDL_SCANCODE_SPACE))
		state = STATE_MENU;
}

void GameClass::renderMenu(){
	// render stuff
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	DrawRectanglee(0.0, 0.0, .50, .190);

	SDL_GL_SwapWindow(displayWindow);

}

void GameClass::renderGO(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	DrawRectanglee(0.0, 0.0, 1.5, 2.0);
	SDL_GL_SwapWindow(displayWindow);
}



void GameClass::Render() {
	// render stuff
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
	glClear(GL_COLOR_BUFFER_BIT);
	
	if (p1) p1->render();
	if (testy) testy->render();
	for (size_t i = 0; i < invaders.size(); i++){
		//check if alive
		if (invaders[i]){
			//check if alive
			invaders[i]->render();
		
		}
	}

	SDL_GL_SwapWindow(displayWindow);

	
}
void GameClass::Update(float elapsed) {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
	}
	int moveDirection = 0;
	bool shoot = false;
	getInput(elapsed, moveDirection, shoot);

	if (p1) p1->update(elapsed, moveDirection, shoot);


	//player bullet stuff
	float xPlayerBullet = 0.0;
	float yPlayerBullet = 0.0;
	bool alivePlayerBullet = false;
	if (p1) alivePlayerBullet = p1->bulletPos(xPlayerBullet, yPlayerBullet);

	bool bulletHit = false;
	for (size_t i = 0; i < invaders.size(); i++){
		if (!bulletHit && alivePlayerBullet && invaders[i])  bulletHit = invaders[i]->kill(xPlayerBullet, yPlayerBullet);
	}
	if (bulletHit) p1->killBullet();

	//enemy bullet stuff

	bulletHit = false;
	for (size_t i = 0; i < invaders.size(); i++){
		if (invaders[i]) {
			alivePlayerBullet = invaders[i]->bulletPos(xPlayerBullet, yPlayerBullet);
			invaders[i]->update(elapsed); //update
		}
		if (p1) {
			bulletHit = p1->killPlayer(xPlayerBullet, yPlayerBullet);
			if (bulletHit) state = STATE_GAMEOVER;
		}
	}
	//if bullet hit game over
	
	//make enemies shoot

	//if (elapsed > 0.1 + lastShotTime){
		lastShotTime = elapsed;
		for (size_t i = 0; i < invaders.size(); i++)
			if (invaders[i]) invaders[i]->shoot();
	
	//}
	

	//check for gameover

}

bool GameClass::getInput(float elapsed, int &movDir, bool &shot){
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_LEFT])
		movDir = -1;
	else if (keys[SDL_SCANCODE_RIGHT])
		movDir = 1;
	else movDir = 0;
	

	if (keys[SDL_SCANCODE_SPACE])
		shot = true;
	else shot = false;

	if (keys[SDL_SCANCODE_RETURN])
		return true;
	else return false;
}

bool GameClass::getInput(int scancode){
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[scancode])
		return true;
	else return false;

}


void DrawRectanglee(float x, float y, float r1, float r2){
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