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
#include "shapes.c"

// Functions
void initControls();
void initCamera();
void init_scene();
void processCameraChange();
double* getDirectionToLeft();

void render_scene();

GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
GLvoid window_key_up(unsigned char key, int x, int y);
GLvoid window_mouseFunc(int button, int state, int x, int y);
GLvoid window_motionFunc(int x, int y);
GLvoid window_timer();
void window_specialDownFunc(int key, int x, int y);
void window_specialUpFunc(int key, int x, int y);
