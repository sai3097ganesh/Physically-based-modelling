#pragma once
#include <iostream>
#include <glm\glm.hpp>
#include <vector>
#include <eigen\dense>

using namespace Eigen;

class Body
{
public:
	float m;
	Vector3d X, V, w, L, p;
	Matrix3d I, R;
	std::vector <Vector3d> vertices;
	std::vector<std::vector<int>> faces;

	Body() {
		V = { 0,0,0 };
	};
	Body(const char* input) {
		
		if (strcmp(input, "cuboid")==0) {

			float l = 100, b = 100, h = 100;

			X = { 0,0,0 }; m = 1; V = { 0 ,0, 0 };
			I << m / 12 * (b*b + h*h), 0, 0,
				0, m / 12 * (l*l + h*h), 0,
				0, 0, m / 12 * (l*l + b*b);
			R << MatrixXf::Identity(3,3);

			vertices.push_back({ 0.0,0.0,0.0 });
			vertices.push_back({ l,0,0 });
			vertices.push_back({ 0,b,0 });
			vertices.push_back({ 0,0,h });
			vertices.push_back({ l,b,0 });
			vertices.push_back({ l,0,h });
			vertices.push_back({ 0,b,h });
			vertices.push_back({ l,b,h });

			for (int i = 0; i < vertices.size(); i++) {
				vertices[i][0] -= l / 2;
				vertices[i][1] -= b / 2;
				vertices[i][2] -= h / 2;
			}

			faces.push_back({ 0,1,2,4 });
			faces.push_back({ 3,5,6,7 });
			faces.push_back({ 1,4,5,7 });
			faces.push_back({ 0,2,3,6 });
			faces.push_back({ 0,1,3,5 });
			faces.push_back({ 2,4,6,7 });

		}

	};

	Body derivative(Body body) {
		Body deriv;
		deriv.X = body.V;
		return deriv;
	}

		 Body add(Body *p1, Body *p2) {
		 Body ans;
		 ans.X = p1->X + p2->X;
		 ans.V = p1->V + p2->V;
	
		 return ans;
	}

	 Body multiply(Body *p1, float h) {
		 Body ans;
		 ans.X = p1->X * h;
		 ans.V = p1->V * h;
		 return ans;
	 }

	void eulerStep(float h) {

		*this = add((this), &multiply(&derivative(*(this)), h));

	}

	void RK2step(float h) {
		Body K1, K2;
		K1 = derivative((*this));
		K2 = derivative(add(this, &multiply(&K1, 0.5*h)));
		*this = add(this, &multiply(&K2, h));
	}

	void RK4step(float h) {
		Body K1, K2, K3, K4;
		K1 = derivative((*this));
		K2 = derivative(add(this, &multiply(&K1, 0.5*h)));
		K3 = derivative(add(this, &multiply(&K2, 0.5*h)));
		K4 = derivative(add(this, &multiply(&K3, h)));
		*this = add(this, &multiply(&K1, h / 6));
		*this = add(this, &multiply(&K2, h / 3));
		*this = add(this, &multiply(&K3, h / 3));
		*this = add(this, &multiply(&K4, h / 6));
	}

	~Body();
};

