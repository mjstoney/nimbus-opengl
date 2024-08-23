#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <glm/vec3.hpp>



struct Mesh
{
	std::vector<float> vertices;
	std::vector<float> texCoords;
	std::vector<float> normals;
	std::vector<unsigned int> indices;
	unsigned int numIdxVert, numIdxTex, numIdxNorm;

};

Mesh LoadOBJ(const char* filepath);
void QuadsToTris(Mesh &m);
void PrintMesh(Mesh m);