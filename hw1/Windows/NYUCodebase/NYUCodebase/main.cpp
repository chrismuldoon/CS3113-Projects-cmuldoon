
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>


SDL_Window* displayWindow;

typedef struct {
	float x;
	float y;
	float r;
	float g;
	float b;
} Vertex2D;

GLuint LoadTexture(const char *image_path) {
	SDL_Surface *surface = IMG_Load(image_path);
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	SDL_FreeSurface(surface);
	return textureID;
}

void DrawSprite(GLint texture, float x, float y, float rotation, int resX = 1, int resY =1) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0.0);
	glRotatef(rotation, 0.0, 0.0, 1.0);
	float xOverY = (float)resX / resY;
	float yOverX = 1.0 / xOverY;
	GLfloat quad[] = { -0.4f*xOverY, 0.4f*1, -0.4f*xOverY, -0.4f*1, 0.4f*xOverY, -0.4f*1, 0.4f*xOverY, 0.4f*1 };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);
	GLfloat quadUVs[] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };
	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
}

//typedef struct SDL_Surface
//{
//	int w; // width of the image
//	int h; // height of the image
//	int pitch; // size of a row in bytes
//	void *pixels; // pointer to pixel data
//	// …other data
//} SDL_Surface;


int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("iLLUMiNATi CONFiRMED!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	bool done = false;
	
	SDL_Event event;

	GLuint img_illuminati = LoadTexture("Illuminati-Logo.png");
	GLuint img_dorito = LoadTexture("dorito.png");
	GLuint img_mtndew = LoadTexture("dew.png");


	float lastFrameTicks = 0.0f;
	int posFlag = 0;
	float rotate = 0.0;
	
	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
		}

		float ticks = (float)SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;

		rotate += 45.0f * elapsed;


		posFlag++;
		if (posFlag== 8) posFlag = 0;


		glClearColor(1.4f, 0.0f, 1.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		

		//make (x,y) shake
		float x = 0.0;
		float y = 0.0;

		if		(posFlag == 0){ x = 0.05; y = 0.0; }
		else if (posFlag == 2){ x = 0.0; y = 0.05; }
		else if (posFlag == 4){ x = -0.05; y = 0.0; }
		else if (posFlag == 6){ x = 0.0; y = -0.05; }

		//triangle
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glBegin(GL_TRIANGLES);

		glColor3f(0.1, 0.1, 0.7);
		glVertex2d(0, 0.8);

		glColor3d(0.1, 0.5, 0.1);
		glVertex2d(-0.7, -0.7);

		glColor3d(0.6, 0.1, 0.1);
		glVertex2d(0.7, -0.7);

		glColor3d(1.0, 1.0, 1.0);
		//glLoadIdentity();

		glEnd();


		//sprites
		DrawSprite(img_illuminati, x, y, 0.0);
		DrawSprite(img_dorito, 0.5, -0.2, rotate, 200, 189);
		DrawSprite(img_mtndew, -0.5, -0.2, rotate*(-1.0), 213, 504);



		//Vertex2D triangle[3] = { { 0.5, 0.5, 1.0, 0.0, 0.0 },
		//{ 0.6, 0.5, 0.0, 0.0, 0.0 },
		//{ 0.55, 0.58, 0.0, 0.0, 0.0 } };

		//glVertexPointer(2, GL_FLOAT, sizeof(float) * 5, triangle);
		//glEnableClientState(GL_VERTEX_ARRAY);

		//glColorPointer(3, GL_FLOAT, sizeof(float) * 5, &triangle[0].r);
		//glEnableClientState(GL_COLOR_ARRAY);
		
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		////std::cout << rotate << "\n";




		SDL_GL_SwapWindow(displayWindow);
	}

	SDL_Quit();
	return 0;
}