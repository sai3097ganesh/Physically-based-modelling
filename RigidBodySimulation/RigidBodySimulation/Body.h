#pragma once
#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Body
{
public:
	float m;
	glm::vec3 X, V, w, L, p;
	glm::mat3 I, R;
	std::vector <glm::vec3> vertices;
	std::vector<std::vector<int>> faces;

	Body() {
		V = { 0,0,0 };
	};

	Body(const char* input) {
		
		if (strcmp(input, "cuboid")==0) {

			float l = 100, b = 100, h = 100;

			X = { 0,0,0 }; m = 1; V = { 2 ,0, 0 };

			float I_arr[9] = { m / 12 * (b*b + h*h), 0, 0,
				0, m / 12 * (l*l + h*h), 0,
				0, 0, m / 12 * (l*l + b*b) };

			I = glm::make_mat3(I_arr);
			R = glm::mat3(glm::rotate(glm::mat4(1.0f), (float)3.14/3, glm::vec3(1.0)));
			w = { 0.1,0.08,0.2 };

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
		deriv.R = body.w_star() * R;
		return deriv;
	}

	 Body add(Body *p1, Body *p2) {
		 Body ans("cuboid");
		 ans.X = p1->X + p2->X;
		 ans.V = p1->V + p2->V;
		 ans.R = p1->R + p2->R;
		 ans.vertices = p1->vertices;
		 ans.faces = p1->faces;
		 return ans;
	}

	 Body multiply(Body *p1, float h) {
		 Body ans("cuboid");
		 ans.X = p1->X * h;
		 ans.V = p1->V * h;
		 ans.R = p1->R * h;
		 ans.vertices = p1->vertices;
		 ans.faces = p1->faces;
		 return ans;
	 }

	 std::vector<glm::vec3> getOrientatedVertices() {
		 std::vector<glm::vec3> orientedVertices;
		 for (int i = 0; i < vertices.size(); i++) {
			 orientedVertices.push_back(X + R * vertices[i]);
		 }
		 return orientedVertices;
	 }

	 glm::mat3 w_star() {
		 float w_arr[9] = { 0, -w[2],w[1], w[2], 0, -w[0], -w[1], w[0], 0 };
		 return(glm::make_mat3(w_arr));
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

	bool isColliding(std::vector <glm::vec3> V, std::vector<std::vector<int>> F) {
		std::vector<glm::vec3> orientedVertices = getOrientatedVertices();
		for (int i = 0; i < vertices.size(); i++) {

		}
	}
	~Body();
};

