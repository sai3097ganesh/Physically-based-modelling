#include "Body.h"
#include <stdio.h>
#include <glut.h>


using namespace std;

float h = 0.01; //step size
static const int FPS = 30;
int rotateon;
int lastx, lasty;
int xchange, ychange;
float spin = 0.0;
float spinup = 0.0;

Body body("cuboid");
std::vector<glm::vec3> orientedVertices;

std::vector <glm::vec3> Vert;
std::vector<std::vector<int>> indices;
bool bounding = true;

Body body1("cuboid");

void ObjectCollision(Body *b1, Body *b2, float h) {
		
	//b1->CollisionTest(b2->vertices, b2->faces, h);
	//b2->CollisionTest(b1->vertices, b1->faces, h);
}

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
	
	if (bounding) {
		Vert.push_back(glm::vec3(100.0, -100, -100));
		Vert.push_back(glm::vec3(100.0, 100, -100));
		Vert.push_back(glm::vec3(100.0, 100, 100));
		Vert.push_back(glm::vec3(100.0, -100, 100));
		Vert.push_back(glm::vec3(-100.0, -100, -100));
		Vert.push_back(glm::vec3(-100.0, 100, -100));
		Vert.push_back(glm::vec3(-100.0, 100, 100));
		Vert.push_back(glm::vec3(-100.0, -100, 100));
		indices.push_back({ 0,1,2,3 });
		indices.push_back({ 4,5,6,7 });
		//indices.push_back({ 1,2,6,5 });
		//indices.push_back({ 0,3,7,4 });
		
		bounding = false;
		body1.p = {-10.0,0,0};
		body.X = { -100,0,0 };
		body1.X = { 100,0,0 };
		body1.L = { -4000,0,0 };
	}
	//printf("%d ", indices.size());
}

void drawBody(Body body) {

	glPushMatrix();
	orientedVertices = body.getOrientatedVertices();
	for (int i = 0; i < body.faces.size();i++) {
		
		/*
		glBegin(GL_POLYGON);
		glColor3f(0.0, 0.0, 0.5);
		glVertex3f(body.X[0] + orientedVertices[body.faces[i][0]][0], body.X[1] + orientedVertices[body.faces[i][0]][1], body.X[2] + orientedVertices[body.faces[i][0]][2]);
		glVertex3f(body.X[0] + orientedVertices[body.faces[i][1]][0], body.X[1] + orientedVertices[body.faces[i][1]][1], body.X[2] + orientedVertices[body.faces[i][1]][2]);
		glVertex3f(body.X[0] + orientedVertices[body.faces[i][3]][0], body.X[1] + orientedVertices[body.faces[i][3]][1], body.X[2] + orientedVertices[body.faces[i][3]][2]);
		glVertex3f(body.X[0] + orientedVertices[body.faces[i][2]][0], body.X[1] + orientedVertices[body.faces[i][2]][1], body.X[2] + orientedVertices[body.faces[i][2]][2]);
		glEnd();
		*/

		glLineWidth(3.0);
		GLfloat lineColor[3] = { 0.0,0.3,0.0 };
		glBegin(GL_LINE_STRIP);
		glMaterialfv(GL_FRONT, GL_AMBIENT, lineColor);
		glVertex3f(body.X[0] + orientedVertices[body.faces[i][0]][0], body.X[1] + orientedVertices[body.faces[i][0]][1], body.X[2] + orientedVertices[body.faces[i][0]][2]);
		glVertex3f(body.X[0] + orientedVertices[body.faces[i][1]][0], body.X[1] + orientedVertices[body.faces[i][1]][1], body.X[2] + orientedVertices[body.faces[i][1]][2]);
		glVertex3f(body.X[0] + orientedVertices[body.faces[i][3]][0], body.X[1] + orientedVertices[body.faces[i][3]][1], body.X[2] + orientedVertices[body.faces[i][3]][2]);
		glVertex3f(body.X[0] + orientedVertices[body.faces[i][2]][0], body.X[1] + orientedVertices[body.faces[i][2]][1], body.X[2] + orientedVertices[body.faces[i][2]][2]);
		glVertex3f(body.X[0] + orientedVertices[body.faces[i][0]][0], body.X[1] + orientedVertices[body.faces[i][0]][1], body.X[2] + orientedVertices[body.faces[i][0]][2]);
		glEnd();
	}
	glPopMatrix();
}

void drawBounding() {
	glPushMatrix();
	
	for (int i = 0; i < indices.size(); i++) {

		glBegin(GL_POLYGON);
		glColor3f(0.3, 0.3, 0.);
		
		for (int j = 0; j < indices[i].size(); j++) {
			glVertex3f(Vert[indices[i][j]][0], Vert[indices[i][j]][1], Vert[indices[i][j]][2]);
		}
		glVertex3f(Vert[indices[i][0]][0], Vert[indices[i][0]][1], Vert[indices[i][0]][2]);
		glEnd();

		glLineWidth(3.0);
		GLfloat lineColor[3] = { 0.3,0.3,0.0 };
		glBegin(GL_LINE_STRIP);
		glMaterialfv(GL_FRONT, GL_AMBIENT, lineColor);

		for (int j = 0; j < indices[i].size(); j++) {
			glVertex3f(Vert[indices[i][j]][0], Vert[indices[i][j]][1], Vert[indices[i][j]][2]);
		}
		glVertex3f(Vert[indices[i][0]][0], Vert[indices[i][0]][1], Vert[indices[i][0]][2]);

		glEnd();
	}
	glPopMatrix();
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	glRotatef(spinup, 1.0, 0.0, 0.0);
	glRotatef(spin, 0.0, 1.0, 0.0);

	drawBody(body);
	drawBody(body1);
	//drawBounding();

	glPopMatrix();
	glutSwapBuffers();
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

void idle(void)
{
	
	if (rotateon) {
		spin += xchange / 250.0;
		if (spin >= 360.0) spin -= 360.0;
		if (spin < 0.0) spin += 360.0;
		spinup -= ychange / 250.0;
		if (spinup > 89.0) spinup = 89.0;
		if (spinup < -89.0) spinup = -89.0;
	}

	for (float t = 0; t < 1.0 / FPS; t += h) {
		
		//body.CollisionTest(Vert, indices, h);
		ObjectCollision(&body, &body1, h);
		body.RK4step(h);
		body.update();

		body1.RK4step(h);
		body1.update();
		
	}
	glutPostRedisplay();
}

void motion(int x, int y)
{
	xchange = x - lastx;
	ychange = y - lasty;
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			lastx = x;
			lasty = y;
			xchange = 0;
			ychange = 0;
			rotateon = 1;
		}
		else if (state == GLUT_UP) {
			xchange = 0;
			ychange = 0;
			rotateon = 0;
		}
		break;

	default:
		break;
	}
}

int main(int argc, char** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Rigid Body demo");

	init();
	glutDisplayFunc(display);
	glutTimerFunc(100, timer, 0);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutIdleFunc(idle);
	glutReshapeFunc(reshapeFunc);

	glutMainLoop();

	return 0;
}