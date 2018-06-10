#pragma once
#include "main.h"
#include <vector>
#include <glm\glm.hpp>
#include "PerlinNoise.h"
class TerrainGenerator
{
private:
	PerlinNoise perlin;
	glm::vec3 calculateNormal(int x, int z);
	void createBlendMap(int vertexCount, int size);
public:
	TerrainGenerator();
	void Generate(std::vector<float> &vert, std::vector<unsigned int> &indi, int vertexCount, int size);
	void SetPerlin(int vertexCount, int size,int seed, float persistence, float frequency, float amplitude, int octaves);
	PerlinNoise GetPerlinNoise(){return perlin;}

	~TerrainGenerator();
};

