#pragma once
#include "Particle.h"
class Edge
{
public:
	float length, restLength, actualDistance, k=0.1, d=0.01;
	Particle *p1, *p2;
	Edge(Particle *p1, Particle *p2) : p1(p1), p2(p2) {
		restLength = (p1->X - p2->X).length();
	};
	void applyConstraintForce() {
		glm::vec3 f;
		actualDistance = (p1->X - p2->X).length();
		f = k*(1 - restLength/ actualDistance)*(p1->X-p2->X);
		f += d*glm::dot((p1->V - p2->V), (p1->X - p2->X)) * (p1->X - p2->X) / (actualDistance*actualDistance);
		p2->f += f; p1->f -= f;
	}
	~Edge();
};

