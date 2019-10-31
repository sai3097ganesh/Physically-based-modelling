#pragma once
#include "Particle.h"
#include "Edge.h"
#include <vector>
#include <glut.h>

class Mesh
{
	
public:
	std::vector<Particle> particles;
	std::vector<Edge> edges;

	void insertEdge(Particle *p1, Particle *p2) { edges.push_back(Edge(p1,p2)); }

	void MakeMesh() {
		glm::vec3 p1 = { 0.0f,0.0f,0.0f }, p2 = { 100.0f,150.0f,0.0f }, p3 = { 150,0,0 };
		particles.push_back(Particle(p1)); particles.push_back(Particle(p2)); particles.push_back(Particle(p3));
		particles[0].V = { -1.0,0,0 };
		
		insertEdge(&particles[0], &particles[1]);
		insertEdge(&particles[1], &particles[2]);
		insertEdge(&particles[0], &particles[2]);
	
	}

	void nextTimeStep(float h) {
		for (int i = 0; i < edges.size(); i++) {
			edges[i].applyConstraintForce();
		}
		for (int i = 0; i < particles.size(); i++) {
			particles[i].RK4step(h);
		}
	}

	void drawEdges() {
		glLineWidth(3.0);
		GLfloat lineColor[3] = { 1.0,1.0,1.0 };
		glBegin(GL_LINES);
		glMaterialfv(GL_FRONT, GL_AMBIENT, lineColor);
	
		for (int i = 0; i < edges.size(); i++) {
			glVertex3f(edges[i].p1->X[0], edges[i].p1->X[1], edges[i].p1->X[2]);
			glVertex3f(edges[i].p2->X[0], edges[i].p2->X[1], edges[i].p2->X[2]);
		}
		glEnd();
	}

	void drawParticles() {
		GLfloat particleColor[3] = { 0.0,1.0,1.0 };
		for (int i = 0; i < particles.size(); i++) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, particleColor);
			glPushMatrix();
			glTranslatef(particles[i].X[0], particles[i].X[1], particles[i].X[2]);
			glutSolidSphere(5, 20, 20);
			glPopMatrix();
		}
	}

	Mesh();
	~Mesh();
};

