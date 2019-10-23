#pragma once
#include <glm/glm.hpp>
class State
{
public:

	State();
	~State();
};
class Particle
{
public: 
	glm::vec3 X;
	glm::vec3 V;
	glm::vec3 f;
	float mass;		
};
class Face
{
public:
	int structIndices[3];
	float VertexAngle[3];
};
class Edge
{
public:
	int vertexIndices[2];
	float k, d, length;
};
