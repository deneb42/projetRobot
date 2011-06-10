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
#include <math.h>

#include "bmp.h"

//utils
#define PI 3.1415926535898
#define SLICES 20
#define STACKS 20
#define NB_TEXTURE 2

//lists
#define BENDER 2
#define EYES 3
#define HAND 4
#define FOOT 5

//colors
#define LIGHT_GRAY 0.84, 0.9, 0.95
#define DARK_GRAY 0.74, 0.8, 0.87
#define WHITE 0.99, 0.99, 0.82
#define BLACK 0.04, 0.05, 0.05
#define BLUE_GRAY 0.6,0.69,0.78
#define LIGHT_BLACK 0.4, 0.5, 0.5


float Bezier4 ( float coor[4] , float t );

void loadTexture(char* chemin, int tex[NB_TEXTURE]);
void makeBody(int tex[NB_TEXTURE]);
void makeEyes();
void makeHand();
void makeFoot();
void drawLimb(char limb, int nbSlices, float *controlsX, float *controlsY, float *controlsZ);


float legX[2][4] = {{ 0.0, -0.1, -0.15, -0.2 }, { 0.0, 0.1, 0.15, 0.2 }};
float legY[2][4] = {{ 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0 }};
float legZ[2][4] = {{ -0.01, -1.0, -2.0, -3.0 }, { -0.01, -1.0, -2.0, -3.0 }}; //control points for legs

float armX[2][4] = {{ 0.0, -1.0, -1.1, -1.2 }, { 0.0, 1.0, 1.1, 1.2 }};
float armY[2][4] = {{ 0.0, 0.0, -0.1, -0.15 }, { 0.0, 0.0, -0.1, -0.15 }};
float armZ[2][4] = {{ 0.0, -1.0, -2.0, -2.5 }, { 0.0, -1.0, -2.0, -2.5 }}; // control points for arms
//0 is right, 1 is left


void drawBender(int nbSlices)
{
	float paddingLeg=0.5, paddingShoulder=1.1, hShoulder=2.2, rShoulder=0.35;
	int i;

	GLUquadricObj* qobj = gluNewQuadric(); // allocation of a quadric description
	gluQuadricDrawStyle(qobj, GLU_FILL); // quadric is filled
	gluQuadricNormals(qobj, GLU_SMOOTH); // shadowings are smooth


	glPushMatrix();
		glTranslatef(0,0,3+0.5); // on se place a la bonne hauteur
		glCallList(BENDER);

		glTranslatef(-paddingLeg,0,0);
		drawLimb('f', nbSlices, legX[0], legY[0], legZ[0]); //right

		glTranslatef(2*paddingLeg,0,0);
		drawLimb('f', nbSlices, legX[1], legY[1], legZ[1]); // left


		glTranslatef(-paddingLeg, 0, hShoulder); // placing at shoulder's height

		for(i=0;i<2;i++)
		{
			glPushMatrix();
				glColor3f(DARK_GRAY);
				glTranslatef(((i*2)-1)*paddingShoulder, 0, 0); // then placing to the good side of the body, (i*2)-1 gives -1 then 1

				glutSolidSphere(rShoulder, SLICES, STACKS); // drawing shoulder
				drawLimb('h', nbSlices, armX[i], armY[i], armZ[i]); // arm
			glPopMatrix();
		}
	glPopMatrix();
}


float Bezier4 ( float coor[4] , float t )
{
	return coor[0]*(1-t)*(1-t)*(1-t) + 3*coor[1]*t*(1-t)*(1-t) + 3*coor[2]*t*t*(1-t) + coor[3]*t*t*t;
}

void loadTexture(char* chemin, int tex[NB_TEXTURE])
{
	int i;
	char lulz[150];

	char nomTextures[NB_TEXTURE][50] = {"ventreBender.bmp", "jackObender.bmp"};

	for(i=0;i<NB_TEXTURE;i++)
	{
		sprintf(lulz, "%stextures/%s", chemin, nomTextures[i]);

		if (!(tex[i] = loadBMPTexture(lulz) ))
		{
			printf("Impossible de charger la texture '%s'\n", lulz);
			exit(EXIT_FAILURE);
		}
		else
			printf("loading : %s\n", lulz);
	}
}

void makeBender(char *chemin)
{
	int tex[NB_TEXTURE];
	loadTexture(chemin, tex);

	makeBody(tex);
	makeEyes();
	makeHand();
	makeFoot(); // calling all the lists declarations
}


void makeBody(int tex[NB_TEXTURE])
{
	float innerBody=1, outerBody=1.25, hBody=2.8, hShoulder=0.5, rHead=0.6, hHead=1.2;
	float innerAnt=0.02, outerAnt=0.05, hAnt=0.5, rBottomAnt=0.1, rTopAnt=0.06;

	GLUquadricObj* qobj = gluNewQuadric(); // allocation of a quadric description
	gluQuadricDrawStyle(qobj, GLU_FILL); // quadric is filled
	gluQuadricNormals(qobj, GLU_SMOOTH); // shadowings are smooth

	glNewList(BENDER, GL_COMPILE); //bender body (WO arms and legs)
		glPushMatrix();

			glColor3f(1, 1, 1);//DARK_GRAY);

			gluQuadricTexture(qobj, GLU_TRUE);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,tex[0]);

			gluCylinder(qobj, innerBody, outerBody, hBody, SLICES, STACKS); // body
			glDisable(GL_TEXTURE_2D);
			gluQuadricTexture(qobj, GLU_FALSE);

			glColor3f(DARK_GRAY);
			gluDisk(qobj, 0, innerBody, SLICES, STACKS); // shiny metal ass

			glColor3f(LIGHT_GRAY);
			glTranslatef(0,0,hBody);
			gluCylinder(qobj, outerBody, rHead, hShoulder, SLICES, STACKS); // shoulders

			glColor3f(1, 1, 1);
			glTranslatef(0,0,hShoulder);

			gluQuadricTexture(qobj, GLU_TRUE);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,tex[1]);
			gluCylinder(qobj, rHead, rHead, hHead, SLICES, STACKS); // head
			glDisable(GL_TEXTURE_2D);
			gluQuadricTexture(qobj, GLU_FALSE);

			glCallList(EYES); // eyes / glasses

			glColor3f(DARK_GRAY);
			glTranslatef(0,0,hHead);
			glutSolidSphere(rHead, SLICES, STACKS); // head's top

			glColor3f(BLUE_GRAY);
			glTranslatef(0,0,rHead);
			gluCylinder(qobj, outerAnt, innerAnt, hAnt, SLICES, STACKS); // antenna

			glColor3f(LIGHT_GRAY);
			glutSolidSphere(rBottomAnt, SLICES, STACKS); // antenna's base

			glTranslatef(0,0,hAnt);
			glutSolidSphere(rTopAnt, SLICES, STACKS); // antenna's top
		glPopMatrix();
	glEndList();
}


void makeEyes()
{
	double plan1[4] = {-1.0, 0.0, 0.0, 0.0};
	double inner = 0.23, outer=0.25, height=0.8;
	double depth=0.19, posi=0.29;
	int i;

	GLUquadricObj* qobj = gluNewQuadric(); // allocation of a quadric description
	gluQuadricDrawStyle(qobj, GLU_FILL); // quadric is filled
	gluQuadricNormals(qobj, GLU_SMOOTH); // shadowings are smooth

	glNewList(EYES,GL_COMPILE);
		glPushMatrix();

			glColor3f(LIGHT_GRAY);

			glTranslatef(-posi, -height, 0.95);
			glRotatef(-90, 1,0,0);

			glClipPlane(GL_CLIP_PLANE0, plan1);

			glEnable(GL_CLIP_PLANE0);
			gluCylinder(qobj, outer, outer, height, SLICES, STACKS);
			gluDisk(qobj, inner, outer, SLICES, 1);
			gluCylinder(qobj, inner, inner, height, SLICES, STACKS);

			glColor3f(BLACK);
			glTranslatef(0, 0, depth);
			gluDisk(qobj, 0, inner, SLICES, 1);// partie droite

			glDisable(GL_CLIP_PLANE0);

			glTranslatef(0.07, 0, 0);
			glBegin(GL_POLYGON);
					glVertex3f(-0.04, -0.04, -depth);
					glVertex3f(0.04, -0.04, -depth);
					glVertex3f(0.04, 0.04, -depth);
					glVertex3f(-0.04, 0.04, -depth); // fond au milieu
			glEnd();

			glColor3f(WHITE);
			glutSolidSphere(depth, SLICES, STACKS); // oeil droit

			glTranslatef(0.44, 0, 0); // 0.44 = espacement entre les yeux
			glRotatef(180, 0,0,1);

			glutSolidSphere(depth, SLICES, STACKS); // oeil gauche

			glColor3f(BLACK);
			glBegin(GL_POLYGON);
					glVertex3f(-0.04, -0.04, -depth); //0.04*2 = taille oeil.
					glVertex3f(0.04, -0.04, -depth);
					glVertex3f(0.04, 0.04, -depth);
					glVertex3f(-0.04, 0.04, -depth); // fond au milieu
			glEnd();

			glTranslatef(-0.07, 0, 0);

			glBegin(GL_POLYGON);
					glVertex3f(0, inner, 0);
					glVertex3f(2*posi, inner, 0);
					glVertex3f(2*posi, -inner, 0);
					glVertex3f(0.0, -inner, 0); // fond au milieu
			glEnd();

			glClipPlane(GL_CLIP_PLANE0, plan1);

			glEnable(GL_CLIP_PLANE0);
			gluDisk(qobj, 0, inner, SLICES, STACKS);
			glTranslatef(0, 0, -depth);

			glColor3f(LIGHT_GRAY);
			gluCylinder(qobj, inner, inner, height, SLICES, STACKS);
			gluCylinder(qobj, outer, outer, height, SLICES, STACKS);
			gluDisk(qobj, inner, outer, SLICES, 1); // coté gauche
			glDisable(GL_CLIP_PLANE0);

			for(i=-1;i<=1;i+=2)
			{
				glBegin(GL_POLYGON);
					glVertex3f(0, i*outer, 0);
					glVertex3f(2*posi, i*outer, 0);
					glVertex3f(2*posi, i*outer, height);
					glVertex3f(0.0, i*outer, height);
				glEnd();

				glBegin(GL_POLYGON);
					glVertex3f(0, i*outer, 0);
					glVertex3f(2*posi, i*outer, 0);
					glVertex3f(2*posi, i*inner, 0);
					glVertex3f(0.0, i*inner, 0);
				glEnd();

				glBegin(GL_POLYGON);
					glVertex3f(0, i*inner, 0);
					glVertex3f(2*posi, i*inner, 0);
					glVertex3f(2*posi, i*inner, height);
					glVertex3f(0.0, i*inner, height);
				glEnd(); // milieu
			}

		glPopMatrix();
	glEndList();
}


void makeHand()
{
	float innerHand=0.25, outerHand=0.35, hHand=0.45;
	float nbFinger=3, sFinger=0.2, rFinger=0.13, hFinger=0.3;
	int i;

	GLUquadricObj* qobj = gluNewQuadric(); // allocation of a quadric description
	gluQuadricDrawStyle(qobj, GLU_FILL); // quadric is filled
	gluQuadricNormals(qobj, GLU_SMOOTH); // shadowings are smooth

	glNewList(HAND, GL_COMPILE);
		glPushMatrix();
			glRotatef(180, 1, 0, 0);
			glColor3f(DARK_GRAY);

			gluCylinder(qobj, innerHand, outerHand, hHand, SLICES, STACKS); // hand
			glTranslatef(0,0,hHand);
			gluDisk(qobj, 0, outerHand, SLICES, STACKS); // "palm"

			for(i=0;i<nbFinger;i++)
			{
				glTranslatef(sFinger, 0, 0);
				gluCylinder(qobj, rFinger, rFinger, hFinger, SLICES, STACKS); // finger
				glTranslatef(0, 0, hFinger);
				glutSolidSphere(rFinger, SLICES, STACKS); // finger's top

				glTranslatef(-sFinger, 0, -hFinger);// reinit position
				glRotatef(360/nbFinger, 0, 0, 1);
			}
		glPopMatrix();
	glEndList();
}


void makeFoot()
{
	float rFoot = 0.6, edge=0.1;
	double plan[4] = {0.0, 0.0, 1.0, 0.0};

	GLUquadricObj* qobj = gluNewQuadric(); // allocation of a quadric description
	gluQuadricDrawStyle(qobj, GLU_FILL); // quadric is filled
	gluQuadricNormals(qobj, GLU_SMOOTH); // shadowings are smooth

	glNewList(FOOT, GL_COMPILE);
		glColor3f(DARK_GRAY);
		glTranslatef(0, 0, -(rFoot-edge));
		glClipPlane(GL_CLIP_PLANE0, plan);

		glEnable(GL_CLIP_PLANE0);
			glutSolidSphere(rFoot, SLICES, STACKS);
		glDisable(GL_CLIP_PLANE0);

		gluDisk(qobj, 0, rFoot, SLICES, STACKS); // foot
		glTranslatef(0, 0, rFoot-edge); //reinit Position
	glEndList();
}


void drawLimb(char limb, int nbSlices, float *controlsX, float *controlsY, float *controlsZ)
{
	float olBezX, olBezY, olBezZ;
	float bezX, bezY, bezZ;
	float angleYZ, angleXZ;
	float t, pas = 1.0/(float)nbSlices;
	int n=0;

	GLUquadricObj* qobj = gluNewQuadric(); // allocation of a quadric description
	gluQuadricDrawStyle(qobj, GLU_FILL); // quadric is filled
	gluQuadricNormals(qobj, GLU_SMOOTH); // shadowings are smooth

//*
	glPushMatrix();
		olBezX=Bezier4(controlsX, 0);
		olBezY=Bezier4(controlsY, 0);
		olBezZ=Bezier4(controlsZ, 0); //origin coordinates

		for(t=0+pas;t<1;t+=pas)
		{
			if(n%(nbSlices/10)==2)
				glColor3f(LIGHT_BLACK);
			else
				glColor3f(BLUE_GRAY); // light black every 15th

			glPushMatrix();

				bezX=Bezier4(controlsX, t);
				bezY=Bezier4(controlsY, t);
				bezZ=Bezier4(controlsZ, t);// calculation of the new Bezier coeff

				glTranslatef(olBezX, olBezY, olBezZ); //placing at the end of the precedent cylinder

				angleYZ = (180*atan((bezX-olBezX)/(bezZ-olBezZ)))/PI;
				angleXZ = (180*atan((bezY-olBezY)/(bezZ-olBezZ)))/PI; //calculation of the rotation angle

				if((bezZ-olBezZ)<=0)
					angleYZ+=180;
				if((bezZ-olBezZ)<=0)
					angleXZ+=180;

				glRotatef(angleYZ, 0, 1, 0); //(bezZ-olBezZ)>0? angleYZ : 180+angleYZ, 0,1,0);
				glRotatef(angleXZ, 1, 0, 0);//(bezZ-olBezZ)>0? angleXZ : 90+angleXZ, -1,0,0);

				gluCylinder(qobj, 0.25, 0.25, sqrt((bezX-olBezX)*(bezX-olBezX)+(bezZ-olBezZ)*(bezZ-olBezZ)+(bezY-olBezY)*(bezY-olBezY)), SLICES, STACKS);
				// new cylinder : lenght = square root of new coordinates - old one.
			glPopMatrix();

			n++;
			olBezX=bezX;
			olBezY=bezY;
			olBezZ=bezZ; // keeping old coeffs
		}

		glTranslatef(olBezX, olBezY, olBezZ);

		if(limb == 'h') //if it's a hand, same rotation than the last cylinder, and calling the HAND list
		{
			glRotatef(angleYZ, 0, 1, 0);
			glRotatef(angleXZ, 1, 0, 0);
			glCallList(HAND);
		}
		else if(limb == 'f') // if it's a foot, no rotation and calling the FOOT list
			glCallList(FOOT);

	glPopMatrix();
//*/

	/* ------------------------------------------ DEBUG -----------------------------------------------------
		// draw the curve from wich the cylinder are extruded
		glBegin(GL_LINE_STRIP);
		glColor3f(0, 1, 1);
		for(t=0;t<=1;t+=pas)
		{
			glVertex3f(Bezier4(controlsX, t), Bezier4(controlsY, t), Bezier4(controlsZ, t));
		}
		glEnd();
		glColor3f(1, 1, 0);

		for(n=0;n<4;n++)
		{
			glBegin(GL_LINE_STRIP);
				glVertex3f(controlsX[n],  controlsY[n] + 0.1 , controlsZ[n] );
				glVertex3f(controlsX[n],  controlsY[n] - 0.1 , controlsZ[n] );
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3f(controlsX[n],  controlsY[n] , controlsZ[n] + 0.1 );
				glVertex3f(controlsX[n], controlsY[n] , controlsZ[n] - 0.1 );
			glEnd();
		}

	// -------------------------------------------------------------------------------------------------------*/
}
