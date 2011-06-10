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
	
	#define CITY 10
	#define SKY 11
	#define	FLOOR 12
	#define	BAT1 13
	#define	BAT2 14
	#define	BAT3 15
	#define	BAT4 16
	#define	BAT5 17
	#define	BAT6 18
	#define	BAT7 19
	#define	BAT8 20
	#define	BAT9 21
	#define	BAT10 22
	#define	BAT11 23
	#define	BAT12 24
	
	// utility functions
	void loadTexture(char* chemin, char* name, int *tex);
	
#endif
