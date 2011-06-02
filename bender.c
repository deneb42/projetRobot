#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>

//utils
#define PI 3.1415926535898
#define SLICES 20
#define STACKS 20

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
void makeBody();
void makeEyes();
void makeHand();
void makeFoot();
void drawLimb(char limb, float *controlsX, float *controlsY, float *controlsZ);


float legX[2][4] = {{ 0.0, -0.1, -0.15, -0.2 }, { 0.0, 0.1, 0.15, 0.2 }};
float legY[2][4] = {{ 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0 }};
float legZ[2][4] = {{ -0.01, -1.0, -2.0, -3.0 }, { -0.01, -1.0, -2.0, -3.0 }}; //control points for legs

float armX[2][4] = {{ 0.0, -1.0, -1.1, -1.2 }, { 0.0, 1.0, 1.1, 1.2 }};
float armY[2][4] = {{ 0.0, 0.0, -0.1, -0.15 },{ 0.0, 0.0, -0.1, -0.15 }};
float armZ[2][4] = {{ 0.0, -1.0, -2.0, -2.5 }, { 0.0, -1.0, -2.0, -2.5 }}; // control points for arms
//0 is right, 1 is left


void drawBender()
{
	int i, paddingLeg=0.5, heightShoulder=2.2, paddingShoulder=1.1, rShoulder=0.35;
	
	
	GLUquadricObj* qobj = gluNewQuadric(); // allocation of a quadric description
	gluQuadricDrawStyle(qobj, GLU_FILL); // quadric is filled
	gluQuadricNormals(qobj, GLU_SMOOTH); // shadowings are smooth


	glCallList(BENDER);

	glPushMatrix();
		glTranslatef(-paddingLeg,0,0);
		drawLimb('f', legX[0], legY[0], legZ[0]); //right

		glTranslatef(2*paddingLeg,0,0);
		drawLimb('f', legX[1], legY[1], legZ[1]); // left


		glTranslatef(-paddingLeg, 0, heightShoulder); // placing at shoulder's height
		
		for(i=0;i<2;i++)
		{
			glPushMatrix();
				glColor3f(DARK_GRAY);
				glTranslatef(((i*2)-1)*paddingShoulder, 0, 0); // then placing to the good side of the body, (i*2)-1 gives -1 then 1

				glutSolidSphere(rShoulder, SLICES, STACKS); // drawing shoulder
				drawLimb('h', armX[i], armY[i], armZ[i]); // arm
			glPopMatrix();
		}
	glPopMatrix();
}


float Bezier4 ( float coor[4] , float t ) {
	return coor[0]*(1-t)*(1-t)*(1-t) + 3*coor[1]*t*(1-t)*(1-t) + 3*coor[2]*t*t*(1-t) + coor[3]*t*t*t;
}


void makeBender()
{
	makeBody();
	makeEyes();
	makeHand();
	makeFoot(); // calling all the lists declarations
}


void makeBody()
{
	GLUquadricObj* qobj = gluNewQuadric(); // allocation of a quadric description
	gluQuadricDrawStyle(qobj, GLU_FILL); // quadric is filled
	gluQuadricNormals(qobj, GLU_SMOOTH); // shadowings are smooth

	glNewList(BENDER, GL_COMPILE); // declaration de la liste Bender
		glPushMatrix();
			glColor3f(DARK_GRAY);
			gluCylinder(qobj, 1, 1.25, 2.8, 20, 20); // corps

			gluDisk(qobj, 0, 1, 20, 1); // fesses

			glColor3f(LIGHT_GRAY);
			glTranslatef(0,0,2.8);
			gluCylinder(qobj, 1.25, 0.6, 0.5, 20, 20); // epaules

			glColor3f(DARK_GRAY);
			glTranslatef(0,0,0.5);
			gluCylinder(qobj, 0.6, 0.6, 1.2, 20, 20); // tete

			glCallList(EYES);

			glColor3f(DARK_GRAY);
			glTranslatef(0,0,1.2);
			glutSolidSphere(0.6, 20, 20); // haut de la tete

			glColor3f(BLUE_GRAY);
			glTranslatef(0,0,0.6);
			gluCylinder(qobj, 0.05, 0.02, 0.5, 20, 20); // antenne

			glColor3f(LIGHT_GRAY);
			glutSolidSphere(0.1, 20, 20); // base de l'antenne

			glTranslatef(0,0,0.5);
			glutSolidSphere(0.06, 20, 20); // boule de l'antenne
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
			gluCylinder(qobj, outer, outer, height, 20, 20);
			gluDisk(qobj, inner, outer, 20, 1);
			gluCylinder(qobj, inner, inner, height, 20, 20);

			glColor3f(BLACK);
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

			glColor3f(WHITE);
			glutSolidSphere(depth, 20, 20); // oeil droit

			glTranslatef(0.44, 0, 0); // 0.44 = espacement entre les yeux
			glRotatef(180, 0,0,1);

			glutSolidSphere(depth, 20, 20); // oeil gauche

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
			gluDisk(qobj, 0, inner, 20, 20);
			glTranslatef(0, 0, -depth);

			glColor3f(LIGHT_GRAY);
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


void makeHand()
{
	int i;

	GLUquadricObj* qobj = gluNewQuadric(); // allocation of a quadric description
	gluQuadricDrawStyle(qobj, GLU_FILL); // quadric is filled
	gluQuadricNormals(qobj, GLU_SMOOTH); // shadowings are smooth

	glNewList(HAND, GL_COMPILE);
		glPushMatrix();
			glColor3f(DARK_GRAY);

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


void makeFoot()
{
	double plan[4] = {0.0, 0.0, 1.0, 0.0};

	GLUquadricObj* qobj = gluNewQuadric(); // allocation of a quadric description
	gluQuadricDrawStyle(qobj, GLU_FILL); // quadric is filled
	gluQuadricNormals(qobj, GLU_SMOOTH); // shadowings are smooth

	glNewList(FOOT, GL_COMPILE);
		glTranslatef(0, 0, -0.5);
		glClipPlane(GL_CLIP_PLANE0, plan);
		glEnable(GL_CLIP_PLANE0);
		
		glColor3f(DARK_GRAY);
		glutSolidSphere(0.6, 20, 20);
		glDisable(GL_CLIP_PLANE0);
		gluDisk(qobj, 0, 0.6, 20, 1); // pied gauche
		glTranslatef(0, 0, 0.5);
	glEndList();
}


void drawLimb(char limb, float *controlsX, float *controlsY, float *controlsZ)
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
		olBezX=Bezier4(controlsX, 0);
		olBezY=Bezier4(controlsY, 0);
		olBezZ=Bezier4(controlsZ, 0); //coords de base

		for(t=0+pas;t<1;t+=pas)
		{
			if(n%15==2)
				glColor3f(LIGHT_BLACK);
			else
				glColor3f(BLUE_GRAY); // application de la couleut (1/15 a gris foncé)

			glPushMatrix();

				bezX=Bezier4(controlsX, t);
				bezY=Bezier4(controlsY, t);
				bezZ=Bezier4(controlsZ, t);// calcul des nouveau coeff de Bezier

				angleYZ = (180*atan((bezX-olBezX)/(bezZ-olBezZ)))/PI;
				angleXZ = (180*atan((bezY-olBezY)/(bezZ-olBezZ)))/PI; //calcul de l'angle de rotation

				glTranslatef(olBezX, olBezY, olBezZ); // on se place a la fin du cylindre prec

				glRotatef((bezZ-olBezZ)>0? angleYZ : 180+angleYZ, 0,1,0);
				glRotatef(angleXZ, 1, 0, 0);//(bezZ-olBezZ)>0? angleXZ : 90+angleXZ, -1,0,0);

				gluCylinder(qobj, 0.25, 0.25, sqrt((bezX-olBezX)*(bezX-olBezX)+(bezZ-olBezZ)*(bezZ-olBezZ)+(bezY-olBezY)*(bezY-olBezY)), 20, 20);
				// nouveau cylindre : longueur racine carré des coords de fin.

				if(t>1-pas && limb == 'h') // si on dessine une main on garde le dernier coeff de bezier et on dessine la main
				{
					glTranslatef(bezX-olBezX, bezY-olBezY, bezZ-olBezZ);
					glCallList(HAND);
				}

			glPopMatrix();

			n++;
			olBezX=bezX;
			olBezY=bezY;
			olBezZ=bezZ; // on garde les anciens coeffs.
		}
		
		if(limb == 'f') // si on dessine une main on garde le dernier coeff de bezier et on dessine la main
		{
			glTranslatef(olBezX, olBezY, olBezZ);
			glCallList(FOOT);
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
