#pragma once
#include "Particle.h"
class System
{
	static const int n_particles = 10000;
	Particle *particle;
	int inactivecount = n_particles;
	int inactive[n_particles];
	int n_generate = 100;

public:
	System();
	void clear();
	void GenerateParticles();
	void TestDeactivate();
	void ComputeAcc();
	void integrate();
	~System();
};

