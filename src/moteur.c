#include "moteur.h"
#include "collisions.h"
#define NBROBOTS 2
float angle_z=0;
float angle_y=0;
float angle_x=0;
float posi_x=0;
float posi_y=0;
float posi_z=0;
float zoom=5;
int mouse_pos_x = 0, mouse_pos_y = 0;
short mouse_down_is_left = 0;

char *chemin;

// Controls
int ARROW_UP = 0;
int ARROW_DOWN = 1;
int ARROW_LEFT = 2;
int ARROW_RIGHT = 3;
int arrowKeys[4];

// Camera
double cameraPosition[3];
double cameraDirection[3];
double phi;
double theta;
double sensitivity = .5;
double cameraSpeed = .2;
int cameraKeys[4];
int follows;

// Robot
double position[NBROBOTS][3];
double direction[NBROBOTS][3];
double angle[NBROBOTS];

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
	free(chemin);

	//-----------------------------------------------------------------------------------------<<<

	glutMainLoop();

	return EXIT_FAILURE;
}

void initControls()
{
	int i;
	for(i=0; i<4; i++)
	{
		arrowKeys[i] = 0;
	}
	for (i=0; i<NBROBOTS; i++) {
		position[i][0] = 0+i*5;
		position[i][1] = 0+i*5;
		position[i][2] = 0;
		direction[i][0] = 1.0;
		direction[i][1] = 0.0;
		direction[i][2] = 0.0;
		angle[i] = 0.0;
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

void render_scene()
{
	int i;
	// ------------------------------------------------------------------------- HERE 2-------<<<
	glRotatef(-90, 1,0,0);

	// ---------------------------------------------------------------------------------------<<<

	drawRepere();

	// -------------------------------------------------------------------------- HERE 3-------<<<
	// Robot
	for(i=0; i<NBROBOTS; i++) {
		glPushMatrix();
		glTranslatef(position[i][0], position[i][1], position[i][2]);
		glRotatef((angle[i]+1.5) * 180.0 / M_PI, 0, 0, 1);
		if (i == follows)
			drawBender(100);
		else
			drawBender(30);
		glPopMatrix();
	}

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
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_pos_x = x;
		mouse_pos_y = y;
		mouse_down_is_left = 1;
		glPushMatrix();
	 }
	else
	{
		mouse_down_is_left = 0;
		glPopMatrix();
	}
}

GLvoid window_motionFunc(int x, int y)
{
	if (follows == NBROBOTS)
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

void window_specialUpFunc(int key, int x, int y) {
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
  double rotation[] = {1.0, 0.0, 1.0};
  double angleIncrement = 1.0/18.0;
  double* leftDirection;
  double tempPosition[3];
  int collision;
  Object *bender, *object;

  glutTimerFunc(40,&window_timer,0);

	// Robot control
  for(robotIndex=0; robotIndex<NBROBOTS; robotIndex++)
  {
	if (robotIndex == follows)
	{
	  if (arrowKeys[ARROW_LEFT] && !arrowKeys[ARROW_RIGHT])
	  {
		// Turn left
		angle[robotIndex] += angleIncrement;
		if (angle[robotIndex]>= M_PI)
			angle[robotIndex] -= 2*M_PI;
		direction[robotIndex][0] = cos (angle[robotIndex]);
		direction[robotIndex][1] = sin (angle[robotIndex]);
	  }
	  else if (arrowKeys[ARROW_RIGHT] && !arrowKeys[ARROW_LEFT])
	  {
		// Turn right
		angle[robotIndex] -= angleIncrement;
		if (angle[robotIndex] < -M_PI)
			angle[robotIndex] += 2*M_PI;
		direction[robotIndex][0] = cos (angle[robotIndex]);
		direction[robotIndex][1] = sin (angle[robotIndex]);
	  }

	  if (arrowKeys[ARROW_UP] && !arrowKeys[ARROW_DOWN])
	  {
		// Move forward
		i=0;
		collision = 0;
		tempPosition[0] = position[robotIndex][0] + speed[0]*direction[robotIndex][0];
		tempPosition[1] = position[robotIndex][1] + speed[1]*direction[robotIndex][1];

		bender = getBender(tempPosition);
		for(i = 0; i<NBROBOTS && collision == 0; i++)
		{
			if (i != robotIndex)
			{
				object = getBender(position[i]);
				if (inCollision(bender, object))
					collision = 1;
				free(object);
			}
		}
		free(bender);
		if (collision == 0)
		{
			position[robotIndex][0] = tempPosition[0];
			position[robotIndex][1] = tempPosition[1];
		}
	  }

	  else if (arrowKeys[ARROW_DOWN] && !arrowKeys[ARROW_UP])
	  {
		// Move backward
		i=0;
		collision = 0;
		tempPosition[0] = position[robotIndex][0] - speed[0]*direction[robotIndex][0];
		tempPosition[1] = position[robotIndex][1] - speed[1]*direction[robotIndex][1];

		bender = getBender(tempPosition);
		for(i = 0; i<NBROBOTS && collision == 0; i++)
		{
			if (i != robotIndex)
			{
				object = getBender(position[i]);
				if (inCollision(bender, object))
					collision = 1;
				free(object);
			}
		}
		free(bender);
		if (collision == 0)
		{
			position[robotIndex][0] = tempPosition[0];
			position[robotIndex][1] = tempPosition[1];
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
  glutPostRedisplay();
}


void processCameraChange()
{
	double r;
	int i;
	if (follows != NBROBOTS)
		gluLookAt(position[follows][0] - 10*direction[follows][0],
				  10,
				  - position[follows][1] + 10*direction[follows][1],
				  position[follows][0],
				  position[follows][2] + 5,
				  -position[follows][1],
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

double* getDirectionToLeft() {
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












