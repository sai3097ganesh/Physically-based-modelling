#include <iostream>

#include "Fluid.h"

int N = 50;
float viscocity = 1, h = 0.1;

Fluid fluid( 50,  viscocity,  h);

int main() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fluid.VelocityField[fluid.indexXY(i, j)] = { 0.0,0.0 };
			fluid.PressureField[fluid.indexXY(i, j)] = 0;
			fluid.AccelerationField[fluid.indexXY(i, j)] = { 0.0,0.0 };
		}
	}
	fluid.timestepVelocity();
	fluid.timestepDye();
	std::cout << "Team Turbulence";
	getchar();
}

