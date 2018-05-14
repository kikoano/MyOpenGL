#pragma once
#include <iostream>
#include <vector>
#include <glm\glm.hpp>
#include "PerlinNoise.h"
class TerrarianGenerator
{
private:
	PerlinNoise perlin;
	int seed;
	int size;
	int vertexCount;
	glm::vec3 calculateNormal(int x, int z);
public:
	TerrarianGenerator(int vertexCount, int size, int seed, float persistence, float frequency, float amplitude, int octaves);
	void Generate(std::vector<float> &vert, std::vector<unsigned int> &indi);
	PerlinNoise GetPerlinNoise(){return perlin;}

	~TerrarianGenerator();
};

