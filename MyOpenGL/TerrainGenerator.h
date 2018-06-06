#pragma once
#include "main.h"
#include <vector>
#include <glm\glm.hpp>
#include "PerlinNoise.h"
#include "Tree.h"
class TerrainGenerator
{
private:
	PerlinNoise perlin;
	int seed;
	int size;
	int fullVertexCount;
	int vertexCount;
	glm::vec3 calculateNormal(int x, int z);
	void createBlendMap();
public:
	TerrainGenerator(int fullVertexCount, int vertexCount, int size, int seed, float persistence, float frequency, float amplitude, int octaves);
	void Generate(std::vector<float> &vert, std::vector<unsigned int> &indi);
	PerlinNoise GetPerlinNoise(){return perlin;}

	~TerrainGenerator();
};

