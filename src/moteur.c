#include "global.h"
#include "moteur.h"
#include "collisions.h"
#include "city.h"
#include "bender.h"

#define NBROBOTS 3		// Number of robots
#define NBBUILDINGS 12 	// Number of buildings
#define TURNING 0		// IA action
#define MOVING 1		// IA action

#define ARROW_UP 0		// Constants for arrow keys
#define ARROW_DOWN 1
#define ARROW_LEFT 2
#define ARROW_RIGHT 3

// Controls
int arrowKeys[4];
int mouseButton[3];
int speedBoost = 1;
int mouse_pos_x = 0, mouse_pos_y = 0;

// Camera
double cameraPosition[3];	// Position of the camera
double cameraDirection[3];	// Direction the camera looks in.
double phi;					// Vertical angle of the camera
double theta;				// Horizontal angle of the camera
double sensitivity = .5;	// Sensitivity of the mouse motion
double cameraSpeed = 1.0;	// Speed of the camera when it's moving
int cameraKeys[4];			// Keys for controlling the camera

int follows; // Associated to the robot currently being followed.
			 // If equal to NBROBOTS, then no robot is being followed and the FreeFly camera mode is activated.

// Robots
Bender robot[NBROBOTS];	// Array of robots.

// Buildings
double buildingPosition[NBBUILDINGS][3];	// Array of buildings.
int buildingType[NBBUILDINGS];	// Type of each building, either TYPE_BOX or TYPE_CYLINDER

// Main function
int main(int argc, char* argv[])
{
	int i;
	char *chemin;

	// Glut initializations
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Projet OpenGl - Bender");
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5,0.5,0.5, 1);

	// Glut callback functions
	glutReshapeFunc(&window_reshape);
	glutDisplayFunc(&window_display);
	glutKeyboardFunc(&window_key);
	glutKeyboardUpFunc(&window_key_up);
	glutMouseFunc(&window_mouseFunc);
	glutMotionFunc(&window_motionFunc);
	glutSpecialFunc(&window_specialDownFunc);
	glutSpecialUpFunc(&window_specialUpFunc);
	glutTimerFunc(40, &window_timer, 0);

	// Program variables initialization
	initControls();
	initCamera();
	initBuildings();

	// Fetching the path for the texture directory.
	chemin = (char*)malloc(100);
	chemin[0]='\0';
	strcat(chemin, argv[0]);
	for(i=99;i>=0;i--)
	{
		if(chemin[i]=='/' || chemin[i]=='\\')
		{
			chemin[i+1]='\0';
			i=-1;
		}
	}

	// Buildings and robots list initialization
	makeBender(chemin);
	createCity(chemin);
	free(chemin);

	glutMainLoop();

	return EXIT_FAILURE;
}

// Initializes the program controls and the robots.
void initControls()
{
	int i;
	srand(time(NULL)); // Clock initialization

	// Control keys and mouse buttons initialization
	for(i=0; i<4; i++)
		arrowKeys[i] = 0;
	for(i=0; i<3; i++)
		mouseButton[i] = 0;

	// Robot initialization
	for (i=0; i<NBROBOTS; i++)
	{
		initBender(robot+i);

		robot[i].position[0] = 0+i*5;
		robot[i].position[1] = 0+i*5;
		robot[i].position[2] = 0;
		robot[i].direction[0] = 1.0;
		robot[i].direction[1] = 0.0;
		robot[i].direction[2] = 0.0;
		robot[i].angle = 0.0;
		robot[i].action = 1;
		robot[i].endActionTime = clock() - 1000;
	}
}

// Initializes the camera.
void initCamera()
{
	int i;
	for(i=0; i<4; i++)
		cameraKeys[i] = 0;

	cameraPosition[0] = 0;
	cameraPosition[1] = 2;
	cameraPosition[2] = 5;
	follows = NBROBOTS;	// We start the camera in FreeFly mode

	phi = -20;
	theta = -90;
	processCameraChange();	// Computes the direction vector.
}

// Initializes the buildings.
void initBuildings()
{
	buildingType[0] = 11;
	buildingPosition[0][0] = 20;
	buildingPosition[0][1] = 0;
	buildingPosition[0][2] = 20;

	buildingType[1] = 12;
	buildingPosition[1][0] = 30;
	buildingPosition[1][1] = 0;
	buildingPosition[1][2] = -90;

	buildingType[2] = 13;
	buildingPosition[2][0] = 60;
	buildingPosition[2][1] = 0;
	buildingPosition[2][2] = 80;

	buildingType[3] = 14;
	buildingPosition[3][0] = -10;
	buildingPosition[3][1] = 0;
	buildingPosition[3][2] = -60;

	buildingType[4] = 15;
	buildingPosition[4][0] = -15;
	buildingPosition[4][1] = 0;
	buildingPosition[4][2] = -15;

	buildingType[5] = 16;
	buildingPosition[5][0] = -30;
	buildingPosition[5][1] = 0;
	buildingPosition[5][2] = 20;

	buildingType[6] = 17;
	buildingPosition[6][0] = -70;
	buildingPosition[6][1] = 0;
	buildingPosition[6][2] = -60;

	buildingType[7] = 18;
	buildingPosition[7][0] = 100;
	buildingPosition[7][1] = 0;
	buildingPosition[7][2] = 50;

	buildingType[8] = 19;
	buildingPosition[8][0] = -100;
	buildingPosition[8][1] = 0;
	buildingPosition[8][2] = -120;

	buildingType[9] = 20;
	buildingPosition[9][0] = -110;
	buildingPosition[9][1] = 0;
	buildingPosition[9][2] = 80;

	buildingType[10] = 21;
	buildingPosition[10][0] = -110;
	buildingPosition[10][1] = 0;
	buildingPosition[10][2] = 80;

	buildingType[11] = 22;
	buildingPosition[11][0] = -90;
	buildingPosition[11][1] = 0;
	buildingPosition[11][2] = -60;
}

// Renders the scene.
void render_scene()
{
	int i;
	glRotatef(-90, 1,0,0);

	// Robot rendering
	for(i=0; i<NBROBOTS; i++) {
		glPushMatrix();
			glTranslatef(robot[i].position[0], robot[i].position[1], robot[i].position[2]);
			glRotatef((robot[i].angle+1.5) * 180.0 / M_PI, 0, 0, 1);
			// Draws Bender, with more or less precision, depending on
			// the expected rendering speed, and whether the robot is being controlled or not.
			if (i == follows || NBROBOTS <=3)
				drawBender(100, robot+i);
			else
				drawBender(50, robot+i);
		glPopMatrix();
	}

	// Environment rendering
	glPushMatrix();
		glCallList(10); // Displays the city
	glPopMatrix();

	glutSwapBuffers();
}

GLvoid window_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	processCameraChange();
	render_scene();
	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70,(double)width/height,0.001,1000);
	glMatrixMode(GL_MODELVIEW);
	processCameraChange();
}

// Handles the normal keys press events.
GLvoid window_key(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'z':	// Camera move forward
			cameraKeys[ARROW_UP] = 1;
			break;
		case 's':	// Camera move backward
			cameraKeys[ARROW_DOWN] = 1;
			break;
		case 'q':	// Camera move to the left
			cameraKeys[ARROW_LEFT] = 1;
			break;
		case 'd':	// Camera move to the right
			cameraKeys[ARROW_RIGHT] = 1;
			break;
		case 'c':	// Change view, either to the next robot or to FreeFly camera view.
			follows = (follows+1)%(NBROBOTS+1);
			break;
		case ' ':	// Exits the program.
			exit(EXIT_SUCCESS);
			break;
        default:
            break;
	}
}

// Handles the normal keys release events.
GLvoid window_key_up(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'z':	// Camera move forward
			cameraKeys[ARROW_UP] = 0;
			break;
		case 's':	// Camera move backward
			cameraKeys[ARROW_DOWN] = 0;
			break;
		case 'q':	// Camera move to the left
			cameraKeys[ARROW_LEFT] = 0;
			break;
		case 'd':	// Camera move to the right
			cameraKeys[ARROW_RIGHT] = 0;
			break;
        default:
            break;
	}
}

// Handles the mouse button events.
GLvoid window_mouseFunc(int button, int state, int x, int y)
{
	mouseButton[button] = (state==GLUT_DOWN) ? 1 : 0;
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_pos_x = x;
		mouse_pos_y = y;
		glPushMatrix();
	 }
	else
		glPopMatrix();
}

// Handles the mouse motion events.
GLvoid window_motionFunc(int x, int y)
{
	if (follows == NBROBOTS && mouseButton[0]) // If the left mouse button is pressed
	{
		// then change the direction the camera is looking in.
		theta += (x - mouse_pos_x)*sensitivity;
		phi -= (y - mouse_pos_y)*sensitivity;
		mouse_pos_x = x;
		mouse_pos_y = y;
		processCameraChange();
		glutPostRedisplay();
	}
}

// Handles the special keys press events.
void window_specialDownFunc(int key, int x, int y)
{
	// If shift is pressed, then make the camera / robots move faster.
	speedBoost = (glutGetModifiers() == GLUT_ACTIVE_SHIFT) ? 2 : 1;
	switch(key)
	{
		case GLUT_KEY_UP:	// Move forward
			arrowKeys[ARROW_UP] = 1;
			break;
		case GLUT_KEY_DOWN:	// Move backward
			arrowKeys[ARROW_DOWN] = 1;
			break;
		case GLUT_KEY_LEFT:	// Turn left
			arrowKeys[ARROW_LEFT] = 1;
			break;
		case GLUT_KEY_RIGHT: // Turn right
			arrowKeys[ARROW_RIGHT] = 1;
			break;
		default:
			break;
	}
}

// Handles the special keys release events.
void window_specialUpFunc(int key, int x, int y)
{
	// If shift is pressed, then make the camera / robots move faster.
	speedBoost = (glutGetModifiers() == GLUT_ACTIVE_SHIFT) ? 2 : 1;
	switch(key) {
		case GLUT_KEY_UP:	// Move forward
			arrowKeys[ARROW_UP] = 0;
			break;
		case GLUT_KEY_DOWN:	// Move backward
			arrowKeys[ARROW_DOWN] = 0;
			break;
		case GLUT_KEY_LEFT:	// Turn left
			arrowKeys[ARROW_LEFT] = 0;
			break;
		case GLUT_KEY_RIGHT: // Turn right
			arrowKeys[ARROW_RIGHT] = 0;
			break;
		default:
			break;
	}
}

// Main updater function.
// Is called every 40ms, and updates the position
// of both the camera and the robots.
GLvoid window_timer()
{
  int i, robotIndex=0;
  double speed = .5; // Speed at which a robot moves.
  double angleIncrement = 1.0/18.0;	// Speed at which a robot turns.
  double* leftDirection;	// For the camera, direction when moving to the left.
  double tempPosition[3];	// Expected position of the robot, used to predict collisions.

  glutTimerFunc(40,&window_timer,0);	// Call this function again over 40ms.

	// Robot control
  for(robotIndex=0; robotIndex<NBROBOTS; robotIndex++)	// For every robot
  {
	if (robotIndex == follows)	// If the robot is being controlled, then update its direction
								// and position based on the pressed keys.
	{
	  if (arrowKeys[ARROW_LEFT] && !arrowKeys[ARROW_RIGHT])
	  {
		// Turn left
		robot[robotIndex].angle += angleIncrement;
		if (robot[robotIndex].angle>= M_PI)
			robot[robotIndex].angle -= 2*M_PI;
		robot[robotIndex].direction[0] = cos (robot[robotIndex].angle);
		robot[robotIndex].direction[1] = sin (robot[robotIndex].angle);
	  }
	  else if (arrowKeys[ARROW_RIGHT] && !arrowKeys[ARROW_LEFT])
	  {
		// Turn right
		robot[robotIndex].angle -= angleIncrement;
		if (robot[robotIndex].angle < -M_PI)
			robot[robotIndex].angle += 2*M_PI;
		robot[robotIndex].direction[0] = cos (robot[robotIndex].angle);
		robot[robotIndex].direction[1] = sin (robot[robotIndex].angle);
	  }

	  if (arrowKeys[ARROW_UP] && !arrowKeys[ARROW_DOWN])
	  {
		// Move forward
		tempPosition[0] = robot[robotIndex].position[0] + speed*robot[robotIndex].direction[0]*speedBoost;
		tempPosition[1] = robot[robotIndex].position[1] + speed*robot[robotIndex].direction[1]*speedBoost;
		if (checkCollision(tempPosition, robotIndex) == 0)	// If the robot won't collide, move it forward.
		{
			robot[robotIndex].position[0] = tempPosition[0];
			robot[robotIndex].position[1] = tempPosition[1];
			setAllCoords(speedBoost, robot+robotIndex);	// Animate the robot.
		}
	  }

	  else if (arrowKeys[ARROW_DOWN] && !arrowKeys[ARROW_UP])
	  {
		// Move backward
		tempPosition[0] = robot[robotIndex].position[0] - speed*robot[robotIndex].direction[0]*speedBoost;
		tempPosition[1] = robot[robotIndex].position[1] - speed*robot[robotIndex].direction[1]*speedBoost;
		if (checkCollision(tempPosition, robotIndex) == 0)	// If the robot won't collide, move it backward
		{
			robot[robotIndex].position[0] = tempPosition[0];
			robot[robotIndex].position[1] = tempPosition[1];
			setAllCoords(-speedBoost, robot+robotIndex); // Animate the robot.
		}
	  }
	}
	else	// If the robot is not being controlled, then update its direction
			// based on the artificial intelligence's decisions.
	{
		// Explaining of how the artificial intelligence works.
		// Robots successively alternate between turning and moving forward.
		// They do each of these actions for a limited period of time.
		// If the robot collides with an other object, then it will keep on turning
		// until its action is set back to MOVING and is expected not to collide.
		if (robot[robotIndex].endActionTime < clock()) {

			// The following action will be finished in 300ms to 2 seconds.
			robot[robotIndex].endActionTime = clock() + (rand()%17 + 3) * 100;
			// We change the robot's action.
			robot[robotIndex].action = (robot[robotIndex].action == TURNING) ? MOVING : TURNING;
			if (robot[robotIndex].action == TURNING)
				// Determines the direction to which the robot will turn, left or right;
				robot[robotIndex].angleDirection = (rand() % 2) * 2 - 1; // -1 or +1.
		}
		if (robot[robotIndex].action == TURNING)	// The robot turns.
		{
			// Updates its direction.
			robot[robotIndex].angle += angleIncrement * robot[robotIndex].angleDirection;
			if (robot[robotIndex].angle>= M_PI)
				robot[robotIndex].angle -= 2*M_PI;
			else if (robot[robotIndex].angle < -M_PI)
				robot[robotIndex].angle += 2*M_PI;
			robot[robotIndex].direction[0] = cos (robot[robotIndex].angle);
			robot[robotIndex].direction[1] = sin (robot[robotIndex].angle);
		}
		else // action == MOVING. The robot moves forward.
		{
			tempPosition[0] = robot[robotIndex].position[0] + speed*robot[robotIndex].direction[0];
			tempPosition[1] = robot[robotIndex].position[1] + speed*robot[robotIndex].direction[1];
			if (checkCollision(tempPosition, robotIndex) == 0)	// If the robot won't collide, move it forward
			{
				robot[robotIndex].position[0] = tempPosition[0];
				robot[robotIndex].position[1] = tempPosition[1];
				setAllCoords(speedBoost, robot+robotIndex);	// Animate the robot.
			}
			else {
				robot[robotIndex].endActionTime = clock() - 1000;
				robot[robotIndex].action = MOVING; // Will be set to TURNING at the next update.
			}
		}
	}
  }

  // Camera control
  if (cameraKeys[ARROW_LEFT] && !cameraKeys[ARROW_RIGHT])
  {
  	// Move left
	leftDirection = getDirectionToLeft();
	for(i=0; i<3; i++)
		cameraPosition[i] += leftDirection[i]*cameraSpeed*speedBoost;
	free(leftDirection);
  }
  else if (cameraKeys[ARROW_RIGHT] && !cameraKeys[ARROW_LEFT])
  {
	// Move right
	leftDirection = getDirectionToLeft();
	for(i=0; i<3; i++)
		cameraPosition[i] -= leftDirection[i]*cameraSpeed*speedBoost;
	free(leftDirection);
  }
  if (cameraKeys[ARROW_UP] && !cameraKeys[ARROW_DOWN])
  {
	// Move forward
	for (i=0; i<3; i++)
		cameraPosition[i] += cameraDirection[i]*cameraSpeed*speedBoost;
  }

  else if (cameraKeys[ARROW_DOWN] && !cameraKeys[ARROW_UP])
  {
	// Move backward
	for (i=0; i<3; i++)
		cameraPosition[i] -= cameraDirection[i]*cameraSpeed*speedBoost;
  }
  // When the user presses on the right mouse button or on the mouse wheel button,
  // the camera will move up or downward.
  if (mouseButton[1] && !mouseButton[2])	// Downward
	cameraPosition[1] -= .5;
  else if (mouseButton[2] && !mouseButton[1])	// Upward
	cameraPosition[1] += .5;
  glutPostRedisplay();
}

// Updates the camera position.
void processCameraChange()
{
	double r;
	if (follows != NBROBOTS) // If a robot is being followed
		// Then place the camera behind the robot.
		gluLookAt(robot[follows].position[0] - 10*robot[follows].direction[0],
				  10,
				  - robot[follows].position[1] + 10*robot[follows].direction[1],
				  robot[follows].position[0],
				  robot[follows].position[2] + 5,
				  -robot[follows].position[1],
				  0, 1, 0);
	else {
		// Limit the vertical angle.
		if (phi > 89)
			phi = 89;
		else if (phi < -89)
			phi = -89;
		// Compute the camera direction, then update the camera.
		r = cos(phi*M_PI/180);
		cameraDirection[0] = r * cos(theta*M_PI/180);
		cameraDirection[1] = sin(phi*M_PI/180);
		cameraDirection[2] = r * sin(theta*M_PI/180);
		gluLookAt(cameraPosition[0],
				  cameraPosition[1],
				  cameraPosition[2],
				  cameraPosition[0] + cameraDirection[0],
				  cameraPosition[1] + cameraDirection[1],
				  cameraPosition[2] + cameraDirection[2],
				  0, 1, 0);
	}
}

// Returns the vector that would make the camera go left.
// Warning : Return value must be freed.
double* getDirectionToLeft()
{
	double up[3] = {0, 1, 0};
	double* left = (double*) malloc(sizeof(double) * 3);
	double norme=0;
	int i;
	left[0] = up[1]*cameraDirection[2] - up[2]*cameraDirection[1];
	left[1] = up[2]*cameraDirection[0] - up[0]*cameraDirection[2];
	left[2] = up[0]*cameraDirection[1] - up[1]*cameraDirection[0];
	for(i=0; i<3; i++)
		norme += cameraDirection[i]*cameraDirection[i];
	norme = sqrt(norme);
	for(i=0; i<3; i++)
		left[i] /= norme;
	return left;
}

// Checks if a robot is going to collide it is positionned at robotPosition.
// robotPosition : Predicted position of the robot.
// robotIndex : Index of the current robot in the robot array.
// Returns 1 if there will be a collision, 0 otherwise.
int checkCollision(double robotPosition[3], int robotIndex)
{
	int i=0;
	int collision = 0;
	Object** bender = getBender(robotPosition); // Bounding shapes of the robot. One as a box, the other as a cylinder.
												// Each will be used for collisions with an object of the same type.
	Object** otherBender;	// Represents the bounding shapes of other robots.
	Object* building;		// Represents the bounding shape of the buildings.

	 // Check if it collides with the other robots.
	for(i = 0; i<NBROBOTS && collision == 0; i++)
	{
		if (i != robotIndex)
		{
			otherBender = getBender(robot[i].position);
			if (inCollision(bender[TYPE_CYLINDER], otherBender[TYPE_CYLINDER]))
				collision = 1;
			free(otherBender[0]);
			free(otherBender[1]);
			free(otherBender);
		}
	}

	// Check if it collides with buildings.
	for(i = 0; i<NBBUILDINGS && collision == 0; i++)
	{
		building = getBuilding(buildingPosition[i], buildingType[i]);
		if (inCollision(bender[building->type], building))
			collision = 1;
		free(building);
	}
	free(bender[0]);
	free(bender[1]);
	free(bender);
	return collision;
}










