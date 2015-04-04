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

	//unsigned char levelData1[LEVEL_HEIGHT][LEVEL_WIDTH] =
	//{	{  3,  3,  3,  3,  3,  3,  3,  3 }, 
	//	{  3, 12, 12, 12, 12, 12, 12,  3 },
	//	{  3, 12, 12, 12, 12, 12, 12,  3 }, 
	//	{  3, 12, 12, 12, 12, 12, 12,  3 },
	//	{  3,  1,  1,  1,  1,  1,  1,  3 },
	//	{  3,  3,  3,  3,  3,  3,  3,  3 }
	//
	//
	//
	//};

	//memcpy(levelData, levelData1, LEVEL_HEIGHT*LEVEL_WIDTH);

	ReadTileMapFile();

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	music = Mix_LoadMUS("murder.mp3");

	player = new Entity(1.5f, -0.7f, 0.055f, 0.0625f);
	player->jumpSound = Mix_LoadWAV("smw_jump.wav");
	player->hitSound = Mix_LoadWAV("smw_shell_ricochet.wav");

	

	
	//someSound = Mix_LoadWAV("hangout.wav");

	//Mix_PlayChannel(-1, someSound, 0);
	Mix_PlayMusic(music, -1);

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

	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
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

	//glLoadIdentity();
	//glTranslatef(-TILE_SIZE * LEVEL_WIDTH / 2, TILE_SIZE * LEVEL_HEIGHT / 2, 0.0f);


	glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
	glEnableClientState(GL_VERTEX_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDrawArrays(GL_QUADS, 0, mapHeight*mapWidth * 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);


}

GameClass::~GameClass() {
	//SDL_Quit();
	//Mix_FreeChunk(someSound);
	Mix_FreeMusic(music);
	SDL_Quit();
}
void GameClass::Render() {
	glClearColor(0.04f, 0.60f, 0.67f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// render stuff

	//DrawText(textImg, "Hello World", 0.2f, -0.1f, -0.9f, 0.5f, 1.0, 1.0, 1.0, 1.0);
	//DrawRectangle(0.0f, -0.2f, 0.2f, 0.2f);

	//DrawSpriteSheetSprite(spriteImg, 80, 16, 8);

	//scrolling
	glLoadIdentity();
	//glTranslatef(player->xPos*-1.0, player->yPos*-1.0, 0.0);
	glTranslatef(player->xPos*-1.0, 1.0, 0.0);

	renderLevel();

	player->Render();


	SDL_GL_SwapWindow(displayWindow);
	
}
void GameClass::Update(float elapsed) {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
				// DO AN ACTION WHEN SPACE IS PRESSED!
				//if (!player) break;
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


	player->playerInput();
	player->FixedUpdate(levelData, mapHeight, mapWidth);
}

/////////////////////////////
//file stuff

void GameClass::ReadTileMapFile() {
	std::ifstream infile("level1.txt");
	std::string line;
	while (std::getline(infile, line)) {
		if (line == "[header]" && !ReadTileMapHeaderData(infile)) {
			return;
		}
		else if (line == "[layer]") {
			ReadTileMapLayerData(infile);
		}
		else if (line == "[ObjectLayer]") {
			ReadTileMapEntityData(infile);
		}
	}
}

bool GameClass::ReadTileMapHeaderData(std::ifstream &stream) {
	std::string line;
	mapWidth = -1;
	mapHeight = -1;
	while (std::getline(stream, line)) {
		if (line == "") { break; }
		std::istringstream sStream(line);
		std::string key, value;
		std::getline(sStream, key, '=');
		std::getline(sStream, value);
		if (key == "width") {
			mapWidth = atoi(value.c_str());
		}
		else if (key == "height"){
			mapHeight = atoi(value.c_str());
		}
	}

	if (mapWidth == -1 || mapHeight == -1) {
		return false;
	}
	else {
		levelData = new unsigned char*[mapHeight];
		for (int i = 0; i < mapHeight; ++i) {
			levelData[i] = new unsigned char[mapWidth];
		}
		return true;
	}
}

bool GameClass::ReadTileMapLayerData(std::ifstream &stream) {
	std::string line;
	while (std::getline(stream, line)) {
		if (line == "") { break; }
		std::istringstream sStream(line);
		std::string key, value;
		std::getline(sStream, key, '=');
		std::getline(sStream, value);
		if (key == "data") {
			for (int y = 0; y < mapHeight; y++) {
				std::getline(stream, line);
				std::istringstream lineStream(line);
				std::string tile;
				for (int x = 0; x < mapWidth; x++) {
					std::getline(lineStream, tile, ',');
					unsigned char val = (unsigned char)atoi(tile.c_str());
					if (val > 0) {
						// be careful, the tiles in this format are indexed from 1 not 0
						levelData[y][x] = val - 1;
					}
					else {
						levelData[y][x] = 12;
					}
				}
			}
		}
	}
	return true;
}

bool GameClass::ReadTileMapEntityData(std::ifstream &stream) {
	std::string line, type;
	while (std::getline(stream, line)) {
		if (line == "") { break; }
		std::istringstream sStream(line);
		std::string key, value;
		std::getline(sStream, key, '=');
		std::getline(sStream, value);
		if (key == "type") {
			type = value;
		}
		else if (key == "location") {
			std::istringstream lineStream(value);
			std::string xPosition, yPosition;
			std::getline(lineStream, xPosition, ',');
			std::getline(lineStream, yPosition, ',');
			float placeX = atoi(xPosition.c_str()) / 16 * TILE_SIZE + TILE_SIZE;
			float placeY = atoi(yPosition.c_str()) / 16 * -TILE_SIZE;
			//BuildEntity(type, placeX, placeY);
		}
	}
	return true;
}


