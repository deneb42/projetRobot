#ifndef BENDER_H
#define BENDER_H

	//colors
	#define LIGHT_GRAY 0.84, 0.9, 0.95
	#define DARK_GRAY 0.74, 0.8, 0.87
	#define WHITE 0.99, 0.99, 0.82
	#define BLACK 0.04, 0.05, 0.05
	#define BLUE_GRAY 0.6,0.69,0.78
	#define LIGHT_BLACK 0.4, 0.5, 0.5


	// List creation functions
	void makeBender(char *chemin);
	void makeBody(int *tex);
	void makeEyes();
	void makeHand();
	void makeFoot();
	
	// Model drawing functions
	void drawBender();
	void drawLimb(char limb, int nbSlices, float *controlsX, float *controlsY, float *controlsZ);
	
	// Utility functions
	float Bezier4 ( float coor[4] , float t );
	void setArmCoords(char axe, int side, int index, float value);
	void setLegCoords(char axe, int side, int index, float value);
	void setAllCoords(int pas);

#endif
