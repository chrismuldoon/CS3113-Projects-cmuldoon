#pragma once
#include "draw.h"





class Paddle
{
private:
	float xPos, yPos, rX, rY;
	int player;

public:
	Paddle(int playerNum);
	float getX() const;
	float getY() const;
	float getRX() const;
	float getRY() const;
	

	void updatePos(float amt);
	void render();

};


class Ball
{
private:
	float xPos, yPos, radius, xVel, yVel;
	int score1, score2;
	bool moving;

public:
	Ball(bool mov);
	void render();
	void move(float elapsed, const Paddle &p1, const Paddle &p2, int &winner);
};
