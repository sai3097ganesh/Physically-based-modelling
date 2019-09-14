#include "ball.h"
#include <iostream>


Ball::Ball()
{
}
float * Ball::getPos() {
	return position;
}

void Ball::update(float h, float d, float * wind) {

	for (int i = 0; i < 3; i++) {
		printf("%f %f %f \n", wind[0], wind[1], wind[2]);
		acceleration[i] = gravity[i]-d/mass*velocity[i]+d*wind[i];
	}
	for (int i = 0; i < 3; i++) {
		position[i] += h*velocity[i];
	}
	for (int i = 0; i < 3; i++) {
		velocity[i] += h*acceleration[i];
	}

	
}
Ball::~Ball()
{
}
