#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <string>
#include <vector>

using namespace std;

void DrawSpriteSheetSprite(int spriteTexture, int index, int spriteCountX, int spriteCountY);

void DrawRectangle(float x, float y, float r1, float r2);

GLuint LoadTexture(const char *image_path);

void DrawText(int fontTexture, string text, float size, float spacing, float x, float y, float r, float g, float b, float a);