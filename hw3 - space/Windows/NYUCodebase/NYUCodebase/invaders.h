#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

using namespace std;

class SpaceInvaders
{
public:
	SpaceInvaders();
	//~SpaceInvaders();
	bool update();
	void DrawText(int fontTexture, string text, float size, float spacing, float x, float y, float r, float g, float b, float a);
	GLuint LoadTexture(const char *image_path);
	void DrawSquare(float x, float y, float radius);
	void DrawRectangle(float x, float y, float r1, float r2);

private:
	bool done;
	SDL_Event event;
	SDL_Window* displayWindow;

};

