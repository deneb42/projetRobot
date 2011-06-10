#ifndef BENDER_H
#define BENDER_H
	#include <time.h>
	//colors
	#define LIGHT_GRAY 0.84, 0.9, 0.95
	#define DARK_GRAY 0.74, 0.8, 0.87
	#define WHITE 0.99, 0.99, 0.82
	#define BLACK 0.04, 0.05, 0.05
	#define BLUE_GRAY 0.6,0.69,0.78
	#define LIGHT_BLACK 0.4, 0.5, 0.5

	// Structure representing a Bender robot.
	typedef struct Bender Bender;
	struct Bender
	{
		// Controls
		double position[3];		// Position
		double direction[3];	// Direction in which the robot is looking.
		double angle;			// Angle corresponding to the direction.

		// Animations
		int increment;			// Used to determine where the body components have to
								// be displayed during the animation.
		// Leg and arms positions.
		float legX[2][4];
		float legY[2][4];
		float legZ[2][4];

		float armX[2][4];
		float armY[2][4];
		float armZ[2][4];

		// Artificial intelligence
		int action;				// Action to be made by the robot, either turning or moving forward.
		clock_t endActionTime;	// Time at which the current action is to be ended,
								// at which point a new action will have to be decided.
		int angleDirection;		// Indicates where the robot is turning to, left or right.
	};

	// List creation functions
	void makeBender(char *chemin);
	void makeBody(int *tex);
	void makeEyes();
	void makeHand();
	void makeFoot();
	void initBender(Bender* bender);

	// Model drawing functions
	void drawBender();
	void drawLimb(char limb, int nbSlices, float *controlsX, float *controlsY, float *controlsZ);

	// Utility functions
	float Bezier4 ( float coor[4] , float t );
	void setArmCoords(Bender* bender, char axe, int side, int index, float value);
	void setLegCoords(Bender* bender, char axe, int side, int index, float value);
	void setAllCoords(int boost, Bender* bender);

#endif
