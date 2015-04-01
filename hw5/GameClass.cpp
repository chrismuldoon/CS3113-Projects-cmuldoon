#pragma once

#include "GameClass.h"
#include "defines.h"

// 60 FPS (1.0f/60.0f)
//#define FIXED_TIMESTEP 0.0166666f
//#define MAX_TIMESTEPS 6


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
	spriteImg = LoadTexture("arne_sprites.png");

	unsigned char levelData1[LEVEL_HEIGHT][LEVEL_WIDTH] =
	{	{ 0, 1, 12, 12, 12, 12, 2, 3 }, 
		{ 12, 12, 12, 12, 12, 12, 12, 12 },
		{ 12, 12, 12, 12, 12, 12, 12, 12 }, 
		{ 12, 12, 12, 12, 12, 12, 12, 12 },
		{ 12, 12, 12, 12, 12, 12, 12, 12 },
		{ 1, 1, 1, 1, 1, 1, 1, 1 }
	
	
	
	};

	memcpy(levelData, levelData1, LEVEL_HEIGHT*LEVEL_WIDTH);


	player = new Entity(0.3f, 0.3f, 0.07f, 0.09f);


}
//defines for sprite sheet
#define SPRITE_COUNT_X 16
#define SPRITE_COUNT_Y 8

void GameClass::renderLevel(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spriteImg);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::vector<float> vertexData;
	std::vector<float> texCoordData;

	for (int y = 0; y < LEVEL_HEIGHT; y++) {
		for (int x = 0; x < LEVEL_WIDTH; x++) {
			float u = (float)(((int)levelData[y][x]) % SPRITE_COUNT_X) / (float)SPRITE_COUNT_X;
			float v = (float)(((int)levelData[y][x]) / SPRITE_COUNT_X) / (float)SPRITE_COUNT_Y;
			float spriteWidth = 1.0f / (float)SPRITE_COUNT_X;
			float spriteHeight = 1.0f / (float)SPRITE_COUNT_Y;
			vertexData.insert(vertexData.end(), {
				TILE_SIZE * x, -TILE_SIZE * y,
				TILE_SIZE * x, (-TILE_SIZE * y) - TILE_SIZE,
				(TILE_SIZE * x) + TILE_SIZE, (-TILE_SIZE * y) - TILE_SIZE,
				(TILE_SIZE * x) + TILE_SIZE, -TILE_SIZE * y
			});
			texCoordData.insert(texCoordData.end(), { u, v,
				u, v + (spriteHeight),
				u + spriteWidth, v + (spriteHeight),
				u + spriteWidth, v
			});
		}
	}

	glLoadIdentity();
	glTranslatef(-TILE_SIZE * LEVEL_WIDTH / 2, TILE_SIZE * LEVEL_HEIGHT / 2, 0.0f);


	glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
	glEnableClientState(GL_VERTEX_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDrawArrays(GL_QUADS, 0, LEVEL_HEIGHT*LEVEL_WIDTH * 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);


}

GameClass::~GameClass() {
	SDL_Quit();
}
void GameClass::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// render stuff

	DrawText(textImg, "Hello World", 0.2f, -0.1f, -0.9f, 0.5f, 1.0, 1.0, 1.0, 1.0);
	//DrawRectangle(0.0f, -0.2f, 0.2f, 0.2f);

	DrawSpriteSheetSprite(spriteImg, 80, 16, 8);
	renderLevel();

	player->Render();


	SDL_GL_SwapWindow(displayWindow);
	
}
void GameClass::Update(float elapsed) {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
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


	//playerInput(player);
	player->FixedUpdate(staticObjects, levelData);
}