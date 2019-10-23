#include <iostream>
#include "State.h"

State derivative(State current) {
	State returnState;
	returnState.X = current.V;
	returnState.V = current.A;
	return returnState;
}

int main() {
	std::cout << "Springy meshes panna porom";
	std::getchar();
}