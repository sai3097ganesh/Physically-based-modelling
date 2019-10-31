#include <iostream>
#include "Mesh.h"
#include <stdlib.h>


Mesh mesh;

float h = 0.01; //step size
static const int FPS = 30;

void init(void)
{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		// Enable Z-buffering, backface culling, and lighting
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_LIGHTING);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0, 1.0, 1, 600);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Set eye point and lookat point
		gluLookAt(0, 0, 300, 0, 0, 0, 0, 1, 0);

		// Set up lights
		GLfloat light0color[] = { 0.5, 0.5, 0.5 };
		GLfloat light0pos[] = { 500, 500, 300 };
		GLfloat light1color[] = { 0.5, 0.5, 0.5 };
		GLfloat light1pos[] = { 1000, 1000, 1000 };
		glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light0color);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0color);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0color);
		glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
		glLightfv(GL_LIGHT1, GL_AMBIENT, light1color);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1color);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light1color);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	mesh.drawEdges();
	mesh.drawParticles();

	glPopMatrix();
	glutSwapBuffers();
}

void idle(void)
{
	for (float t = 0; t < 1.0 / FPS; t += h) {
		mesh.nextTimeStep(h);
	}
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
	init();
	glutPostRedisplay();
}


int main(int argc, char** argv) {
	
	mesh.MakeMesh();
	std::cout<<mesh.edges.size();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Spring mesh demo");
	init();
	glutDisplayFunc(display);
	glutTimerFunc(100, timer, 0);
	glutIdleFunc(idle);
	glutReshapeFunc(reshapeFunc);

	glutMainLoop();

	return 0;
}
