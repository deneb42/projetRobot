#include "city.h"


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
    
    
    //city
	glNewList(10, GL_COMPILE); // declaration de la liste City



    //sol
    glNewList(11, GL_COMPILE);
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
    glEndList();
		
		
	//batiment 1	
    glNewList(12, GL_COMPILE);
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
    glEndList();
		
    
    //batiment 2
    glNewList(13, GL_COMPILE);
		glPushMatrix();
            glTranslatef(30,0,0);
            
            glBegin(GL_QUADS);
            
            //4 faces latrales
            glVertex3d(5,5,20);
            glVertex3d(5,5,0);
            glVertex3d(0,5,0);
            glVertex3d(0,5,20);
            
            glVertex3d(5,0,20);
            glVertex3d(5,0,0);
            glVertex3d(5,5,0);
            glVertex3d(5,5,20);
            
            glVertex3d(0,0,20);
            glVertex3d(0,0,0);
            glVertex3d(5,0,0);
            glVertex3d(5,0,20);
            
            glVertex3d(0,5,20);
            glVertex3d(0,5,0);
            glVertex3d(0,0,0);
            glVertex3d(0,0,20);
            
            //sol
            glVertex3d(5,5,0);
            glVertex3d(5,0,0);
            glVertex3d(0,0,0);
            glVertex3d(0,5,0);
            
            //toit
            glVertex3d(5,0,20);
            glVertex3d(5,5,20);
            glVertex3d(0,5,5);
            glVertex3d(0,0,20);
            
            glEnd();
		
		glPopMatrix();
    glEndList();
		
		
    //batiment3
    glNewList(14,GL_COMPILE);
		glPushMatrix();
            glTranslatef(0,50,0);
            
            glBegin(GL_QUADS);
            
            //4 faces latrales
            glVertex3d(30,30,10);
            glVertex3d(30,30,0);
            glVertex3d(0,30,0);
            glVertex3d(0,30,10);
            
            glVertex3d(30,0,10);
            glVertex3d(30,0,0);
            glVertex3d(30,30,0);
            glVertex3d(30,30,10);
            
            glVertex3d(0,0,10);
            glVertex3d(0,0,0);
            glVertex3d(30,0,0);
            glVertex3d(30,0,10);
            
            glVertex3d(0,30,10);
            glVertex3d(0,30,0);
            glVertex3d(0,0,0);
            glVertex3d(0,0,10);
            
            //sol
            glVertex3d(30,30,0);
            glVertex3d(30,0,0);
            glVertex3d(0,0,0);
            glVertex3d(0,30,0);
            
            //toit
            glVertex3d(30,0,10);
            glVertex3d(30,30,10);
            glVertex3d(0,30,30);
            glVertex3d(0,0,10);
            
            glEnd();
		
		glPopMatrix();
    glEndList();
		
    glNewList(15, GL_COMPILE);
		//batiment 4 conique
		GLUquadricObj* quadratic = gluNewQuadric();
		
		glColor3f(1,1,1);
		glPushMatrix();
            gluCylinder(quadratic, 10, 10, 50, 100, 100);
            glTranslatef(0,0,50);
            
            gluCylinder(quadratic, 10, 20, 10, 100, 100);
            glTranslatef(0,0,10);
            
            gluCylinder(quadratic, 20, 20, 5, 100, 100);
            
		glPopMatrix();
    glEndList();
    
    
    
    
    
    
    
    
    /*//nuages
    glNewList(20,GL_COMPILE);
    
    glEndList();    
    */
    
    
    
		
	glEndList();    
    
    
}




