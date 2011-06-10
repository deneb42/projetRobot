#ifndef MOTEUR_H
#define MOTEUR_H
	#include <string.h>

	void initControls();
	void initCamera();
	void init_scene();
	void initBuildings();
	void processCameraChange();
	double* getDirectionToLeft();
	int checkCollision(double robotPosition[3], int robotIndex);

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

#endif
