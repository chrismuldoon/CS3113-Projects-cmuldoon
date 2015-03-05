
/*
	Chris Muldoon
	github.com/chrismuldoon
	CS3113
	HW2 


*/


#include "GameClass.h"

int main(int argc, char *argv[])
{
	GameClass app;
	while (!app.UpdateAndRender()) {}
	return 0;
}