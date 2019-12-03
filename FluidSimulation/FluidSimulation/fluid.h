#pragma once
#include <glm/glm.hpp>

static int N = 50;

int indexXY(int x, int y) {
	return y*N + x;
}

class fluid
{
	glm::vec2 *V, *P;
	glm::vec3 *color;
	float viscosity, density;

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
public:
	fluid();
	~fluid();
};

