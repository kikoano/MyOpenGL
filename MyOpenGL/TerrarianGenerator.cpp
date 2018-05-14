#include "TerrarianGenerator.h"



TerrarianGenerator::TerrarianGenerator(int vertexCount, int size, int seed, float persistence, float frequency, float amplitude, int octaves): size(size), vertexCount(vertexCount)
{
	perlin.Set(persistence,frequency,amplitude,octaves,seed);
}

void TerrarianGenerator::Generate(std::vector<float> &vert, std::vector<unsigned int> &indi)
{
	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			vert.push_back((float)j / ((float)vertexCount - 1) * size);
			vert.push_back(perlin.GetHeight(j, i));
			vert.push_back((float)i / ((float)vertexCount - 1) * size);
			glm::vec3 normal = calculateNormal(j, i);
			vert.push_back(normal.x);
			vert.push_back(normal.y);
			vert.push_back(normal.z);
			vert.push_back((float)(j * 16) / ((float)vertexCount - 1));
			vert.push_back((float)(i * 16) / ((float)vertexCount - 1));
		}
	}

	for (int gz = 0; gz < vertexCount - 1; gz++) {
		for (int gx = 0; gx < vertexCount - 1; gx++) {
			int topLeft = (gz*vertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*vertexCount) + gx;
			int bottomRight = bottomLeft + 1;
			indi.push_back(topLeft);
			indi.push_back(bottomLeft);
			indi.push_back(topRight);
			indi.push_back(topRight);
			indi.push_back(bottomLeft);
			indi.push_back(bottomRight);
		}
	}
}

glm::vec3 TerrarianGenerator::calculateNormal(int x, int z)
{
	float heightL = perlin.GetHeight(x - 1, z);
	float heightR = perlin.GetHeight(x + 1, z);
	float heightD = perlin.GetHeight(x, z - 1);
	float heightU = perlin.GetHeight(x, z + 1);

	glm::vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
	normal = glm::normalize(normal);
	return normal;
}

TerrarianGenerator::~TerrarianGenerator()
{
}
