#include <iostream>

#include "Fluid.h"
#include <glut.h>
#include <ctime>

int N = 50;
float viscocity = 1, h = 0.1;

static const int FPS = 30;
const int tMAX = 10;
float timeSinceLast = 0, timeTaken;
int frameTime = 0;
clock_t initialTime = clock(), finalTime;

Fluid fluid( 50,  viscocity,  h);


void initializeField() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fluid.VelocityField[fluid.indexXY(i, j)] = { 0.0,0.0 };
			fluid.PressureField[fluid.indexXY(i, j)] = 0;
			fluid.AccelerationField[fluid.indexXY(i, j)] = { -0.5,0.0 };
			fluid.color[fluid.indexXY(i, j)] = { 0.0,0.0,0.0 };
		}
	}
}


void velocityDisplay() {

	int i, j;
	float x, y, spacing;
	spacing = 1.0f / fluid.gridSize;
	glColor3f(1.0f,1.0f,1.0f);
	glLineWidth(1.0f);
	glBegin(GL_LINES);

	for (i = 0; i < fluid.gridSize-1; i++) {
		for (j = 0; j < fluid.gridSize-1; j++) {

			x = (i + 0.5f) * spacing; y = (j + 0.5f) * spacing;
			glVertex2f(x, y);
			glVertex2f(x + fluid.VelocityField[fluid.indexXY(i, j)][0], y + fluid.VelocityField[fluid.indexXY(i, j)][1]);
		}
	}
	glEnd();
	glutSwapBuffers();
}
void idle(void)
{

	for (float t = 0; t < 1.0 / FPS; t += h) {
		fluid.timestepVelocity();
		fluid.timestepDye();
	}

	finalTime = clock();
	timeTaken = (float)((finalTime - initialTime)) / CLOCKS_PER_SEC;
	initialTime = finalTime;
	timeSinceLast += timeTaken;
	while ((timeSinceLast + (float)(clock() - initialTime) / CLOCKS_PER_SEC)  < 1.0 / FPS);

	timeSinceLast = 0;
	glutPostRedisplay();
}

void timer(int v) {
	glutTimerFunc(1000 / FPS, timer, v);
}

void reshapeFunc(GLint newWidth, GLint newHeight)
{
	if (newWidth > newHeight) // Keep a square viewport
		glViewport((newWidth - newHeight) / 2, 0, newHeight, newHeight);
	else
		glViewport(0, (newHeight - newWidth) / 2, newWidth, newWidth);
	glutPostRedisplay();
}

void display() {

	//Drawing the quads
	glBegin(GL_QUADS);
	float spacing = 1.0f / fluid.gridSize;
	for (int i = 0; i < fluid.gridSize; i++) {
		for (int j = 0; j < fluid.gridSize; j++) {
			float x = (i + 0.5f) * spacing;
			float y = (j + 0.5f) * spacing;

			glColor3f(fluid.color[fluid.indexXY(i, j)][0], fluid.color[fluid.indexXY(i, j)][1], fluid.color[fluid.indexXY(i, j)][2]);
			glVertex2f(x, y);
			glColor3f(fluid.color[fluid.indexXY(i+1, j)][0], fluid.color[fluid.indexXY(i+1, j)][1], fluid.color[fluid.indexXY(i+1, j)][2]);
			glVertex2f(x+spacing, y);
			glColor3f(fluid.color[fluid.indexXY(i+1, j+1)][0], fluid.color[fluid.indexXY(i+1, j+1)][1], fluid.color[fluid.indexXY(i+1, j+1)][2]);
			glVertex2f(x+spacing, y + spacing);
			glColor3f(fluid.color[fluid.indexXY(i, j+1)][0], fluid.color[fluid.indexXY(i, j+1)][1], fluid.color[fluid.indexXY(i, j+1)][2]);
			glVertex2f(x, y + spacing);
		}
	}

	glEnd();
	glutSwapBuffers();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	initializeField();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Stable fluids");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	
	glViewport(0, 0, 512, 512);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	glutTimerFunc(100, timer, 0);
	glutReshapeFunc(reshapeFunc);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	
	glutMainLoop();
	
	

	std::cout << "Team Turbulence";
	getchar();
}

