#pragma once
#include <iostream>
#include <glm\glm.hpp>
#include <vector>
class Body
{
public:
	glm::vec3 m, X, V, w, L, p;
	glm::mat3 R;
	std::vector <glm::vec3> vertices;
	std::vector<std::vector<int>> faces;
	Body();
	Body(const char* input) {
		
		if (strcmp(input, "cuboid")==0) {
			float l = 10, b = 10, h = 10;

			vertices.push_back({ 0.0,0.0,0.0 });
			vertices.push_back({ l,0,0 });
			vertices.push_back({ 0,b,0 });
			vertices.push_back({ 0,0,h });
			vertices.push_back({ l,b,0 });
			vertices.push_back({ l,0,h });
			vertices.push_back({ 0,b,h });
			vertices.push_back({ l,b,h });

			faces.push_back({ 0,1,2,4 });
			faces.push_back({ 3,5,6,7 });
			faces.push_back({ 1,4,5,7 });
			faces.push_back({ 0,2,3,6 });
			faces.push_back({ 0,1,3,5 });
			faces.push_back({ 2,4,6,7 });
		}

	};
	~Body();
};

