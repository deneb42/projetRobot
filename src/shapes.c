#include "../include/shapes.h"

// Shapes
int My_Square = 8;
int My_Cube = 9;

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

void make_square()
{
  glNewList(My_Square, GL_COMPILE);
    glBegin(GL_POLYGON);
      glVertex3f(0, 0, 0);
      glVertex3f(1, 0, 0);
      glVertex3f(1, 1, 0);
      glVertex3f(0, 1, 0);
    glEnd();
  glEndList();
}

void make_cube()
{
  glNewList(My_Cube, GL_COMPILE);
    glTranslatef(-0.5, -0.5, 0.5);

    glColor3f(1, 0, 0);
    glCallList(My_Square);

    glColor3f(1, 1, 0);
    glPushMatrix();
    glTranslatef(0, 0,-1);
    glCallList(My_Square);
    glPopMatrix();

    glColor3f(0, 1, 0);
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glCallList(My_Square);
    glPopMatrix();

    glColor3f(0, 1, 1);
    glPushMatrix();
    glTranslatef(1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glCallList(My_Square);
    glPopMatrix();

    glColor3f(0, 0, 1);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glCallList(My_Square);
    glPopMatrix();

    glColor3f(1, 0, 1);
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    glCallList(My_Square);
    glPopMatrix();
  glEndList();
}
