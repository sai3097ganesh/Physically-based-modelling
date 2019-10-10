#pragma once
#include "Boid.h"
#include <math.h>
#include <Windows.h>
#include <cmath>
#include <iostream>
#include <time.h>
#include <random>
#include "geometry.h"

#define PI 3.14159265

class Flock
{
public:
	static const int n_Boids = 200;
	Boid *boid;
	int inactivecount = n_Boids;
	int inactive[n_Boids];
	int n_generate = 1;
	float newPos[n_Boids][3];
	float timestepmain[n_Boids], f;
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
	float distance_from_center;
	float vnorm[3];
	Point origin, newpos[n_Boids], oldpos[n_Boids], face[3];
	float P_velocity;

	Flock();
	void clear();
	void GenerateBoidsPoint();
	void GenerateBoidsDisc(float x, float y, float z, float rad);
	void GenerateBoidsRectangle();
	void TestDeactivate();
	void ComputeAccAlign();
	void ComputeAccCohesion();
	void integrate(float h, Point *wall, Point * unit_normal, int n_faces);
	void GenerateBoids(int no_times);

	~Flock();
};

