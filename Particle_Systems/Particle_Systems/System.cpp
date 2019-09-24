#include "System.h"



System::System()
{
	particle = new Particle[n_particles];
	for (int i = 0; i < n_particles; i++) {
		inactive[i] = n_particles - 1 - i;
	}
}

void System::clear() {
	for (int i = 0; i < n_particles; i++) {
		particle[i].active = false;
		inactive[i] = n_particles - 1 - i;
	}
}
void System::GenerateParticles() {
	for (int i = 0; i < n_generate; i++) {
		inactivecount--;
		
	}
}

void System::TestDeactivate() {
	for (int i = 0; i < n_particles; i++) {

	}
}
System::~System()
{
	delete[] particle;
}
