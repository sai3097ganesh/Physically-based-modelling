#pragma once
#include "Particle.h"
#include <math.h>
#include <Windows.h>
#include <cmath>
#include <iostream>
#include <time.h>
#include "geometry.h"

class System
{
public:
	static const int n_particles = 10000;
	Particle *particle;
	int inactivecount = n_particles;
	int inactive[n_particles];
	int n_generate = 1;
	float newPos[n_particles][3];
	float timestepmain[n_particles], f;
	float d = 0.5; //air resistance constant
	float wind[3] = { 0.0,0.0,0.0 };
	float mu = 0.1; //friction constant
	float boxxl = -100;
	float boxxh = 100;
	float boxyl = -100;
	float boxyh = 100;
	float boxzl = -100;
	float boxzh = 100;
	char Gravity = 'y';
	Point origin, newpos[10000];

	System();
	void clear();
	void GenerateParticles();
	void TestDeactivate();
	void ComputeAcc();
	void integrate(float h, Point *wall, Plane * const P);
	~System();
};

