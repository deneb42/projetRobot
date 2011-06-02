#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float angle_z=0;
float angle_y=0;
float angle_x=0;
float posi_x=0;
float posi_y=0;
float posi_z=0;
float zoom=5;
int mouse_pos_x = 0, mouse_pos_y = 0;
short mouse_down_is_left = 0;

// Camera
double cameraPosition[3];
double cameraTarget[3];

// Shapes
int My_Square;
int My_Cube;

// Controls
int ARROW_UP = 0;
int ARROW_DOWN = 1;
int ARROW_LEFT = 2;
int ARROW_RIGHT = 3;
int arrowKeys[4];

// Robot
double position[3];
double direction[3];
double angle;

// Functions
void initControls();
void initCamera();
void init_scene();
void updateCameraPosition();
void render_scene();
//void createBender();
void make_square();
void make_cube();
void drawRepere();

GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
GLvoid window_mouseFunc(int button, int state, int x, int y);
GLvoid window_motionFunc(int x, int y);
GLvoid window_timer();
void window_specialDownFunc(int key, int x, int y);
void window_specialUpFunc(int key, int x, int y);

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Test moteur");
	// end of glut initializations

	glutReshapeFunc(&window_reshape);
	glutDisplayFunc(&window_display);
	glutKeyboardFunc(&window_key);
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
	//createBender();
	make_square();
	make_cube();

	//-----------------------------------------------------------------------------------------<<<

	glutMainLoop();

	return EXIT_FAILURE;
}

void render_scene() {
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

GLvoid window_display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	updateCameraPosition();
	render_scene();

	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-zoom, zoom, -zoom, zoom, -10*zoom, 10*zoom);
	glMatrixMode(GL_MODELVIEW);
	updateCameraPosition();
}

GLvoid window_key(unsigned char key, int x, int y) {
	double diff[3];
	double norme = 0.0;
	int i;
	switch(key)
	{
		case 'z':
			for (i=0; i<3; i++) {
				diff[i] = cameraPosition[i] - cameraTarget[i];
				norme += diff[i]*diff[i];
			}
			norme = sqrt(norme);
			for (i=0; i<3; i++) {
				printf("%f  ", diff[i] / norme);
				cameraPosition[i] += diff[i] / norme;
				cameraTarget[i] += diff[i] / norme;
			}
			for (i=0; i<3; i++)
				printf("%f  ", cameraPosition[i]);
			printf("\n");
			break;
		case 's':
			for (i=0; i<3; i++) {
				diff[i] = cameraPosition[i] - cameraTarget[i];
				norme += diff[i]*diff[i];
			}
			norme = sqrt(norme);
			for (i=0; i<3; i++) {
				printf("%f  ", diff[i] / norme);
				cameraPosition[i] -= diff[i] / norme;
				cameraTarget[i] -= diff[i] / norme;
			}
			for (i=0; i<3; i++)
				printf("%f  ", cameraPosition[i]);
			printf("\n");
			break;
		case 'q':
			posi_x+=0.1;
			cameraPosition[0] -= 0.3;
			cameraTarget[0] -= 0.3;
			break;
		case 'd':
			posi_x-=0.1;
			cameraPosition[0] += 0.3;
			cameraTarget[0] += 0.3;
			break;
		case 'r':
			angle_x=0;
			angle_y=0;
			angle_z=0;
			posi_x=0;
			posi_y=0;
			posi_z=0;
			zoom=5;
			window_reshape(400, 400);
			break;
		case 'a':
			zoom+=0.1;
			window_reshape(400, 400);
			break;
		case 'e':
			zoom-=0.1;
			window_reshape(400, 400);
			break;
		case ' ':
			exit(1);
			break;
        default:
            break;
	}
	glutPostRedisplay();
}

GLvoid window_mouseFunc(int button, int state, int x, int y) {
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		mouse_pos_x = x;
		mouse_pos_y = y;
		mouse_down_is_left = 1;
		glPushMatrix();
	 }
	else {
		mouse_down_is_left = 0;
		glPopMatrix();
	  }
}

GLvoid window_motionFunc(int x, int y) {
	if( !mouse_down_is_left )
	return;

	angle_z += y - mouse_pos_y;
	angle_y += x - mouse_pos_x;
	mouse_pos_x = x;
	mouse_pos_y = y;

	glutPostRedisplay();
}

void drawRepere() {
	glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex3f(-10,0,0);
		glColor3f(1,0,0);
		glVertex3f(0, 0, 0);
		glColor3f(1,0,0);
		glVertex3f(0, 0, 0);
		glColor3f(1,1,1);
		glVertex3f(10, 0, 0);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex3f(0,-10,0);
		glColor3f(0,1,0);
		glVertex3f(0,0, 0);
		glColor3f(0,1,0);
		glVertex3f(0,0, 0);
		glColor3f(1,1,1);
		glVertex3f(0, 10, 0);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex3f(0,0,-10);
		glColor3f(0,0,1);
		glVertex3f(0, 0, 0);
		glColor3f(0,0,1);
		glVertex3f(0, 0, 0);
		glColor3f(1,1,1);
		glVertex3f(0, 0, 10);
	glEnd();
}

void make_square() {
  My_Square = 4;
  glNewList(My_Square, GL_COMPILE);
    glBegin(GL_POLYGON);
      glVertex3f(0, 0, 0);
      glVertex3f(1, 0, 0);
      glVertex3f(1, 1, 0);
      glVertex3f(0, 1, 0);
    glEnd();
  glEndList();
}

void make_cube() {
  My_Cube = 5;

  glNewList(My_Cube, GL_COMPILE);
    glTranslatef(-0.5, -0.5, 0.5);

    glColor3f(1, 0, 0);
    glCallList(My_Square);

    glColor3f(1, 1, 0);
    glPushMatrix();
    glTranslatef(0, 0, -1);
    glCallList(My_Square);
    glPopMatrix();

    glColor3f(0, 1, 0);
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glCallList(My_Square);
    glPopMatrix();

    glColor3f(0, 1, 1);
    glPushMatrix();
    glTranslatef(1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glCallList(My_Square);
    glPopMatrix();

    glColor3f(0, 0, 1);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glCallList(My_Square);
    glPopMatrix();

    glColor3f(1, 0, 1);
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    glCallList(My_Square);
    glPopMatrix();
  glEndList();

}

void initControls() {
	int i;
	for(i=0; i<4; i++) {
		arrowKeys[i] = 0;
		position[i] = 0;
	}
	direction[0] = 1.0;
	direction[1] = 0.0;
	direction[2] = 0.0;
	angle = 0.0;
}

void initCamera() {
	cameraPosition[0] = 1;
	cameraPosition[1] = 1;
	cameraPosition[2] = 1;

	cameraTarget[0] = 0;
	cameraTarget[1] = 0;
	cameraTarget[2] = 0;
	updateCameraPosition();
}

void updateCameraPosition() {
	gluLookAt(cameraPosition[0],
			  cameraPosition[1],
			  cameraPosition[2],
			  cameraTarget[0],
			  cameraTarget[1],
			  cameraTarget[2],
			  0, 1, 0);
}

void window_specialDownFunc(int key, int x, int y) {
	switch(key) {
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

GLvoid window_timer() {
  int i;
  double speed[] = {.5, .5, .5};
  double rotation[] = {1.0, 0.0, 1.0};
  double angleIncrement = 1.0/18.0;
  glutTimerFunc(40,&window_timer,0);

  if (arrowKeys[ARROW_LEFT] && !arrowKeys[ARROW_RIGHT]) {
  	// Turn left
	angle += angleIncrement;
	if (angle>= M_PI)
		angle -= 2*M_PI;
	direction[0] = cos (angle);
	direction[1] = sin (angle);
  }
  if (arrowKeys[ARROW_RIGHT] && !arrowKeys[ARROW_LEFT]) {
	// Turn right
	angle -= angleIncrement;
	if (angle < -M_PI)
		angle += 2*M_PI;
	direction[0] = cos (angle);
	direction[1] = sin (angle);
  }

  if (arrowKeys[ARROW_UP] && !arrowKeys[ARROW_DOWN]) {
	// Move forward
	position[0] += speed[0]*direction[0];
	position[1] += speed[1]*direction[1];
  }
  if (arrowKeys[ARROW_DOWN] && !arrowKeys[ARROW_UP]) {
	// Move backward
	position[0] -= speed[0]*direction[0] / 2;
	position[1] -= speed[1]*direction[1] / 2;
  }
  glutPostRedisplay();
}
