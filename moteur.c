#include "moteur.h"

float angle_z=0;
float angle_y=0;
float angle_x=0;
float posi_x=0;
float posi_y=0;
float posi_z=0;
float zoom=5;
int mouse_pos_x = 0, mouse_pos_y = 0;
short mouse_down_is_left = 0;

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

// Robot
double position[3];
double direction[3];
double angle;

int main(int argc, char* argv[])
{
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
	// end of ours initializations

	//--------------------------------------------------------------------------- HERE 1-------<<<
	make_square();
	make_cube();

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
		position[i] = 0;
	}
	direction[0] = 1.0;
	direction[1] = 0.0;
	direction[2] = 0.0;
	angle = 0.0;
}

void initCamera()
{
	int i;
	for(i=0; i<4; i++)
		cameraKeys[i] = 0;

	cameraPosition[0] = 0;
	cameraPosition[1] = 2;
	cameraPosition[2] = 5;

	phi = -20;
	theta = -90;
	processCameraChange();
}

void render_scene()
{
	// ------------------------------------------------------------------------- HERE 2-------<<<
	glRotatef(-90, 1,0,0);

	// ---------------------------------------------------------------------------------------<<<

	drawRepere();

	// -------------------------------------------------------------------------- HERE 3-------<<<
	// Cube
	glPushMatrix();
	glTranslatef(position[0], position[1], position[2]);
	glRotatef(angle * 180.0 / M_PI, 0, 0, 1);
	glCallList(My_Cube);
	glPopMatrix();

	// Sphere showing the direction of the robot.
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(position[0] + direction[0],
				 position[1] + direction[1],
				 position[2]);
	glutSolidSphere(0.2, 50, 50);
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
	if( !mouse_down_is_left )
		return;

	theta += (x - mouse_pos_x)*sensitivity;
	phi -= (y - mouse_pos_y)*sensitivity;
	mouse_pos_x = x;
	mouse_pos_y = y;
	processCameraChange();
	glutPostRedisplay();
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
  int i;
  double speed[] = {.5, .5, .5};
  double rotation[] = {1.0, 0.0, 1.0};
  double angleIncrement = 1.0/18.0;
  glutTimerFunc(40,&window_timer,0);
  double* leftDirection;

	// Robot control
  if (arrowKeys[ARROW_LEFT] && !arrowKeys[ARROW_RIGHT])
  {
  	// Turn left
	angle += angleIncrement;
	if (angle>= M_PI)
		angle -= 2*M_PI;
	direction[0] = cos (angle);
	direction[1] = sin (angle);
  }
  else if (arrowKeys[ARROW_RIGHT] && !arrowKeys[ARROW_LEFT])
  {
	// Turn right
	angle -= angleIncrement;
	if (angle < -M_PI)
		angle += 2*M_PI;
	direction[0] = cos (angle);
	direction[1] = sin (angle);
  }

  if (arrowKeys[ARROW_UP] && !arrowKeys[ARROW_DOWN])
  {
	// Move forward
	position[0] += speed[0]*direction[0];
	position[1] += speed[1]*direction[1];
  }

  else if (arrowKeys[ARROW_DOWN] && !arrowKeys[ARROW_UP])
  {
	// Move backward
	position[0] -= speed[0]*direction[0] / 2;
	position[1] -= speed[1]*direction[1] / 2;
  }


  // Camera control
  if (cameraKeys[ARROW_LEFT] && !cameraKeys[ARROW_RIGHT])
  {
  	// Move left
	leftDirection = getDirectionToLeft();
	for(i=0; i<3; i++)
		cameraPosition[i] += leftDirection[i]*cameraSpeed;
  }
  else if (cameraKeys[ARROW_RIGHT] && !cameraKeys[ARROW_LEFT])
  {
	// Move right
	leftDirection = getDirectionToLeft();
	for(i=0; i<3; i++)
		cameraPosition[i] -= leftDirection[i]*cameraSpeed;
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


void processCameraChange() {
	double r;
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

double* getDirectionToLeft() {
	double up[3] = {0, 1, 0};
	double left[3];
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












