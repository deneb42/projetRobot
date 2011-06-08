#ifndef __APPLE__
	#include <GL/gl.h>           
	#include <GL/glu.h>         
	#include <GL/glut.h> 
#else
	#include <OpenGL/gl.h>           
	#include <OpenGL/glu.h>         
	#include <GLUT/glut.h> 
#endif
#include "bmp.h"


#include <math.h>
#define PI 3.1415926535898


void load_textures(void);
int texId[4]; //A créer en même temps que toutes les variables. La taille depend du nombre de textures



//Loader de textures
void load_textures(void) {
    /* Si le programme n'arrive pas a charger la texture */
    if ( !(texId[0] = loadBMPTexture("textures/sol.bmp"))){
        /* Gestion de l'erreur */
        printf("Impossible de charger la texture 'sol'\n");
        exit(EXIT_FAILURE);
    }
    if ( !(texId[1] = loadBMPTexture("textures/bat1.bmp"))){
        /* Gestion de l'erreur */
        printf("Impossible de charger la texture 'bat1'\n");
        exit(EXIT_FAILURE);
    }
    if ( !(texId[2] = loadBMPTexture("textures/bat3.bmp"))){
        /* Gestion de l'erreur */
        printf("Impossible de charger la texture 'bat2'\n");
        exit(EXIT_FAILURE);
    }
    if ( !(texId[3] = loadBMPTexture("textures/bat3.bmp"))){
        /* Gestion de l'erreur */
        printf("Impossible de charger la texture 'bat3'\n");
        exit(EXIT_FAILURE);
    }
}



void createCity()
{
	GLUquadricObj* qobj;
	//GLUquadricObj* GLAPIENTRY qobj;


	// allocation d´une description de quadrique
	qobj = gluNewQuadric();
	// la quadrique est pleine
	gluQuadricDrawStyle(qobj, GLU_FILL);
	// les ombrages, s´il y en a, sont doux
	gluQuadricNormals(qobj, GLU_SMOOTH);
	
	load_textures();
        
    
	glNewList(10, GL_COMPILE); // declaration de la liste City

		//sol
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texId[0]);
		
		glColor3f (1,1,1); 
		glPushMatrix();
		glBegin(GL_POLYGON);
		glTexCoord2i(100,100);		glVertex3f(100,100,0);
		glTexCoord2i(100,0);		glVertex3f(100,-100,0);
		glTexCoord2i(0,0);		glVertex3f(-100,-100,0);
		glTexCoord2i(0,100);      glVertex3f(-100,100,0);
		glEnd();		
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		
		
		

		//batiment 1
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texId[3]);
		
		glPushMatrix();
		
		glBegin(GL_QUADS);
		
		//4 faces latrales
		glTexCoord2i(0,0); glVertex3d(3,3,5);
		glTexCoord2i(0,1); glVertex3d(3,3,0);
		glTexCoord2i(1,1); glVertex3d(0,3,0);
		glTexCoord2i(1,0); glVertex3d(0,3,5);
		
		glTexCoord2i(0,0); glVertex3d(3,0,5);
		glTexCoord2i(0,1); glVertex3d(3,0,0);
		glTexCoord2i(1,1); glVertex3d(3,3,0);
		glTexCoord2i(1,0); glVertex3d(3,3,5);
		
		glTexCoord2i(0,0); glVertex3d(0,0,5);
		glTexCoord2i(0,1); glVertex3d(0,0,0);
		glTexCoord2i(1,1); glVertex3d(3,0,0);
		glTexCoord2i(1,0); glVertex3d(3,0,5);
		
		glTexCoord2i(0,0); glVertex3d(0,3,5);
		glTexCoord2i(0,1); glVertex3d(0,3,0);
		glTexCoord2i(1,1); glVertex3d(0,0,0);
		glTexCoord2i(1,0); glVertex3d(0,0,5);
		
		//sol
		glVertex3d(3,3,0);
		glVertex3d(3,0,0);
		glVertex3d(0,0,0);
		glVertex3d(0,3,0);
		
		//toit
		glVertex3d(3,0,5);
		glVertex3d(3,3,5);
		glVertex3d(0,3,5);
		glVertex3d(0,0,5);
		
		glEnd();
		
		glPopMatrix();
		
		glDisable(GL_TEXTURE_2D);
		
		
		
		//batiment 2
		glPushMatrix();
		glTranslatef(20,0,0);
		
		glBegin(GL_QUADS);
		
		//4 faces latrales
		glVertex3d(3,3,5);
		glVertex3d(3,3,0);
		glVertex3d(0,3,0);
		glVertex3d(0,3,5);
		
		glVertex3d(3,0,5);
		glVertex3d(3,0,0);
		glVertex3d(3,3,0);
		glVertex3d(3,3,5);
		
		glVertex3d(0,0,5);
		glVertex3d(0,0,0);
		glVertex3d(3,0,0);
		glVertex3d(3,0,5);
		
		glVertex3d(0,3,5);
		glVertex3d(0,3,0);
		glVertex3d(0,0,0);
		glVertex3d(0,0,5);
		
		//sol
		glVertex3d(3,3,0);
		glVertex3d(3,0,0);
		glVertex3d(0,0,0);
		glVertex3d(0,3,0);
		
		//toit
		glVertex3d(3,0,5);
		glVertex3d(3,3,5);
		glVertex3d(0,3,3);
		glVertex3d(0,0,5);
		
		glEnd();
		
		glPopMatrix();
		
		
		
		//batiment3
		glPushMatrix();
		glTranslatef(0,10,0);
		
		glBegin(GL_QUADS);
		
		//4 faces latrales
		glVertex3d(3,3,5);
		glVertex3d(3,3,0);
		glVertex3d(0,3,0);
		glVertex3d(0,3,5);
		
		glVertex3d(3,0,5);
		glVertex3d(3,0,0);
		glVertex3d(3,3,0);
		glVertex3d(3,3,5);
		
		glVertex3d(0,0,5);
		glVertex3d(0,0,0);
		glVertex3d(3,0,0);
		glVertex3d(3,0,5);
		
		glVertex3d(0,3,5);
		glVertex3d(0,3,0);
		glVertex3d(0,0,0);
		glVertex3d(0,0,5);
		
		//sol
		glVertex3d(3,3,0);
		glVertex3d(3,0,0);
		glVertex3d(0,0,0);
		glVertex3d(0,3,0);
		
		//toit
		glVertex3d(3,0,5);
		glVertex3d(3,3,5);
		glVertex3d(0,3,3);
		glVertex3d(0,0,5);
		
		glEnd();
		
		glPopMatrix();
		
		/*
		//batiment 4 conique
		GLUquadricObj* quadratic = gluNewQuadric();
		
		glColor3f(0.4,0.4,0.4);
		glPushMatrix();
		gluCylinder(quadratic, 10, 10, 50, 100, 100);
		glTranslatef(0,0,50);
		
		gluCylinder(quadratic, 10, 20, 10, 100, 100);
		glTranslatef(0,0,10);
		
		gluCylinder(quadratic, 20, 20, 5, 100, 100);
		
		glTranslatef(0,0,5);
		gluCylinder(quadratic, 20, 10, 10, 100, 100);
		glTranslatef(0,0,10);
		gluDisk(quadratic,0,10,100,100);	
		glPopMatrix();
		*/
		
	glEndList();    
    
    
}




