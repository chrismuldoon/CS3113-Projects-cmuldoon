#pragma once
#include "pong.h"


	Paddle::Paddle(int playerNum){
		yPos = 0.0;
		rX = .05;
		rY = .15;

		if (playerNum == 1){
			xPos = 1.33 - rX;
			player = 1;
		}

		else{
			xPos = -1.33 + rX;
			player = 1;
		}

	}

	float Paddle::getX() const { return xPos; }
	float Paddle::getY() const{ return yPos; }
	float Paddle::getRX() const { return rX; }
	float Paddle::getRY() const { return rY; }


	void Paddle::updatePos(float amt){
		yPos += amt;
		if (yPos > UPBOUND - rY) yPos = UPBOUND - rY;
		else if (yPos < LOWBOUND + rY) yPos = LOWBOUND + rY;
	}
	void Paddle::render(){
		DrawRectangle(xPos, yPos, rX, rY);
	}




	Ball::Ball(bool mov){
		radius = 0.05;
		xPos = -0.1;
		yPos = 1.0 - radius;
		xVel = 0.70; //glunit/sec
		yVel = 0.6;
		//angle = 30.0;
		moving = mov;
	}


	void Ball::render(){
		DrawSquare(xPos, yPos, radius);
	}

	void Ball::move(float elapsed, const Paddle &p1, const Paddle &p2, int &winner){
		xPos = xPos + xVel * elapsed;		//* sin(angle * 3.14 / 180.0);
		yPos = yPos + yVel * elapsed;		//* cos(angle * 3.14 / 180.0);


		///////CHECK FOR COLLISIONS WITH P1 

		if (xVel > 0 && xPos >0){ //moving to the right
			if ((xPos + radius) >= (p1.getX() - p1.getRX()) &&
				(xPos - radius) <= (p1.getX() + p1.getRX()) &&
				(yPos + radius) >= (p1.getY() - p1.getRY()) &&
				(yPos - radius) <= (p1.getY() + p1.getRY()))
			{
				//collision with p1!
				xVel *= -1.0;
				xVel -= 0.1; //p2 is on left so more speed to the right

			}

			else if ((xPos + radius) >= 1.33) { // point award to player2!!
				xVel = -0.7; //reset speed, and so it twords the winner
				xPos = 0.0;
				yPos = 1.0 - radius;
				winner = 2;
			}

		} //end top if


		///////CHECK FOR COLLISIONS WITH P2 

		else if (xVel < 0 && xPos <0) {  //moving to the left

			if ((xPos + radius) >= (p2.getX() - p2.getRX()) &&
				(xPos - radius) <= (p2.getX() + p2.getRX()) &&

				(yPos + radius) >= (p2.getY() - p2.getRY()) &&
				(yPos - radius) <= (p2.getY() + p2.getRY()))
			{
				//collision with p2!
				xVel *= -1.0;
				xVel += 0.1; //p2 is on left so more speed to the right
			}

			else if ((xPos - radius) <= -1.33) {   // point award to player1!!
				xVel = 0.7; //reset speed, and so it twords the winner
				xPos = 0.0;
				yPos = 1.0 - radius;
				winner = 1;
			}


		} //end top elseif



		//collisions at walls, y = -1, 1
		if (yPos >= (1.0 - radius)){
			yPos = 1.0 - radius; //fix later for greater acuracy
			yVel = -1.0*abs(yVel);
		}
		else if (yPos <= (-1.0 + radius)) {
			yPos = -1.0 + radius;
			yVel = abs(yVel);
		}


	} // end move() def

