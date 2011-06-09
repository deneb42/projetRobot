#ifndef __APPLE__
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#else
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

#define PI 3.1415926535898

float angle_z=0;
float angle_y=0;
float angle_x=0;
float posi_x=0;
float posi_y=0;
float posi_z=0;
float zoom=5;
int mouse_pos_x = 0, mouse_pos_y = 0;
short mouse_down_is_left = 0;

long increment=0;

char *chemin;


void init_scene();
void render_scene();
void makeBender(char *chemin);
void drawBender();
void drawRepere();
float getCoord(char part, char axe, int side, int index);
void setCoord(char part, char axe, int side, int index, float value);

void makeSky();

GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
GLvoid window_mouseFunc(int button, int state, int x, int y);
GLvoid window_motionFunc(int x, int y);
GLvoid window_timer();

int main(int argc, char* argv[])
{
	int i;

	printf("lol : %s\n", argv[0]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("test Bender");
	// end of glut initializations

	glutReshapeFunc(&window_reshape);
	glutDisplayFunc(&window_display);
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&window_mouseFunc);
	glutMotionFunc(&window_motionFunc);
	glutTimerFunc(40, &window_timer, 0);
	// end of the setting of glut's callback functions

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5,0.5,0.5, 1);
	// end of GL initializations
	
	chemin = (char*)malloc(100);
	chemin[0]='\0';
	strcat(chemin, argv[0]);
	for(i=99;i>=0;i--)
	{
		if(chemin[i]=='/' || chemin[i]=='\\')
		{
			chemin[i+1]='\0';
			i=-1;
		}
	}

	//--------------------------------------------------------------------------- HERE 1-------<<<
	makeBender(chemin);
	makeSky();

	//-----------------------------------------------------------------------------------------<<<

	glutMainLoop();

	return EXIT_FAILURE;
}


void render_scene()
{
	
	glRotatef(angle_z, 1, 0, 0);
	glRotatef(angle_y, 0, 1, 0);
	glRotatef(angle_x, 0, 0, 1);

	// ------------------------------------------------------------------------- HERE 2-------<<<
	glRotatef(-90, 1, 0,0);
	// ---------------------------------------------------------------------------------------<<<

	glCallList(6);
	
	glTranslatef(posi_x,posi_y,posi_z);

	drawRepere();

	// -------------------------------------------------------------------------- HERE 3-------<<<
	drawBender(100);

	//-----------------------------------------------------------------------------------------<<<

	glutSwapBuffers();
}


GLvoid window_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	render_scene();

	glFlush();

}


GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-zoom, zoom, -zoom, zoom, -10, 100*zoom);
	glMatrixMode(GL_MODELVIEW);
}


GLvoid window_key(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'z':
			posi_z-=0.1;
			break;
		case 's':
			posi_z+=0.1;
			break;
		case 'q':
			posi_x+=0.1;
			break;
		case 'd':
			posi_x-=0.1;
			break;
		case 'r':
			angle_x=0;
			angle_y=0;
			angle_z=0;
			posi_x=0;
			posi_y=0;
			posi_z=0;
			zoom=5;
			window_reshape(400, 400);
			break;
		case 'a':
			zoom+=0.1;
			window_reshape(400, 400);
			break;
		case 'e':
			zoom-=0.1;
			window_reshape(400, 400);
			break;
		default:
			exit(1);
			break;
	}
	glutPostRedisplay();
}

GLvoid window_mouseFunc(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		mouse_pos_x = x;
		mouse_pos_y = y;
		mouse_down_is_left = 1;
		glPushMatrix();
	}
	else {
		mouse_down_is_left = 0;
		glPopMatrix();
	}
}

GLvoid window_motionFunc(int x, int y)
{
	if( !mouse_down_is_left )
	return;

	angle_z += y - mouse_pos_y;
	angle_y += x - mouse_pos_x;

	mouse_pos_x = x;
	mouse_pos_y = y;

	glutPostRedisplay();
}

void drawRepere()
{
	glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex3f(-10,0,0);
		glColor3f(1,0,0);
		glVertex3f(0, 0, 0);
		glColor3f(1,0,0);
		glVertex3f(0, 0, 0);
		glColor3f(1,1,1);
		glVertex3f(10, 0, 0);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex3f(0,-10,0);
		glColor3f(0,1,0);
		glVertex3f(0,0, 0);
		glColor3f(0,1,0);
		glVertex3f(0,0, 0);
		glColor3f(1,1,1);
		glVertex3f(0, 10, 0);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex3f(0,0,-10);
		glColor3f(0,0,1);
		glVertex3f(0, 0, 0);
		glColor3f(0,0,1);
		glVertex3f(0, 0, 0);
		glColor3f(1,1,1);
		glVertex3f(0, 0, 10);
	glEnd();
}

void makeSky()
{
	int tex;
	
	if (!(tex = loadBMPTexture("textures/skybox.bmp") ))
	{
		printf("Impossible de charger la texture 'skybox'\n");
		exit(EXIT_FAILURE);
	}
	// !!! danger approximation
	glNewList(6, GL_COMPILE);
		glPushMatrix();
			glColor3f (1,1,1);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,tex);
			
			glBegin(GL_POLYGON);//millieu
				glTexCoord2f(0.25, 0.65);	glVertex3f(-300,300,300);
				glTexCoord2f(0.5, 0.65);		glVertex3f(300,300,300);
				glTexCoord2f(0.5, 0.34);		glVertex3f(300,300,-300);
				glTexCoord2f(0.25, 0.34);    glVertex3f(-300,300,-300);
			glEnd();
			
			glBegin(GL_POLYGON);//haut
				glTexCoord2f(0.25, 1);		glVertex3f(-300,-300,300);
				glTexCoord2f(0.5, 1);		glVertex3f(300,-300,300);
				glTexCoord2f(0.5, 0.65);		glVertex3f(300,300,300);
				glTexCoord2f(0.25, 0.65);    glVertex3f(-300,300,300);
			glEnd();
			
			glBegin(GL_POLYGON);//gauche
				glTexCoord2f(0, 0.65);		glVertex3f(-300,-300,300);
				glTexCoord2f(0.25, 0.65);		glVertex3f(-300,300,300);
				glTexCoord2f(0.25, 0.34);		glVertex3f(-300,300,-300);
				glTexCoord2f(0, 0.34);      glVertex3f(-300,-300,-300);
			glEnd();
			
			glBegin(GL_POLYGON);//bas
				glTexCoord2f(0.25, 0.34);	glVertex3f(-300,300,-300);
				glTexCoord2f(0.5, 0.34);		glVertex3f(300,300,-300);
				glTexCoord2f(0.5, 0);		glVertex3f(300,-300,-300);
				glTexCoord2f(0.25, 0);      glVertex3f(-300,-300,-300);
			glEnd();
			
			glBegin(GL_POLYGON);//droite
				glTexCoord2f(0.5, 0.65);		glVertex3f(300,300,300);
				glTexCoord2f(0.75, 0.65);		glVertex3f(300,-300,300);
				glTexCoord2f(0.75, 0.34);		glVertex3f(300,-300,-300);
				glTexCoord2f(0.5, 0.34);      glVertex3f(300,300,-300);
			glEnd();
			
			glBegin(GL_POLYGON);//derrière
				glTexCoord2f(0.75, 0.65);	glVertex3f(300,-300,300);
				glTexCoord2f(1, 0.65);		glVertex3f(-300,-300,300);
				glTexCoord2f(1, 0.34);		glVertex3f(-300,-300,-300);
				glTexCoord2f(0.75, 0.34);      glVertex3f(300,-300,-300);
			glEnd();
				
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	glEndList();
}

GLvoid window_timer()
{
	float Sin = sin(increment*PI/180);
	float Cos = cos(increment*PI/180);
	float Sin1P = sin((increment+180)*PI/180);
	float Cos1P = cos((increment+180)*PI/180);
	float tmp;

	glutTimerFunc(40,&window_timer,0);
	
	// bras !!!
	setCoord('h', 'y', 0, 1, -(Sin*0.7));
	setCoord('h', 'y', 0, 2, -(0.1 + Sin*(0.7+0.1)));
	setCoord('h', 'y', 0, 3, -(0.15 + Sin*(1.1+0.15)));
	
	setCoord('h', 'z', 0, 1, -(0.55 + (Sin<0?-Sin:Sin)*(0.95-0.55)));
	setCoord('h', 'z', 0, 2, -(1.765 + (Sin<0?-Sin:Sin)*(1.875-1.765)));
	setCoord('h', 'z', 0, 3, -(2.2 + (Cos<0?-Cos:Cos)*(2.45-2.2)));
	
	setCoord('h', 'y', 1, 1, -(Sin1P*0.7));
	setCoord('h', 'y', 1, 2, -(0.1 + Sin1P*(0.7+0.1)));
	setCoord('h', 'y', 1, 3, -(0.15 + Sin1P*(1.1+0.15)));
	
	setCoord('h', 'z', 1, 1, -(0.55 + (Sin1P<0?-Sin1P:Sin1P)*(0.95-0.55)));
	setCoord('h', 'z', 1, 2, -(1.765 + (Sin1P<0?-Sin1P:Sin1P)*(1.875-1.765)));
	setCoord('h', 'z', 1, 3, -(2.2 + (Cos1P<0?-Cos1P:Cos1P)*(2.45-2.2)));
	
	// jambes !!!
	setCoord('f', 'y', 0, 1, (Sin*1.125));
	setCoord('f', 'y', 0, 2, (Sin*1.2));
	setCoord('f', 'y', 0, 3, (Sin*1.225));

	setCoord('f', 'z', 0, 2, -(1.8 + Cos*(2-1.8)));
	tmp = -(2.675+(3.3-2.85) + Cos*(3.5-2.675));
	setCoord('f', 'z', 0, 3, tmp<-3 ? -3:tmp);
	
	setCoord('f', 'y', 1, 1, (Sin1P*1.125));
	setCoord('f', 'y', 1, 2, (Sin1P*1.2));
	setCoord('f', 'y', 1, 3, (Sin1P*1.225));

	setCoord('f', 'z', 1, 2, -(1.8 + Cos1P*(2-1.8)));
	tmp = -(2.675+(3.3-2.85) + Cos1P*(3.5-2.675)); //3.3-2.85 valeur trouvée pour faire que le pied heurte le sol quand il ne va plus en avant
	setCoord('f', 'z', 1, 3, tmp<-3 ? -3:tmp);
	
	glutPostRedisplay();
	
	if(increment<360) increment+=6; else increment=0; // on peut se permettre car elles sont 360 periodiques
}
