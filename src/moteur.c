#include "global.h"
#include "moteur.h"
#include "collisions.h"
#include "city.h"
#include "bender.h"

#define NBROBOTS 3
#define NBBUILDINGS 12
#define TURNING 0
#define MOVING 1

int mouse_pos_x = 0, mouse_pos_y = 0;

char *chemin;

// Controls
int ARROW_UP = 0;
int ARROW_DOWN = 1;
int ARROW_LEFT = 2;
int ARROW_RIGHT = 3;
int arrowKeys[4];
int mouseButton[3];

// Camera
double cameraPosition[3];
double cameraDirection[3];
double phi;
double theta;
double sensitivity = .5;
double cameraSpeed = 1.0;
int cameraKeys[4];
int follows;

// Robots
Bender robot[NBROBOTS];
// Buildings
double buildingPosition[NBBUILDINGS][3];
int buildingType[NBBUILDINGS];

// Shapes
int My_Square;
int My_Cube;

int main(int argc, char* argv[])
{
	int i;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Test moteur");
	// end of glut initializations

	glutReshapeFunc(&window_reshape);
	glutDisplayFunc(&window_display);
	glutKeyboardFunc(&window_key);
	glutKeyboardUpFunc(&window_key_up);
	glutMouseFunc(&window_mouseFunc);
	glutMotionFunc(&window_motionFunc);
	glutSpecialFunc(&window_specialDownFunc);
	glutSpecialUpFunc(&window_specialUpFunc);
	glutTimerFunc(40, &window_timer, 0);
	// end of the setting of glut's callback functions

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5,0.5,0.5, 1);
	// end of GL initializations

	initControls();
	initCamera();
	initBuildings();
	// end of the initializations
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


	//--------------------------------------------------------------------------- HERE 1-------<<<
	makeBender(chemin);
	createCity(chemin);
	free(chemin);
	//-----------------------------------------------------------------------------------------<<<

	glutMainLoop();

	return EXIT_FAILURE;
}

void initControls()
{
	int i;
	srand(time(NULL));

	for(i=0; i<4; i++)
		arrowKeys[i] = 0;
	for(i=0; i<3; i++)
		mouseButton[i] = 0;

	for (i=0; i<NBROBOTS; i++) {
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

void initCamera()
{
	int i;
	for(i=0; i<4; i++)
		cameraKeys[i] = 0;

	cameraPosition[0] = 0;
	cameraPosition[1] = 2;
	cameraPosition[2] = 5;
	follows = NBROBOTS;

	phi = -20;
	theta = -90;
	processCameraChange();
}

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

void render_scene()
{
	int i;
	// ------------------------------------------------------------------------- HERE 2-------<<<
	glRotatef(-90, 1,0,0);

	// ---------------------------------------------------------------------------------------<<<

	drawRepere();

	// -------------------------------------------------------------------------- HERE 3-------<<<
	// Robots
	for(i=0; i<NBROBOTS; i++) {
		glPushMatrix();
		glTranslatef(robot[i].position[0], robot[i].position[1], robot[i].position[2]);
		glRotatef((robot[i].angle+1.5) * 180.0 / M_PI, 0, 0, 1);
		drawBender(100, robot+i);
		glPopMatrix();
	}

	glPushMatrix();
	glCallList(10); // Displays the city
	glPopMatrix();
	//-----------------------------------------------------------------------------------------<<<

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

GLvoid window_key(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'z':
			cameraKeys[ARROW_UP] = 1;
			break;
		case 's':
			cameraKeys[ARROW_DOWN] = 1;
			break;
		case 'q':
			cameraKeys[ARROW_LEFT] = 1;
			break;
		case 'd':
			cameraKeys[ARROW_RIGHT] = 1;
			break;
		case 'c':
			follows = (follows+1)%(NBROBOTS+1);
			break;
		case ' ':
			exit(1);
			break;
        default:
            break;
	}
}

GLvoid window_key_up(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'z':
			cameraKeys[ARROW_UP] = 0;
			break;
		case 's':
			cameraKeys[ARROW_DOWN] = 0;
			break;
		case 'q':
			cameraKeys[ARROW_LEFT] = 0;
			break;
		case 'd':
			cameraKeys[ARROW_RIGHT] = 0;
			break;
        default:
            break;
	}
}

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
	{
		glPopMatrix();
	}
}

GLvoid window_motionFunc(int x, int y)
{
	if (follows == NBROBOTS && mouseButton[0])
	{
		theta += (x - mouse_pos_x)*sensitivity;
		phi -= (y - mouse_pos_y)*sensitivity;
		mouse_pos_x = x;
		mouse_pos_y = y;
		processCameraChange();
		glutPostRedisplay();
	}
}

void window_specialDownFunc(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			arrowKeys[ARROW_UP] = 1;
			break;
		case GLUT_KEY_DOWN:
			arrowKeys[ARROW_DOWN] = 1;
			break;
		case GLUT_KEY_LEFT:
			arrowKeys[ARROW_LEFT] = 1;
			break;
		case GLUT_KEY_RIGHT:
			arrowKeys[ARROW_RIGHT] = 1;
			break;
		default:
			break;
	}
}

void window_specialUpFunc(int key, int x, int y)
{
	switch(key) {
		case GLUT_KEY_UP:
			arrowKeys[ARROW_UP] = 0;
			break;
		case GLUT_KEY_DOWN:
			arrowKeys[ARROW_DOWN] = 0;
			break;
		case GLUT_KEY_LEFT:
			arrowKeys[ARROW_LEFT] = 0;
			break;
		case GLUT_KEY_RIGHT:
			arrowKeys[ARROW_RIGHT] = 0;
			break;
		default:
			break;
	}
}

GLvoid window_timer()
{
  int i, robotIndex=0;
  double speed[] = {.5, .5, .5};
  //double rotation[] = {1.0, 0.0, 1.0};
  double angleIncrement = 1.0/18.0;
  double* leftDirection;
  double tempPosition[3];

  glutTimerFunc(40,&window_timer,0);

	// Robot control
  for(robotIndex=0; robotIndex<NBROBOTS; robotIndex++)
  {
	if (robotIndex == follows)
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
		tempPosition[0] = robot[robotIndex].position[0] + speed[0]*robot[robotIndex].direction[0];
		tempPosition[1] = robot[robotIndex].position[1] + speed[1]*robot[robotIndex].direction[1];
		if (checkCollision(tempPosition, robotIndex) == 0)
		{
			robot[robotIndex].position[0] = tempPosition[0];
			robot[robotIndex].position[1] = tempPosition[1];
			setAllCoords(robot+robotIndex);
		}
	  }

	  else if (arrowKeys[ARROW_DOWN] && !arrowKeys[ARROW_UP])
	  {
		// Move backward
		tempPosition[0] = robot[robotIndex].position[0] - speed[0]*robot[robotIndex].direction[0];
		tempPosition[1] = robot[robotIndex].position[1] - speed[1]*robot[robotIndex].direction[1];
		if (checkCollision(tempPosition, robotIndex) == 0)
		{
			robot[robotIndex].position[0] = tempPosition[0];
			robot[robotIndex].position[1] = tempPosition[1];
			setAllCoords(robot+robotIndex);
		}
	  }
	}
	else // The robot is currently not being controlled by the user.
	{
		if (robot[robotIndex].endActionTime < clock()) {
			// The following action will be finished in 300ms to 2 seconds.
			robot[robotIndex].endActionTime = clock() + (rand()%17 + 3) * 100;
			// We change the robot's action.
			robot[robotIndex].action = (robot[robotIndex].action == TURNING) ? MOVING : TURNING;
			if (robot[robotIndex].action == TURNING)
				robot[robotIndex].angleDirection = (rand() % 2) * 2 - 1; // -1 or +1
		}
		if (robot[robotIndex].action == TURNING)
		{
			robot[robotIndex].angle += angleIncrement * robot[robotIndex].angleDirection;
			if (robot[robotIndex].angle>= M_PI)
				robot[robotIndex].angle -= 2*M_PI;
			else if (robot[robotIndex].angle < -M_PI)
				robot[robotIndex].angle += 2*M_PI;
			robot[robotIndex].direction[0] = cos (robot[robotIndex].angle);
			robot[robotIndex].direction[1] = sin (robot[robotIndex].angle);
		}
		else // action == MOVING
		{
			tempPosition[0] = robot[robotIndex].position[0] + speed[0]*robot[robotIndex].direction[0];
			tempPosition[1] = robot[robotIndex].position[1] + speed[1]*robot[robotIndex].direction[1];
			if (checkCollision(tempPosition, robotIndex) == 0)
			{
				robot[robotIndex].position[0] = tempPosition[0];
				robot[robotIndex].position[1] = tempPosition[1];
				setAllCoords(robot+robotIndex);
			}
			else {
				robot[robotIndex].endActionTime = clock() - 1000;
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
		cameraPosition[i] += leftDirection[i]*cameraSpeed;
	free(leftDirection);
  }
  else if (cameraKeys[ARROW_RIGHT] && !cameraKeys[ARROW_LEFT])
  {
	// Move right
	leftDirection = getDirectionToLeft();
	for(i=0; i<3; i++)
		cameraPosition[i] -= leftDirection[i]*cameraSpeed;
	free(leftDirection);
  }
  if (cameraKeys[ARROW_UP] && !cameraKeys[ARROW_DOWN])
  {
	// Move forward
	for (i=0; i<3; i++)
		cameraPosition[i] += cameraDirection[i]*cameraSpeed;
  }

  else if (cameraKeys[ARROW_DOWN] && !cameraKeys[ARROW_UP])
  {
	// Move backward
	for (i=0; i<3; i++)
		cameraPosition[i] -= cameraDirection[i]*cameraSpeed;
  }
  if (mouseButton[1] && !mouseButton[2])
  {
	cameraPosition[1] -= .5;
  }
  if (mouseButton[2] && !mouseButton[1])
  {
	cameraPosition[1] += .5;
  }
  glutPostRedisplay();
}

void processCameraChange()
{
	double r;
	if (follows != NBROBOTS)
		gluLookAt(robot[follows].position[0] - 10*robot[follows].direction[0],
				  10,
				  - robot[follows].position[1] + 10*robot[follows].direction[1],
				  robot[follows].position[0],
				  robot[follows].position[2] + 5,
				  -robot[follows].position[1],
				  0, 1, 0);
	else {
		if (phi > 89)
			phi = 89;
		else if (phi < -89)
			phi = -89;
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

int checkCollision(double robotPosition[3], int robotIndex)
{
	int i=0;
	int collision = 0;
	Object** bender = getBender(robot[robotIndex].position);
	Object** otherBender;
	Object* building;

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










