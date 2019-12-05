#pragma once
#include <glm/glm.hpp>
#include <stdio.h>


#define EPSILON 1.0e-5



class Fluid
{
public:
	int gridSize, totalCells;
	glm::vec2 *VelocityField, *AccelerationField;
	glm::vec3 *color;
	float viscosity, density, h;

/*
	glm::vec2* integrate(glm::vec2* u, glm::vec2* g, float h) {
		glm::vec2* w;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				w[indexXY(i, j)] = u[indexXY(i, j)] + h * g[indexXY(i, j)];
			}
		}
	}

	glm::vec2* backtrace(glm::vec2* u, float h){
		glm::vec2* w;
}
*/

	


	int indexXY(int x, int y) {
		return y*gridSize + x;
	}

	Fluid(int size, float viscocity, float h):gridSize(size), viscosity(viscocity), h(h), totalCells(size*size) {
		VelocityField = new glm::vec2[totalCells];
		AccelerationField = new glm::vec2[totalCells];
	}

	void AddForce() {
		for (int i = 0; i < totalCells; i++) {
			VelocityField[i] = h*AccelerationField[i];
		}
	}

	void advectVelocity() {
		glm::vec2 oldPos, currentPos, vel;
		glm::vec2 *newVelField = new glm::vec2[totalCells];
		
		for (int i = 1; i < gridSize - 1; i++) {
			for (int j = 1; j < gridSize - 1; j++) {

				currentPos = { i - 0.5,j - 0.5 };
				vel = bilinearInterpolation(currentPos);
				oldPos = currentPos - vel*h;
				newVelField[indexXY(i, j)] = bilinearInterpolation(oldPos);
			}
		}

		for (int i = 1; i < gridSize - 1; i++) {
			for (int j = 1; j < gridSize - 1; j++) {

				if (i == 1)
				{
					VelocityField[indexXY(i, j)][0] = 0;
				}
				else
				{
					VelocityField[indexXY(i, j)][0] = 0.5 * (newVelField[indexXY(i, j)][0]
						+ newVelField[indexXY(i - 1, j)][0]);
				}

				if (j == 1)
				{
					VelocityField[indexXY(i, j)][1] = 0;
				}
				else
				{
					VelocityField[indexXY(i, j)][1] = 0.5 * (VelocityField[indexXY(i, j)][1]
						+ VelocityField[indexXY(i, j - 1)][1]);
				}
			}
		}

		delete[] newVelField;
	}

	glm::vec2 bilinearInterpolation(glm::vec2 &pos) {
		float vel_x, vel_y;

		int x0 = static_cast<int>(floor(pos[0] + 1) + EPSILON);
		int y0 = static_cast<int>(pos[1] + 0.5 + EPSILON);
		vel_x = BI(pos, x0, y0, 0);

		// Interpolate the y component
		x0 = static_cast<int>(pos[0] + 0.5);
		y0 = static_cast<int>(floor(pos[1] + 1) + EPSILON);
		vel_y = BI(pos, x0, y0, 1);

		return glm::vec2(vel_x, vel_y);
	}

	float BI(glm::vec2 &pos, int x0, int y0, int coord) {
		return 0.25*VelocityField[indexXY(x0, y0)][coord]+ 0.25*VelocityField[indexXY(x0, y0+1)][coord]+ 0.25*VelocityField[indexXY(x0+1, y0)][coord]+ 0.25*VelocityField[indexXY(x0+1, y0+1)][coord];
	}

	~Fluid() {
		delete[] VelocityField;
		delete[] AccelerationField;
	}
};

