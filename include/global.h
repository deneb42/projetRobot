#ifndef GLOBAL_H
#define GLOBAL_H

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
	
	void loadTexture(char* chemin, char* name, int *tex);
	
#endif
