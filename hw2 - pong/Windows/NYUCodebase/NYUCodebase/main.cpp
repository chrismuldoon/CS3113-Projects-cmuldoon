/*
	Chris Muldoon
	github.com/chrismuldoon
	CS3113
	HW2 

	          O .
           	_/|\_-O
	       ___|_______
	      /     |     \
    	 /      |      \
	    #################
	   /   _ ( )|        \
	  /   ( ) | |         \
	 /  \  |_/  |          \
	/____\/|____|___________\
	   |   |             |
	   |  / \            |
	   | /   \           |
	   _/    /_


	   P0ng!

	   the x speed of the ball increaces slightly after every hit, 
	   but the y speed remains the same so the game never becomes unplayable
*/





#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

using namespace std;



SDL_Window* displayWindow;

const float UPBOUND = 1.0f;
const float LOWBOUND = -1.0f;
const float LEFTBOUND = -1.0f;
const float RIGHTBOUND = 1.0f;


void DrawText(int fontTexture, string text, float size, float spacing, float x, float y, float r, float g, float b, float a) {
	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	float texture_size = 1.0 / 16.0f;
	vector<float> vertexData;
	vector<float> texCoordData;
	vector<float> colorData;
	for (int i = 0; i < text.size(); i++) {
		float texture_x = (float)(((int)text[i]) % 16) / 16.0f;
		float texture_y = (float)(((int)text[i]) / 16) / 16.0f;
		colorData.insert(colorData.end(), { r, g, b, a, r, g, b, a, r, g, b, a, r, g, b, a });
		vertexData.insert(vertexData.end(), { ((size + spacing) * i) + (-0.5f * size), 0.5f * size, ((size + spacing) * i) +
			(-0.5f * size), -0.5f * size, ((size + spacing) * i) + (0.5f * size), -0.5f * size, ((size + spacing) * i) + (0.5f * size), 0.5f
			* size });
		texCoordData.insert(texCoordData.end(), { texture_x, texture_y, texture_x, texture_y + texture_size, texture_x +
			texture_size, texture_y + texture_size, texture_x + texture_size, texture_y });
	}
	glColorPointer(4, GL_FLOAT, 0, colorData.data());
	glEnableClientState(GL_COLOR_ARRAY);

	//glLoadIdentity();
	glTranslatef(x, y, 0.0);
	glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
	glEnableClientState(GL_VERTEX_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDrawArrays(GL_QUADS, 0, text.size() * 4);

	////
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


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

void DrawSquare(float x, float y, float radius){
	GLfloat quad[] = {	(x - radius), (y + radius),
						(x - radius), (y - radius),
						(x + radius), (y - radius),
						(x + radius), (y + radius) };

	GLfloat triangleColors[] = { 0.95, 1.0, 0.0,
								 0.95, 1.0, 0.0,
								 0.95, 1.0, 0.0,
							  	 0.95, 1.0, 0.0 };

	

	glLoadIdentity();
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);


	glColorPointer(3, GL_FLOAT, 0, triangleColors);
	glEnableClientState(GL_COLOR_ARRAY);


	glDrawArrays(GL_QUADS, 0, 4);

	
	glDisableClientState(GL_COLOR_ARRAY);

}

void DrawRectangle(float x, float y, float r1, float r2){
	GLfloat quad[] = {  (x - r1), (y + r2),
						(x - r1), (y - r2),
						(x + r1), (y - r2),
						(x + r1), (y + r2) };

	glLoadIdentity();
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	//glEnd();

}

class Paddle
{
private:
	float xPos, yPos, rX, rY;
	int player;

public:
	Paddle(int playerNum){
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

	float getX() const { return xPos; }
	float getY() const{ return yPos; }
	float getRX() const {return rX;} 
	float getRY() const { return rY; }
	
	bool isHit(float x, float y, float r){}

	void updatePos(float amt){
		yPos += amt;
		if (yPos > UPBOUND - rY) yPos = UPBOUND - rY;
		else if (yPos < LOWBOUND + rY) yPos = LOWBOUND + rY;
	}
	void render(){
		DrawRectangle(xPos, yPos, rX, rY);
	}

};


class Ball
{
private:
	float xPos, yPos, radius, xVel, yVel;
	int score1, score2;
	bool moving;

public:
	


	Ball(bool mov){
		radius = 0.05;
		xPos = -0.1;
		yPos = 1.0 - radius;
		xVel = 0.70; //glunit/sec
		yVel = 0.6;
		//angle = 30.0;
		moving = mov;
	}


	void render(){
		DrawSquare(xPos, yPos, radius);
	}

	void move(float elapsed, const Paddle &p1, const Paddle &p2, int &winner){
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
				xVel =0.7; //reset speed, and so it twords the winner
				xPos = 0.0;
				yPos = 1.0-radius;
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

};

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


void videoSetup(){
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("Less Bugs Than Halo:MCC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}



int main(int argc, char *argv[])
{
	videoSetup();
	bool done = false;
	SDL_Event event;

	float lastFrameTicks = 0.0f;
	int posFlag = 0;
	float rotate = 0.0;
	
	int winnerFlag = 0;
	int lastWinner = 0;
	float winTime = -500.0;

	Ball b(true);
	Paddle player1(1);
	Paddle player2(2);

	GLuint winImg = LoadTexture("win.png");
	GLuint txtImg = LoadTexture("font1.png");


	//DrawText(txtImg, "Hello", 0.2, 0.05, 1.0, 1.0, 1.0, 1.0);


	/////////////////////////////////////////THEGAME
	while (!done) {
		////quit czech
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
		}

		//////timing stuff

		float ticks = (float)SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;
		
		//////////////get input///////////
		
		float mov1 =0;
		float mov2 = 0;
		const Uint8 *keys = SDL_GetKeyboardState(NULL);
		if (keys[SDL_SCANCODE_UP]) {
			mov1 = elapsed* 2.0;
		}
		else if (keys[SDL_SCANCODE_DOWN]) {
			mov1 = elapsed* -2.0;
		}

		if (keys[SDL_SCANCODE_W]) {
			mov2 = elapsed* 2.0;
		}
		else if (keys[SDL_SCANCODE_S]) {
			mov2 = elapsed* -2.0;
		}




		////////update//////////////////
		
		player1.updatePos(mov1);
		player2.updatePos(mov2);
		b.move(elapsed, player1, player2, winnerFlag );

		//check winner
		if (winnerFlag > 0) {
			winTime = lastFrameTicks;
			lastWinner = winnerFlag;
			winnerFlag = 0;
		}

		///////////render/////////////

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);		
		
		
		DrawText(txtImg, "PONG", 0.20, -0.05, -0.3, -0.3, 1.0, 1.0, 1.0, 1.0);

		//if score, render win sprite over correct side for a second
		if (winTime + 0.9 > lastFrameTicks){
			if (lastWinner == 1)  //render sprite for player1
				DrawSprite(winImg, 0.5, 0, 0);
			else if (lastWinner == 2)  //render sprite for player 2
				DrawSprite(winImg, -0.5, 0, 0);
		}
		
		//render game objects
		b.render();
		player1.render();
		player2.render();

		

	
		SDL_GL_SwapWindow(displayWindow);

	}//end while

	SDL_Quit();
	return 0;
}