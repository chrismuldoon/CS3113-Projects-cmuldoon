#include "invaders.h"


SpaceInvaders::SpaceInvaders(){
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("Less Bugs Than Halo:MCC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	done = false;

}

void SpaceInvaders::DrawSquare(float x, float y, float radius){
	GLfloat quad[] = { (x - radius), (y + radius),
		(x - radius), (y - radius),
		(x + radius), (y - radius),
		(x + radius), (y + radius) };

	GLfloat triangleColors[] = { 0.95, 1.0, 0.0,
		0.95, 1.0, 0.0,
		0.95, 1.0, 0.0,
		0.95, 1.0, 0.0 };



	glLoadIdentity();
	glVertexPointer(2, GL_FLOAT, 0, quad);

	glColorPointer(3, GL_FLOAT, 0, triangleColors);
	glEnableClientState(GL_COLOR_ARRAY);

	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);


	glDisableClientState(GL_COLOR_ARRAY);

}

bool SpaceInvaders::update(){

		////quit czech
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
		}

		//get input

		//update

		//render
		
		
		DrawSquare(0.0, 0.0, 0.2);



	SDL_GL_SwapWindow(displayWindow);
	return done;
}

