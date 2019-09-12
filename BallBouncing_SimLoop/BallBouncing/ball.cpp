#include "ball.h"
#include <iostream>


Ball::Ball()
{
}
float * Ball::getPos() {
	return position;
}

void Ball::update(float h, float d) {

	for (int i = 0; i < 3; i++) {
		acceleration[i] = gravity[i]-d/mass*velocity[i];
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
