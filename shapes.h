#ifndef SHAPES_H
#define SHAPES_H
#ifndef __APPLE__
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

//void createBender();
void make_square();
void make_cube();
void drawRepere();

#endif
