#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

using namespace std;


const float UPBOUND = 1.0f;
const float LOWBOUND = -1.0f;
const float LEFTBOUND = -1.0f;
const float RIGHTBOUND = 1.0f;


SDL_Window* displayWindow;

void videoSetup();

void DrawText(int fontTexture, string text, float size, float spacing, float x, float y, float r, float g, float b, float a);

GLuint LoadTexture(const char *image_path);

void DrawSquare(float x, float y, float radius);

void DrawRectangle(float x, float y, float r1, float r2);

void DrawSprite(GLint texture, float x, float y, float rotation, int resX = 1, int resY = 1);

