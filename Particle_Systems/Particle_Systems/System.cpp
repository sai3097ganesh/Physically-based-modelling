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
		//make the particle active 
		particle[inactive[inactivecount - 1]].active = true;
		//initialize the velocities of the particles
		particle[inactive[inactivecount - 1]].init();
		//popping the inactive array
		inactive[inactivecount - 1] = inactive[inactivecount];
		inactivecount--;
	}
}

void System::TestDeactivate() {
	for (int i = 0; i < n_particles; i++) {
		if (particle[i].active == true) {
			if (particle[i].lifespan < 1) {
				particle[i].active = false;
				inactive[inactivecount] = i;
				inactivecount++;
			}
		}
	}
}
void System::ComputeAcc() {
	for (int i = 0; i < n_particles; i++) {
		if (particle[i].active == true) {

		}
	}
}

void System::integrate(float h) {

	//Find what would be the new position
	for (int j = 0; j < n_particles; j++) {
		if (particle[j].active == true) {
			for (int i = 0; i < 3; i++) {
				newPos[j][i] = particle[j].getPos()[i] + h*particle[j].velocity[i];
			}
			timestepmain[j] = h;
		}
	}

	float tangent_vector;
	//Checking whether the particle would collide in the next time step

	for (int k = 0; k < n_particles; k++) {

		while (timestepmain[k] > 0) {

			if (newPos[k][0] > (boxxh - 10)) {

				f = ((boxxh - 10) - particle[k].getPos()[0]) / (newPos[k][0] - particle[k].getPos()[0]);
				particle[k].update(f*h, d, wind, Gravity);
				for (int i = 0; i < 3; i++) {
					newPos[k][i] = particle[k].getPos()[i];
				}
				particle[k].velocity[0] = -particle[k].velocity[0];
				tangent_vector = sqrt((particle[k].velocity[1] * particle[k].velocity[1]) + (particle[k].velocity[2] * particle[k].velocity[2]));
				if (tangent_vector != 0) {
					particle[k].velocity[1] = particle[k].velocity[1] - min(mu*abs(particle[k].velocity[0]), tangent_vector)*particle[k].velocity[1] / tangent_vector;
					particle[k].velocity[2] = particle[k].velocity[2] - min(mu*abs(particle[k].velocity[0]), tangent_vector)*particle[k].velocity[2] / tangent_vector;
				}
				timestepmain[k] = (1 - f)*timestepmain[k];
			}
			else if (newPos[k][0] < (boxxl + 10)) {

				f = ((boxxl + 10) - particle[k].getPos()[0]) / (newPos[k][0] - particle[k].getPos()[0]);
				particle[k].update(f*h, d, wind, Gravity);
				for (int i = 0; i < 3; i++) {
					newPos[k][i] = particle[k].getPos()[i];
				}
				particle[k].velocity[0] = -particle[k].velocity[0];
				tangent_vector = sqrt((particle[k].velocity[1] * particle[k].velocity[1]) + (particle[k].velocity[2] * particle[k].velocity[2]));
				if (tangent_vector != 0) {
					particle[k].velocity[1] = particle[k].velocity[1] - min(mu*abs(particle[k].velocity[0]), tangent_vector)*particle[k].velocity[1] / tangent_vector;
					particle[k].velocity[2] = particle[k].velocity[2] - min(mu*abs(particle[k].velocity[0]), tangent_vector)*particle[k].velocity[2] / tangent_vector;
				}
				timestepmain[k] = (1 - f)*timestepmain[k];
			}
			else if (newPos[k][1] > (boxyh - 10)) {

				f = ((boxyh - 10) - particle[k].getPos()[1]) / (newPos[k][1] - particle[k].getPos()[1]);
				particle[k].update(f*h, d, wind, Gravity);
				for (int i = 0; i < 3; i++) {
					newPos[k][i] = particle[k].getPos()[i];
				}
				particle[k].velocity[1] = -particle[k].velocity[1];
				tangent_vector = sqrt((particle[k].velocity[0] * particle[k].velocity[0]) + (particle[k].velocity[2] * particle[k].velocity[2]));
				if (tangent_vector != 0) {
					particle[k].velocity[0] = particle[k].velocity[0] - min(mu*abs(particle[k].velocity[1]), tangent_vector)*particle[k].velocity[0] / tangent_vector;
					particle[k].velocity[2] = particle[k].velocity[2] - min(mu*abs(particle[k].velocity[1]), tangent_vector)*particle[k].velocity[2] / tangent_vector;
				}
				timestepmain[k] = (1 - f)*timestepmain[k];
			}
			else if (newPos[k][1] < (boxyl + 10)) {
				f = ((boxyl + 10) - particle[k].getPos()[1]) / (newPos[k][1] - particle[k].getPos()[1]);
				particle[k].update(f*h, d, wind, Gravity);
				for (int i = 0; i < 3; i++) {
					newPos[k][i] = particle[k].getPos()[i];
				}
				particle[k].velocity[1] = -particle[k].velocity[1];
				tangent_vector = sqrt((particle[k].velocity[0] * particle[k].velocity[0]) + (particle[k].velocity[2] * particle[k].velocity[2]));
				if (tangent_vector != 0) {
					particle[k].velocity[0] = particle[k].velocity[0] - min(mu*abs(particle[k].velocity[1]), tangent_vector)*particle[k].velocity[0] / tangent_vector;
					particle[k].velocity[2] = particle[k].velocity[2] - min(mu*abs(particle[k].velocity[1]), tangent_vector)*particle[k].velocity[2] / tangent_vector;
				}
				timestepmain[k] = (1 - f)*timestepmain[k];
			}
			else if (newPos[k][2] > (boxzh - 10)) {
				f = ((boxzh - 10) - particle[k].getPos()[2]) / (newPos[k][2] - particle[k].getPos()[2]);
				particle[k].update(f*h, d, wind, Gravity);
				for (int i = 0; i < 3; i++) {
					newPos[k][i] = particle[k].getPos()[i];
				}
				particle[k].velocity[2] = -particle[k].velocity[2];
				tangent_vector = sqrt((particle[k].velocity[0] * particle[k].velocity[0]) + (particle[k].velocity[1] * particle[k].velocity[1]));
				if (tangent_vector != 0) {
					particle[k].velocity[0] = particle[k].velocity[0] - min(mu*abs(particle[k].velocity[2]), tangent_vector)*particle[k].velocity[0] / tangent_vector;
					particle[k].velocity[1] = particle[k].velocity[1] - min(mu*abs(particle[k].velocity[2]), tangent_vector)*particle[k].velocity[1] / tangent_vector;
				}
				timestepmain[k] = (1 - f)*timestepmain[k];

			}
			else if (newPos[k][2] < (boxzl + 10)) {
				f = ((boxzl + 10) - particle[k].getPos()[2]) / (newPos[k][2] - particle[k].getPos()[2]);
				particle[k].update(f*h, d, wind, Gravity);
				for (int i = 0; i < 3; i++) {
					newPos[k][i] = particle[k].getPos()[i];
				}
				particle[k].velocity[2] = -particle[k].velocity[2];
				tangent_vector = sqrt((particle[k].velocity[0] * particle[k].velocity[0]) + (particle[k].velocity[1] * particle[k].velocity[1]));
				if (tangent_vector != 0) {
					particle[k].velocity[0] = particle[k].velocity[0] - min(mu*abs(particle[k].velocity[2]), tangent_vector)*particle[k].velocity[0] / tangent_vector;
					particle[k].velocity[1] = particle[k].velocity[1] - min(mu*abs(particle[k].velocity[2]), tangent_vector)*particle[k].velocity[1] / tangent_vector;
				}
				timestepmain[k] = (1 - f)*timestepmain[k];

			}

			if (timestepmain[k] != 0) //if not just update the state to the next time step
			{

				particle[k].update(timestepmain[k], d, wind, Gravity);

				timestepmain[k] = 0;
			}

		}
	}//End of for loop
}
System::~System()
{
	delete[] particle;
}
