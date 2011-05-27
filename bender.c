#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.1415926535898
#define BENDER 2


float Bezier4 ( float coor[4] , float t );
void makeHand(); // BENDER+1
void makeEyes(); // BENDER+2
void drawMembre(char part, float *controlesX, float *controlesY, float *controlesZ);


float jambesX[2][4] = {{ 0.0, -0.1, -0.15, -0.2 }, { 0.0, -0.1, -0.15, -0.2 }};
float jambesY[2][4] = {{ 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0 }};
float jambesZ[2][4] = {{ -0.01, 1.0, 2.0, 3.0 }, { -0.01, 1.0, 2.0, 3.0 }};

float brasX[2][4] = {{ 0.0, -1.0, -2.0, -2.5 }, { 0.0, 1.0, 2.0, 2.5 }};
float brasY[2][4] = {{ 0.0, 0.0, -0.1, -0.15 },{ 0.0, 0.0, -0.1, -0.15 }};
float brasZ[2][4] = {{ 0.0, 1.0, 1.1, 1.2 }, { 0.0, 1.0, 1.1, 1.2 }};

void createBender()
{
	GLUquadricObj* qobj;
	//GLUquadricObj* GLAPIENTRY qobj;
	int i;

	qobj = gluNewQuadric(); // allocation d´une description de quadrique
	gluQuadricDrawStyle(qobj, GLU_FILL); // la quadrique est pleine
	gluQuadricNormals(qobj, GLU_SMOOTH); // les ombrages, s´il y en a, sont doux

	makeHand();
	makeEyes();

	glNewList(BENDER, GL_COMPILE); // declaration de la liste Bender

		glPushMatrix();
			glRotatef(-90, 1, 0,0);
			glColor3f(0.74, 0.8, 0.87);
			gluCylinder(qobj, 1, 1.25, 2.8, 20, 20); // corps

			gluDisk(qobj, 0, 1, 20, 1); // fesses

			glColor3f(0.84, 0.9, 0.95);
			glTranslatef(0,0,2.8);
			gluCylinder(qobj, 1.25, 0.6, 0.5, 20, 20); // epaules

			glColor3f(0.74, 0.8, 0.87);
			glTranslatef(0,0,0.5);
			gluCylinder(qobj, 0.6, 0.6, 1.2, 20, 20); // tete

			glCallList(BENDER+2);

			glColor3f(0.74, 0.8, 0.87);
			glTranslatef(0,0,1.2);
			glutSolidSphere(0.6, 20, 20); // haut de la tete

			glColor3f(0.6,0.69,0.78);
			glTranslatef(0,0,0.6);
			gluCylinder(qobj, 0.05, 0.02, 0.5, 20, 20); // antenne

			glColor3f(0.84, 0.9, 0.95);
			glutSolidSphere(0.1, 20, 20); // base de l'antenne

			glTranslatef(0,0,0.5);
			glutSolidSphere(0.06, 20, 20); // boule de l'antenne

			glPushMatrix();
/*
				glRotatef(180, 1, 0,0);
				glTranslatef(-0.5,0,5.6);
				drawMembre(' ', jambesX, jambesY, jambesZ);

				glTranslatef(1,0,0);
				glRotatef(180, 0, 0,1);
				drawMembre(' ', jambesX, jambesY, jambesZ);

				glRotatef(180, 1, 0,0);
				glTranslatef(jambesX[3],jambesY[3],-jambesZ[3]-0.5);
				{
					double plan[4] = {0.0, 0.0, 1.0, 0.0};

					glClipPlane(GL_CLIP_PLANE0, plan);
					glEnable(GL_CLIP_PLANE0);

					glColor3f(0.74, 0.8, 0.87);
					glutSolidSphere(0.6, 20, 20);
					//glColor3f(0.25, 0.5, 0.25);
					glDisable(GL_CLIP_PLANE0);
					gluDisk(qobj, 0, 0.6, 20, 1); // pied gauche

					glTranslatef(1 -2*jambesX[3],0,0);

					glEnable(GL_CLIP_PLANE0);

					//glColor3f(0.5, 0.25, 0.25);
					glutSolidSphere(0.6, 20, 20);
					//glColor3f(0.25, 0.5, 0.25);
					glDisable(GL_CLIP_PLANE0);
					gluDisk(qobj, 0, 0.6, 20, 1); // pied droit
				}*/
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0, 0, -3.3); // on se place a la bonne hauteur

				for(i=-1;i<=1;i+=2)
				{
					glPushMatrix();
						glColor3f(0.74, 0.8, 0.87);

						glTranslatef(i*1.1, 0, 0); // puis du bon coté a la sortie du cylindre corps
						glutSolidSphere(0.35, 20, 20); // epaule
						glRotatef(i*90, 0, 1,0);
						drawMembre('h', brasX[i<0?i+1:i], brasY[i<0?i+1:i], brasZ[i<0?i+1:i]); // bras

					glPopMatrix();
				}
			glPopMatrix();
		glPopMatrix();
	glEndList();
}


float Bezier4 ( float coor[4] , float t ) {
	return coor[0]*(1-t)*(1-t)*(1-t) + 3*coor[1]*t*(1-t)*(1-t) + 3*coor[2]*t*t*(1-t) + coor[3]*t*t*t;
}


void makeHand()
{
	int i;

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);

	glNewList(BENDER+1, GL_COMPILE);
		glPushMatrix();
			glColor3f(0.74, 0.8, 0.87);

			gluCylinder(qobj, 0.25, 0.35, 0.45, 20, 20); // main
			glTranslatef(0,0,0.45);
			gluDisk(qobj, 0, 0.35, 20, 1); // "paume"

			for(i=0;i<3;i++)
			{
				glTranslatef(0.2, 0, 0);
				gluCylinder(qobj, 0.13, 0.13, 0.3, 20, 20); // doigt
				glTranslatef(0, 0, 0.3);
				glutSolidSphere(0.13, 20, 20); // bout du doigt

				glTranslatef(-0.2, 0, -0.3);
				glRotatef(120, 0, 0, 1);
			}

		glPopMatrix();
	glEndList();
}

void makeEyes()
{
	double plan1[4] = {-1.0, 0.0, 0.0, 0.0};
	double inner = 0.23, outer=0.25, height=0.8;
	double depth=0.19, posi=0.29;
	int i;

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);

	glNewList(BENDER+2,GL_COMPILE);
		glPushMatrix();

			glColor3f(0.84, 0.9, 0.95);

			glTranslatef(-posi, -height, 0.95);
			glRotatef(-90, 1,0,0);

			glClipPlane(GL_CLIP_PLANE0, plan1);

			glEnable(GL_CLIP_PLANE0);
			gluCylinder(qobj, outer, outer, height, 20, 20);
			gluDisk(qobj, inner, outer, 20, 1);
			gluCylinder(qobj, inner, inner, height, 20, 20);

			glColor3f(0.04, 0.05, 0.05);
			glTranslatef(0, 0, depth);
			gluDisk(qobj, 0, inner, 20, 1);// partie droite

			glDisable(GL_CLIP_PLANE0);

			glTranslatef(0.07, 0, 0);
			glBegin(GL_POLYGON);
					glVertex3f(-0.04, -0.04, -depth);
					glVertex3f(0.04, -0.04, -depth);
					glVertex3f(0.04, 0.04, -depth);
					glVertex3f(-0.04, 0.04, -depth); // fond au milieu
			glEnd();

			glColor3f(0.99, 0.99, 0.82);
			glutSolidSphere(depth, 20, 20); // oeil droit

			glTranslatef(0.44, 0, 0); // 0.44 = espacement entre les yeux
			glRotatef(180, 0,0,1);

			glutSolidSphere(depth, 20, 20); // oeil gauche

			glColor3f(0.04, 0.05, 0.05);
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
			gluDisk(qobj, 0, inner, 20, 20);
			glTranslatef(0, 0, -depth);

			glColor3f(0.84, 0.9, 0.95);
			gluCylinder(qobj, inner, inner, height, 20, 20);
			gluCylinder(qobj, outer, outer, height, 20, 20);
			gluDisk(qobj, inner, outer, 20, 1); // coté gauche
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

void drawMembre(char part, float *controlesX, float *controlesY, float *controlesZ)
{
	float olBezX, olBezY, olBezZ;
	float bezX, bezY, bezZ;
	float angleYZ, angleXZ;
	float t, pas = 0.01;
	int n=0;

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);


	glPushMatrix();
		olBezX=Bezier4(controlesX, 0);
		olBezY=Bezier4(controlesY, 0);
		olBezZ=Bezier4(controlesZ, 0); //coords de base

		for(t=0+pas;t<1;t+=pas)
		{
			if(n%15==2)
				glColor3f(0.4,0.5,0.5);
			else
				glColor3f(0.6,0.69,0.78); // application de la couleut (1/15 a gris foncé)

			glPushMatrix();

				bezX=Bezier4(controlesX, t);
				bezY=Bezier4(controlesY, t);
				bezZ=Bezier4(controlesZ, t);// calcul des nouveau coeff de Bezier

				angleYZ = (180*atan((bezX-olBezX)/(bezZ-olBezZ)))/PI;
				angleXZ = (180*atan((bezY-olBezY)/(bezZ-olBezZ)))/PI; //calcul de l'angle de rotation

				glTranslatef(olBezX, olBezY, olBezZ); // on se place a la fin du cylindre prec

				glRotatef((bezZ-olBezZ)>0? angleYZ : 180+angleYZ, 0,1,0);
				glRotatef((bezZ-olBezZ)>0? angleXZ : 90+angleXZ, -1,0,0);

				gluCylinder(qobj, 0.25, 0.25, sqrt((bezX-olBezX)*(bezX-olBezX)+(bezZ-olBezZ)*(bezZ-olBezZ)+(bezY-olBezY)*(bezY-olBezY)), 20, 20);
				// nouveau cylindre : longueur racine carré des coords de fin.

				if(part == 'h' && t>1-2*pas) // si on dessine une main on garde le dernier coeff de bezier et on dessine la main
				{
					glTranslatef(bezX-olBezX, bezY-olBezY, bezZ-olBezZ);
					glCallList(BENDER+1);
				}

			glPopMatrix();

			n++;
			olBezX=bezX;
			olBezY=bezY;
			olBezZ=bezZ; // on garde les anciens coeffs.
		}

	/* ------------------------------------------ DEBUG -----------------------------------------------------
		// affiche la courbe de bezier a l'origine du bras
		glBegin(GL_LINE_STRIP);
		glColor3f(0, 1, 1);
		for(t=0;t<=1;t+=pas)
		{
			glVertex3f(Bezier4(controlesX, t), Bezier4(controlesY, t), Bezier4(controlesZ, t));
		}
		glEnd();
	// -------------------------------------------------------------------------------------------------------*/

	glPopMatrix();
}
