#include <string.h>

#include "bmp.h"


void loadTexture(char* path, char* name, int *tex)
{
	char nameWPath[150];

	sprintf(nameWPath, "%stextures/%s", path, name);

	printf("loading : %s\n", nameWPath);

	if (!(*tex= loadBMPTexture(nameWPath)) )
	{
		printf("Could not read '%s'\n", nameWPath);
		exit(EXIT_FAILURE);
	}
}

void drawRepere()
{
	glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex3f(-100,0,0);
		glColor3f(1,0,0);
		glVertex3f(0, 0, 0);
		glColor3f(1,0,0);
		glVertex3f(0, 0, 0);
		glColor3f(1,1,1);
		glVertex3f(100, 0, 0);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex3f(0,-100,0);
		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glColor3f(1,1,1);
		glVertex3f(0, 100,0);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex3f(0,0,-100);
		glColor3f(0,0,1);
		glVertex3f(0, 0,0);
		glColor3f(0,0,1);
		glVertex3f(0, 0,0);
		glColor3f(1,1,1);
		glVertex3f(0, 0,100);
	glEnd();
}
