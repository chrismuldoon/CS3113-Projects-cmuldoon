/*
	Chris Muldoon
	github.com/chrismuldoon
	CS3113
	HW2 


*/




#include "invaders.h"

using namespace std;





//extern SDL_Window* displayWindow;



int main(int argc, char *argv[]){


	SpaceInvaders game;
	while (!game.update()) {}

	return 0;




}


//int main2(int argc, char *argv[])
//{
//	videoSetup();
//	bool done = false;
//	SDL_Event event;
//
//	float lastFrameTicks = 0.0f;
//	int posFlag = 0;
//	float rotate = 0.0;
//	
//	int winnerFlag = 0;
//	int lastWinner = 0;
//	float winTime = -500.0;
//
//	Ball b(true);
//	Paddle player1(1);
//	Paddle player2(2);
//
//	GLuint winImg = LoadTexture("win.png");
//	GLuint txtImg = LoadTexture("font1.png");
//
//
//	//DrawText(txtImg, "Hello", 0.2, 0.05, 1.0, 1.0, 1.0, 1.0);
//
//
//	/////////////////////////////////////////THEGAME
//	while (!done) {
//		////quit czech
//		while (SDL_PollEvent(&event)) {
//			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
//				done = true;
//			}
//		}
//
//		//////timing stuff
//
//		float ticks = (float)SDL_GetTicks() / 1000.0f;
//		float elapsed = ticks - lastFrameTicks;
//		lastFrameTicks = ticks;
//		
//		//////////////get input///////////
//		
//		float mov1 =0;
//		float mov2 = 0;
//		const Uint8 *keys = SDL_GetKeyboardState(NULL);
//		if (keys[SDL_SCANCODE_UP]) {
//			mov1 = elapsed* 2.0;
//		}
//		else if (keys[SDL_SCANCODE_DOWN]) {
//			mov1 = elapsed* -2.0;
//		}
//
//		if (keys[SDL_SCANCODE_W]) {
//			mov2 = elapsed* 2.0;
//		}
//		else if (keys[SDL_SCANCODE_S]) {
//			mov2 = elapsed* -2.0;
//		}
//
//
//
//
//		////////update//////////////////
//		
//		player1.updatePos(mov1);
//		player2.updatePos(mov2);
//		b.move(elapsed, player1, player2, winnerFlag );
//
//		//check winner
//		if (winnerFlag > 0) {
//			winTime = lastFrameTicks;
//			lastWinner = winnerFlag;
//			winnerFlag = 0;
//		}
//
//		///////////render/////////////
//
//		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);		
//		
//		
//		DrawText(txtImg, "PONG", 0.20, -0.05, -0.3, -0.3, 1.0, 1.0, 1.0, 1.0);
//
//		//if score, render win sprite over correct side for a second
//		if (winTime + 0.9 > lastFrameTicks){
//			if (lastWinner == 1)  //render sprite for player1
//				DrawSprite(winImg, 0.5, 0, 0);
//			else if (lastWinner == 2)  //render sprite for player 2
//				DrawSprite(winImg, -0.5, 0, 0);
//		}
//		
//		//render game objects
//		b.render();
//		player1.render();
//		player2.render();
//
//		
//
//	
//		SDL_GL_SwapWindow(displayWindow);
//
//	}//end while
//
//	SDL_Quit();
//	return 0;
//}