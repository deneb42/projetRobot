#include "city.h"
#include "global.h"


//Loader de textures
void load_textures(char *chemin, int *texId) {
	int i;

	char texName[14][20] = {"mars2.bmp", "mur1.bmp", "mur1.bmp", "mur1.bmp", "mur1.bmp", "mur1.bmp", "mur1.bmp",
						"cyl10.bmp", "cyl11.bmp", "cyl12.bmp", "cyl13.bmp", "cyl14.bmp", "eau2.bmp", "skybox.bmp"};

	for(i=0;i<14;i++)
		loadTexture(chemin, texName[i],  &texId[i]);
}

void makeSky(int tex)
{
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



void createCity(char *chemin)
{
	int texId[14]; //A créer en même temps que toutes les variables. La taille depend du nombre de textures

	GLUquadricObj* qobj;
	//GLUquadricObj* GLAPIENTRY qobj;

	// allocation d´une description de quadrique
	qobj = gluNewQuadric();
	// la quadrique est pleine
	gluQuadricDrawStyle(qobj, GLU_FILL);
	// les ombrages, s´il y en a, sont doux
	gluQuadricNormals(qobj, GLU_SMOOTH);

	load_textures(chemin, texId);

	makeSky(texId[13]);

    //sol
    glNewList(11, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texId[0]);

    glColor3f (1,1,1);
    glPushMatrix();
    glBegin(GL_POLYGON);
    glTexCoord2i(1,1);		glVertex3f(150,150,0);
    glTexCoord2i(1,0);		glVertex3f(150,-150,0);
    glTexCoord2i(0,0);		glVertex3f(-150,-150,0);
    glTexCoord2i(0,1);      glVertex3f(-150,150,0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glEndList();



    //batiment 1

    glNewList(12, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texId[1]);

    glPushMatrix();
    glTranslatef(20,20,0);

    glBegin(GL_QUADS);

    //4 faces latrales
    glTexCoord2i(0,0); glVertex3d(10,10,60);
    glTexCoord2i(0,4); glVertex3d(10,10,0);
    glTexCoord2i(4,4); glVertex3d(0,10,0);
    glTexCoord2i(4,0); glVertex3d(0,10,60);

    glTexCoord2i(0,0); glVertex3d(10,0,60);
    glTexCoord2i(0,4); glVertex3d(10,0,0);
    glTexCoord2i(4,4); glVertex3d(10,10,0);
    glTexCoord2i(4,0); glVertex3d(10,10,60);

    glTexCoord2i(0,0); glVertex3d(0,0,60);
    glTexCoord2i(0,4); glVertex3d(0,0,0);
    glTexCoord2i(4,4); glVertex3d(10,0,0);
    glTexCoord2i(4,0); glVertex3d(10,0,60);

    glTexCoord2i(0,0); glVertex3d(0,10,60);
    glTexCoord2i(0,4); glVertex3d(0,10,0);
    glTexCoord2i(4,4); glVertex3d(0,0,0);
    glTexCoord2i(4,0); glVertex3d(0,0,60);

    //sol
    glTexCoord2i(0,0); glVertex3d(10,10,0);
    glTexCoord2i(0,4); glVertex3d(10,0,0);
    glTexCoord2i(4,4); glVertex3d(0,0,0);
    glTexCoord2i(4,0); glVertex3d(0,10,0);

    //toit
    glTexCoord2i(0,0); glVertex3d(10,0,60);
    glTexCoord2i(0,4); glVertex3d(10,10,60);
    glTexCoord2i(4,4); glVertex3d(0,10,60);
    glTexCoord2i(4,0); glVertex3d(0,0,60);

    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glEndList();



    //batiment 2

    glNewList(13, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texId[2]);

    glPushMatrix();
    glTranslatef(30,-90,0);

    glBegin(GL_QUADS);

    //4 faces latrales
    glTexCoord2i(0,0); glVertex3d(15,15,90);
    glTexCoord2i(0,1); glVertex3d(15,15,0);
    glTexCoord2i(1,1); glVertex3d(0,15,0);
    glTexCoord2i(1,0); glVertex3d(0,15,90);

    glTexCoord2i(0,0); glVertex3d(15,0,90);
    glTexCoord2i(0,1); glVertex3d(15,0,0);
    glTexCoord2i(1,1); glVertex3d(15,15,0);
    glTexCoord2i(1,0); glVertex3d(15,15,90);

    glTexCoord2i(0,0); glVertex3d(0,0,90);
    glTexCoord2i(0,1); glVertex3d(0,0,0);
    glTexCoord2i(1,1); glVertex3d(15,0,0);
    glTexCoord2i(1,0); glVertex3d(15,0,90);

    glTexCoord2i(0,0); glVertex3d(0,15,90);
    glTexCoord2i(0,1); glVertex3d(0,15,0);
    glTexCoord2i(1,1); glVertex3d(0,0,0);
    glTexCoord2i(1,0); glVertex3d(0,0,90);

    //sol
    glTexCoord2i(0,0); glVertex3d(15,15,0);
    glTexCoord2i(0,1); glVertex3d(15,0,0);
    glTexCoord2i(1,1); glVertex3d(0,0,0);
    glTexCoord2i(1,0); glVertex3d(0,15,0);

    //toit
    glTexCoord2i(0,0); glVertex3d(15,0,90);
    glTexCoord2i(0,1); glVertex3d(15,15,90);
    glTexCoord2i(1,1); glVertex3d(0,15,90);
    glTexCoord2i(1,0); glVertex3d(0,0,90);

    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glEndList();



    //batiment3

    glNewList(14,GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texId[3]);

    glPushMatrix();
    glTranslatef(60,80,0);

    glBegin(GL_QUADS);

    //4 faces latrales
    glTexCoord2i(0,0); glVertex3d(30,30,10);
    glTexCoord2i(0,1); glVertex3d(30,30,0);
    glTexCoord2i(1,1); glVertex3d(0,30,0);
    glTexCoord2i(1,0); glVertex3d(0,30,10);

    glTexCoord2i(0,0); glVertex3d(30,0,10);
    glTexCoord2i(0,1); glVertex3d(30,0,0);
    glTexCoord2i(1,1); glVertex3d(30,30,0);
    glTexCoord2i(1,0); glVertex3d(30,30,10);

    glTexCoord2i(0,0); glVertex3d(0,0,10);
    glTexCoord2i(0,1); glVertex3d(0,0,0);
    glTexCoord2i(1,1); glVertex3d(30,0,0);
    glTexCoord2i(1,0); glVertex3d(30,0,10);

    glTexCoord2i(0,0); glVertex3d(0,30,10);
    glTexCoord2i(0,1); glVertex3d(0,30,0);
    glTexCoord2i(1,1); glVertex3d(0,0,0);
    glTexCoord2i(1,0); glVertex3d(0,0,10);

    //sol
    glTexCoord2i(0,0); glVertex3d(30,30,0);
    glTexCoord2i(0,1); glVertex3d(30,0,0);
    glTexCoord2i(1,1); glVertex3d(0,0,0);
    glTexCoord2i(1,0); glVertex3d(0,30,0);

    //toit
    glTexCoord2i(0,0); glVertex3d(30,0,10);
    glTexCoord2i(0,1); glVertex3d(30,30,10);
    glTexCoord2i(1,1); glVertex3d(0,30,10);
    glTexCoord2i(1,0); glVertex3d(0,0,10);

    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glEndList();



    //batiment 4 conique

    glNewList(15, GL_COMPILE);

    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GLU_TRUE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texId[10]);

    glPushMatrix();
    glTranslatef(0,-60,0);

    //glColor3f(0.5, 0.35, 0.05);
    gluCylinder(quadric, 5, 5, 40, 100, 100);
    glTranslatef(0,0,30);

    //glColor3f(0.5, 0.35, 0.05);
    gluCylinder(quadric, 5, 10, 30, 100, 100);
    glTranslatef(0, 0, 30);
    gluDisk(quadric,0,10,100,100);


    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    gluQuadricTexture(quadric, GLU_FALSE);
    glEndList();



    //batiment 5 avec sphere

    glNewList(16, GL_COMPILE);

    GLUquadricObj* quadric2 = gluNewQuadric();
    gluQuadricTexture(quadric2, GLU_TRUE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texId[11]);

    glPushMatrix();
    glTranslatef(-15,-15,0);

    glColor3f(0.01, 0.56, 0.61);
    gluCylinder(quadric2, 5, 5, 20, 100, 100);
    glTranslatef(0,0,20);

    glColor3f(0.01, 0.56, 0.61);
    gluSphere(quadric2, 10, 100, 100);


    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    gluQuadricTexture(quadric2, GLU_FALSE);
    glEndList();



    //batiment 6

    glNewList(17, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texId[4]);

    glPushMatrix();
    glTranslatef(-30,20,0);

    glBegin(GL_QUADS);

    //4 faces latrales
    glTexCoord2i(0,0); glVertex3d(20,20,70);
    glTexCoord2i(0,2); glVertex3d(20,20,0);
    glTexCoord2i(2,2); glVertex3d(0,20,0);
    glTexCoord2i(2,0); glVertex3d(0,20,70);

    glTexCoord2i(0,0); glVertex3d(20,0,70);
    glTexCoord2i(0,2); glVertex3d(20,0,0);
    glTexCoord2i(2,2); glVertex3d(20,20,0);
    glTexCoord2i(2,0); glVertex3d(20,20,70);

    glTexCoord2i(0,0); glVertex3d(0,0,70);
    glTexCoord2i(0,2); glVertex3d(0,0,0);
    glTexCoord2i(2,2); glVertex3d(20,0,0);
    glTexCoord2i(2,0); glVertex3d(20,0,70);

    glTexCoord2i(0,0); glVertex3d(0,20,70);
    glTexCoord2i(0,2); glVertex3d(0,20,0);
    glTexCoord2i(2,2); glVertex3d(0,0,0);
    glTexCoord2i(2,0); glVertex3d(0,0,70);

    //sol
    glTexCoord2i(0,0); glVertex3d(20,20,0);
    glTexCoord2i(0,2); glVertex3d(20,0,0);
    glTexCoord2i(2,2); glVertex3d(0,0,0);
    glTexCoord2i(2,0); glVertex3d(0,20,0);

    //toit
    glTexCoord2i(0,0); glVertex3d(20,0,70);
    glTexCoord2i(0,2); glVertex3d(20,20,70);
    glTexCoord2i(2,2); glVertex3d(0,20,70);
    glTexCoord2i(2,0); glVertex3d(0,0,70);

    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glEndList();



    //batiment 7
    glNewList(18, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texId[5]);

    glPushMatrix();
    glTranslatef(-70,-60,0);

    glBegin(GL_QUADS);

    //4 faces latrales
    glTexCoord2i(0,0); glVertex3d(25,25,5);
    glTexCoord2i(0,1); glVertex3d(25,25,0);
    glTexCoord2i(1,1); glVertex3d(0,25,0);
    glTexCoord2i(1,0); glVertex3d(0,25,5);

    glTexCoord2i(0,0); glVertex3d(25,0,5);
    glTexCoord2i(0,1); glVertex3d(25,0,0);
    glTexCoord2i(1,1); glVertex3d(25,25,0);
    glTexCoord2i(1,0); glVertex3d(25,25,5);

    glTexCoord2i(0,0); glVertex3d(0,0,5);
    glTexCoord2i(0,1); glVertex3d(0,0,0);
    glTexCoord2i(1,1); glVertex3d(25,0,0);
    glTexCoord2i(1,0); glVertex3d(25,0,5);

    glTexCoord2i(0,0); glVertex3d(0,25,5);
    glTexCoord2i(0,1); glVertex3d(0,25,0);
    glTexCoord2i(1,1); glVertex3d(0,0,0);
    glTexCoord2i(1,0); glVertex3d(0,0,5);

    //sol
    glTexCoord2i(0,0); glVertex3d(25,25,0);
    glTexCoord2i(0,1); glVertex3d(25,0,0);
    glTexCoord2i(1,1); glVertex3d(0,0,0);
    glTexCoord2i(1,0); glVertex3d(0,25,0);

    //toit
    glTexCoord2i(0,0); glVertex3d(25,0,5);
    glTexCoord2i(0,1); glVertex3d(25,25,5);
    glTexCoord2i(1,1); glVertex3d(0,25,5);
    glTexCoord2i(1,0); glVertex3d(0,0,5);

    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glEndList();



    //batiment 8
    glNewList(18, GL_COMPILE);

    GLUquadricObj* quadric3 = gluNewQuadric();
    gluQuadricTexture(quadric3, GLU_TRUE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texId[12]);

    glPushMatrix();
    glTranslatef(100, 50, 0);

    glColor3f(0.5, 0.37, 0.05);
    gluCylinder(quadric3, 10, 10, 90, 100, 100);
    glTranslatef(0, 0, 90);
    gluDisk(quadric3,0,10,100,100);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    gluQuadricTexture(quadric3, GLU_FALSE);
    glEndList();



    //batiment 9
    glNewList(19, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texId[6]);

    glPushMatrix();
    glTranslatef(-100,-120,0);

    glBegin(GL_QUADS);

    //4 faces latrales
    glTexCoord2i(0,0); glVertex3d(18,18,120);
    glTexCoord2i(0,1); glVertex3d(18,18,0);
    glTexCoord2i(1,1); glVertex3d(0,18,0);
    glTexCoord2i(1,0); glVertex3d(0,18,120);

    glTexCoord2i(0,0); glVertex3d(18,0,120);
    glTexCoord2i(0,1); glVertex3d(18,0,0);
    glTexCoord2i(1,1); glVertex3d(18,18,0);
    glTexCoord2i(1,0); glVertex3d(18,18,120);

    glTexCoord2i(0,0); glVertex3d(0,0,120);
    glTexCoord2i(0,1); glVertex3d(0,0,0);
    glTexCoord2i(1,1); glVertex3d(18,0,0);
    glTexCoord2i(1,0); glVertex3d(18,0,120);

    glTexCoord2i(0,0); glVertex3d(0,18,120);
    glTexCoord2i(0,1); glVertex3d(0,18,0);
    glTexCoord2i(1,1); glVertex3d(0,0,0);
    glTexCoord2i(1,0); glVertex3d(0,0,120);

    //sol
    glTexCoord2i(0,0); glVertex3d(18,18,0);
    glTexCoord2i(0,1); glVertex3d(18,0,0);
    glTexCoord2i(1,1); glVertex3d(0,0,0);
    glTexCoord2i(1,0); glVertex3d(0,18,0);

    //toit
    glTexCoord2i(0,0); glVertex3d(18,0,120);
    glTexCoord2i(0,1); glVertex3d(18,18,120);
    glTexCoord2i(1,1); glVertex3d(0,18,120);
    glTexCoord2i(1,0); glVertex3d(0,0,120);

    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEndList();



    //batiment 10

    glNewList(20, GL_COMPILE);

    GLUquadricObj* quadric4 = gluNewQuadric();
    gluQuadricTexture(quadric4, GLU_TRUE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texId[13]);

    glPushMatrix();
    glTranslatef(100,-60,0);

    gluCylinder(quadric4, 30, 30, 10, 100, 100);
    glTranslatef(0,0,10);
	gluDisk(quadric4,0,30,100,100);

    gluSphere(quadric4, 10, 100, 100);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    gluQuadricTexture(quadric4, GLU_FALSE);
    glEndList();



    //batiment 11
    glNewList(21, GL_COMPILE);

    GLUquadricObj* quadric5 = gluNewQuadric();
    gluQuadricTexture(quadric5, GLU_TRUE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texId[14]);

    glPushMatrix();
    glTranslatef(-110,80,0);

    gluCylinder(quadric5, 10, 0, 95, 100, 100);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    gluQuadricTexture(quadric5, GLU_FALSE);
    glEndList();



    //batiment 12 sphere

    glNewList(22, GL_COMPILE);

    GLUquadricObj* quadric6 = gluNewQuadric();
    gluQuadricDrawStyle(quadric6, GLU_FILL);
    gluQuadricNormals(quadric6, GLU_SMOOTH);
    gluQuadricTexture(quadric6, GLU_TRUE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texId[15]);

    glPushMatrix();
    glTranslatef(-90,-60,0);
    glTranslatef(0,0,5);

    gluSphere(quadric6, 20, 100, 100);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    gluQuadricTexture(quadric6, GLU_FALSE);
    glEndList();





    //city
	glNewList(10, GL_COMPILE); // declaration de la liste City

	glCallList(6);

    glCallList(11);

    glCallList(12);

    glCallList(13);

    glCallList(14);

    glCallList(15);

    glCallList(16);

    glCallList(17);

    glCallList(18);

    glCallList(19);

    glCallList(20);

    glCallList(21);

    glCallList(22);


	glEndList();


}




