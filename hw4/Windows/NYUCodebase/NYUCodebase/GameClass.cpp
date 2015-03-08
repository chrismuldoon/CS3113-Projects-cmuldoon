#pragma once

#include "GameClass.h"




GameClass::GameClass() {
	Init();
	done = false;
	lastFrameTicks = 0.0f;
	timeLeftOver = 0.0f;

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

	//other stuff
	textImg = LoadTexture("font1.png");
	player = new Entity(0.3f, 0.3f, 0.07f, 0.09f);
	buildLevel();
}

void GameClass::buildLevel(){
								//	  (  x  ,     y , xRad , yRad,  r,   g,   b,    static?, destructable?, coin?)
	//staticObjects.push_back(new Entity(0.30f, -0.880f, 01.3f, 0.1f, 0.0f, 1.0f, 0.0f, true));
	staticObjects.push_back(new Entity(1.250f, 0.0f, 0.05f, 0.950f, 0.0f, 1.0f, 1.0f, true));
	staticObjects.push_back(new Entity(-1.250f, 0.0f, 0.05f, 0.950f, 0.0f, 1.0f, 1.0f, true));
	staticObjects.push_back(new Entity(0.850f, 0.05f, 0.05f, 0.60f, 0.0f, 1.0f, 1.0f, true));
	
	//boxes that disapear
	staticObjects.push_back(new Entity(-0.310f, -0.3520f, 0.1f, 0.1f, 0.7f, 0.7f, 0.9f, true, true));
	staticObjects.push_back(new Entity(0.710f, -0.3520f, 0.1f,  0.1f, 0.7f, 0.7f, 0.9f, true, true));
	staticObjects.push_back(new Entity(0.310f, 0.1520f, 0.1f, 0.1f,   0.7f, 0.7f, 0.9f, true, true));

	staticObjects.push_back(new Entity(-0.80f, 0.5520f, 0.1f, 0.1f, 0.7f, 0.7f, 0.9f, true, true));
	staticObjects.push_back(new Entity(0.310f, -0.880f, 0.3f, 0.1f, 0.7f, 0.7f, 0.9f, true, true));
	staticObjects.push_back(new Entity(-0.70f, 0.1520f, 0.1f, 0.1f, 0.7f, 0.7f, 0.9f, true, true));



	coins.push_back(        new Entity(1.010f, 0.8520f, 0.05f, 0.05f, 1.0f, 0.90f, 0.0f, false, false, true));
	coins.push_back(        new Entity(0.010f, 0.9520f, 0.05f, 0.05f, 1.0f, 0.90f, 0.0f, false, false, true));


}
GameClass::~GameClass() {
	delete player;
	SDL_Quit();
}
void GameClass::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// render stuff

	

	player->Render();

	for (size_t i = 0; i < staticObjects.size(); i++){
		staticObjects[i]->Render();
	}

	for (size_t i = 0; i < coins.size(); i++){
		coins[i]->Render();
	}

	//DrawText(textImg, "Hellkk", 0.2f, -0.1f, -0.9f, 0.5f, 1.0, 1.0, 1.0, 1.0);
	DrawText(textImg, "Score:", 0.10, -0.06, 0.71, 0.9, 1.0, 1.0, 1.0, 1.0);
	DrawText(textImg, std::to_string(player->score * 10), 0.10, -0.06, 1.05, 0.9, 1.0, 1.0, 1.0, 1.0);



	SDL_GL_SwapWindow(displayWindow);
	
}
void GameClass::Update(float elapsed) {
	// player inputs
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
				// DO AN ACTION WHEN SPACE IS PRESSED!
				printf("%i", player->collidedBottom);
				player->jump();
			}
			//other keys...

		}
	}
}
bool GameClass::UpdateAndRender() {
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;


	float fixedElapsed = elapsed + timeLeftOver;
	if (fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS) {
		fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
	}
	while (fixedElapsed >= FIXED_TIMESTEP) {
		fixedElapsed -= FIXED_TIMESTEP;
		FixedUpdate();
	}
	timeLeftOver = fixedElapsed;
		Update(elapsed);




	Update(elapsed);
	Render();
	return done;
}

void GameClass::FixedUpdate(){
	//prints once per second
	//static int counter = 0;
	//if(!(counter % 60)) printf("a");
	//counter++;

	playerInput(player);
	player->FixedUpdate(staticObjects);
	for (size_t i = 0; i < coins.size(); i++)
		coins[i]->FixedUpdate(staticObjects, player);
}

void GameClass::playerInput(Entity* player){
	player->playerInput();
}