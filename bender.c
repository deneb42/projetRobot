#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.1415926535898


float Bezier4 ( float coor[4] , float t );
void makeHand();
void drawMembre(char part, float *controlesX, float *controlesY, float *controlesZ);


float jambesX[4] = { 0.0, -0.1, -0.15, -0.2 };
float jambesY[4] = { 0.0, 0.0, 0.0, 0.0 };
float jambesZ[4] = { -0.01, 1.0, 2.0, 3.0 };

float brasX[4] = { 0.0, -1.0, -2.0, -2.5 };
float brasZ[4] = { 0.0, 1.0, 1.1, 1.2 };
float brasY[4] = { 0.0, 0.0, -0.1, -0.15 };

float pas;

void createBender()
{
	GLUquadricObj* qobj;
	//GLUquadricObj* GLAPIENTRY qobj;
	int i;

	// allocation d´une description de quadrique
	qobj = gluNewQuadric();
	// la quadrique est pleine
	gluQuadricDrawStyle(qobj, GLU_FILL);
	// les ombrages, s´il y en a, sont doux
	gluQuadricNormals(qobj, GLU_SMOOTH);


	glNewList(2, GL_COMPILE); // declaration de la liste Bender

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


			// ------------------ yeux -----------------------------
			glPushMatrix();
				double plan1[4] = {-1.0, 0.0, 0.0, 0.0};

				glColor3f(0.84, 0.9, 0.95);
				glTranslatef(-0.29, -0.8, 0.95);
				glRotatef(-90, 1,0,0);

				glClipPlane(GL_CLIP_PLANE0, plan1);

				glEnable(GL_CLIP_PLANE0);
				gluCylinder(qobj, 0.25, 0.25, 0.8, 20, 20);
				gluDisk(qobj, 0.23, 0.25, 20, 1);
				gluCylinder(qobj, 0.23, 0.23, 0.8, 20, 20);

				glColor3f(0.04, 0.05, 0.05);
				glTranslatef(0, 0, 0.19);
				gluDisk(qobj, 0, 0.23, 20, 1);// partie droite

				glDisable(GL_CLIP_PLANE0);

				glTranslatef(0.07, 0, 0);
				glBegin(GL_POLYGON);
						glVertex3f(-0.04, -0.04, -0.19);
						glVertex3f(0.04, -0.04, -0.19);
						glVertex3f(0.04, 0.04, -0.19);
						glVertex3f(-0.04, 0.04, -0.19); // fond au milieu
				glEnd();

				glColor3f(0.99, 0.99, 0.82);
				glutSolidSphere(0.19, 20, 20); // oeil droit

				glTranslatef(0.44, 0, 0);
				glRotatef(180, 0,0,1);

				glutSolidSphere(0.19, 20, 20); // oeil gauche

				glColor3f(0.04, 0.05, 0.05);
				glBegin(GL_POLYGON);
						glVertex3f(-0.04, -0.04, -0.19);
						glVertex3f(0.04, -0.04, -0.19);
						glVertex3f(0.04, 0.04, -0.19);
						glVertex3f(-0.04, 0.04, -0.19); // fond au milieu
				glEnd();

				glTranslatef(-0.07, 0, 0);

				glBegin(GL_POLYGON);
						glVertex3f(0, 0.23, 0);
						glVertex3f(0.58, 0.23, 0);
						glVertex3f(0.58, -0.23, 0);
						glVertex3f(0.0, -0.23, 0); // fond au milieu
				glEnd();

				glClipPlane(GL_CLIP_PLANE0, plan1);

				glEnable(GL_CLIP_PLANE0);
				gluDisk(qobj, 0, 0.23, 20, 1);
				glTranslatef(0, 0, -0.19);
				glColor3f(0.84, 0.9, 0.95);
				gluCylinder(qobj, 0.23, 0.23, 0.8, 20, 20);
				gluCylinder(qobj, 0.25, 0.25, 0.8, 20, 20);
				gluDisk(qobj, 0.23, 0.25, 20, 1); // coté gauche
				glDisable(GL_CLIP_PLANE0);

				for(i=-1;i<=1;i+=2)
				{
					glBegin(GL_POLYGON);
						glVertex3f(0, i*0.25, 0);
						glVertex3f(0.58, i*0.25, 0);
						glVertex3f(0.58, i*0.25, 0.8);
						glVertex3f(0.0, i*0.25, 0.8);
					glEnd();

					glBegin(GL_POLYGON);
						glVertex3f(0, i*0.25, 0);
						glVertex3f(0.58, i*0.25, 0);
						glVertex3f(0.58, i*0.23, 0);
						glVertex3f(0.0, i*0.23, 0);
					glEnd();

					glBegin(GL_POLYGON);
						glVertex3f(0, i*0.23, 0);
						glVertex3f(0.58, i*0.23, 0);
						glVertex3f(0.58, i*0.23, 0.8);
						glVertex3f(0.0, i*0.23, 0.8);
					glEnd(); // milieu
				}

			glPopMatrix();

			// ---------------------------------------------------------------

			glColor3f(0.74, 0.8, 0.87);
			glTranslatef(0,0,1.2);
			glutSolidSphere(0.6, 20, 20); // haut de la tete

			glColor3f(0.6,0.69,0.78);
			glTranslatef(0,0,0.6);
			gluCylinder(qobj, 0.05, 0.02, 0.5, 20, 20); // antenne

			glColor3f(0.84, 0.9, 0.95);
			glutSolidSphere(0.1, 20, 20); // base de l'antenne

			//glColor3f(1,0,1);
			glTranslatef(0,0,0.5);
			glutSolidSphere(0.06, 20, 20); // boule de l'antenne

			glPushMatrix();

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
				}
			glPopMatrix();

			glPushMatrix();
				//glColor3f(1, 0.25, 0.5);
				glTranslatef(-1.1, 0, -3.3);
				glutSolidSphere(0.35, 20, 20); // epaule droite

				//makeHand();

				glRotatef(-90, 0, 1,0);
				drawMembre('h', brasX, brasY, brasZ); // bras droit

				glColor3f(0.74, 0.8, 0.87);
				glTranslatef(0, 0, -2.2);
				glutSolidSphere(0.35, 20, 20); // epaule gauche

				//makeHand(); // main gauche

				glRotatef(180, 1, 0,0);
				drawMembre('h', brasX, brasY, brasZ); // bras gauche
			glPopMatrix();


		/*reste :

			- Integrer le pied ou la main a drawMembre

			- tete
				-bouche
		*/

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


}

void drawMembre(char part, float *controlesX, float *controlesY, float *controlesZ)
{
	float olBezX, olBezY, olBezZ;
	float bezX, bezY, bezZ;
	float tmp, TMP;
	float t;
	int n;

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);


	glPushMatrix();
		//glColor3f(1,1,0);
		//glRotatef(180, 1,0,0);

		pas = 0.01;
		n=0;

		olBezX=Bezier4(controlesX, 0);
		olBezY=Bezier4(controlesY, 0);
		olBezZ=Bezier4(controlesZ, 0);

		for(t=0+pas;t<1;t+=pas)
		{
			if(n%15==2)
				glColor3f(0.4,0.5,0.5);
			else
				glColor3f(0.6,0.69,0.78);

			glPushMatrix();

				bezX=Bezier4(controlesX, t);
				bezY=Bezier4(controlesY, t);
				bezZ=Bezier4(controlesZ, t);

				tmp = (180*atan((bezX-olBezX)/(bezZ-olBezZ)))/PI;
				TMP = (180*atan((bezY-olBezY)/(bezZ-olBezZ)))/PI;

				glTranslatef(olBezX, olBezY, olBezZ);

				glRotatef((bezZ-olBezZ)>0? tmp : 180+tmp, 0,1,0);
				glRotatef((bezZ-olBezZ)>0? TMP : 90+TMP, -1,0,0);

				gluCylinder(qobj, 0.25, 0.25, sqrt((bezX-olBezX)*(bezX-olBezX)+(bezZ-olBezZ)*(bezZ-olBezZ)+(bezY-olBezY)*(bezY-olBezY)), 20, 20);

				if(part == 'h' && t>1-2*pas)
				{
					glTranslatef(bezX-olBezX, bezY-olBezY, bezZ-olBezZ);
					makeHand();
				}

			glPopMatrix();

			n++;
			olBezX=bezX;
			olBezY=bezY;
			olBezZ=bezZ;
		}
/*
		if(part == 'h') // si on a affaire a une main
		{
			/*glPushMatrix();

				bezX=Bezier4(controlesX, 1);
				bezY=Bezier4(controlesY, 1);
				bezZ=Bezier4(controlesZ, 1);

				tmp = (180*atan((bezX-olBezX)/(bezZ-olBezZ)))/PI;
				TMP = (180*atan((bezY-olBezY)/(bezZ-olBezZ)))/PI;

				glTranslatef(olBezX, olBezY, olBezZ);

				glRotatef((bezZ-olBezZ)>0? tmp : 180+tmp, 0,1,0);
				glRotatef((bezZ-olBezZ)>0? TMP : 90+TMP, -1,0,0);

				//gluCylinder(qobj, 0.25, 0.25, sqrt((bezX-olBezX)*(bezX-olBezX)+(bezZ-olBezZ)*(bezZ-olBezZ)+(bezY-olBezY)*(bezY-olBezY)), 20, 20);*

				glTranslatef(bezX, bezY, bezZ);

				glRotatef((bezZ-olBezZ)>0? tmp : 180+tmp, 0,1,0);
				glRotatef((bezZ-olBezZ)>0? TMP : 90+TMP, -1,0,0);
				makeHand();

			//glPopMatrix();
		}*/

	/* ------------------------------------------ DEBUG -----------------------------------------------------
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
