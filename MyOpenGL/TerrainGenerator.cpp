#include "TerrainGenerator.h"
#include <cinttypes>
#include <fstream>
#include <algorithm>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb\stb_image_write.h>



TerrainGenerator::TerrainGenerator(int fullVertexCount, int vertexCount, int size, int seed, float persistence, float frequency, float amplitude, int octaves) : fullVertexCount(fullVertexCount), size(size), vertexCount(vertexCount)
{
	perlin.Set(persistence, frequency, amplitude, octaves, seed);
	createBlendMap();
}

void TerrainGenerator::Generate(std::vector<float> &vert, std::vector<unsigned int> &indi)
{
	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			vert.push_back((float)j / ((float)vertexCount - 1) * size);
			float noise= perlin.GetHeight(j, i);
			vert.push_back(noise);
			vert.push_back((float)i / ((float)vertexCount - 1) * size);			
			glm::vec3 normal = calculateNormal(j, i);
			vert.push_back(normal.x);
			vert.push_back(normal.y);
			vert.push_back(normal.z);
			vert.push_back((float)(j /*more*/) / ((float)vertexCount - 1));
			vert.push_back((float)(i /*more*/) / ((float)vertexCount - 1));
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

void TerrainGenerator::createBlendMap()
{
	int dataSize = fullVertexCount * fullVertexCount * 3;
	uint8_t *data = new uint8_t[dataSize];
	for (unsigned int y = 0; y < fullVertexCount; y++) {
		for (unsigned int x = 0; x < fullVertexCount; x++) {
			double noise = perlin.GetHeight(y, x);
			int color= noise * 60;
			if (color > 255)
				color = 255;
			if (color < 0)
				color = 0;
			for (int i = x * 3; i < (x * 3) + 3; i++) {
				data[i + y * fullVertexCount *3] = color;
			}

		}
	}

	stbi_write_bmp((RESOURCES_PATH + "Textures/Maps/terrainBlendMap.bmp").c_str(), fullVertexCount, fullVertexCount, 3, data);
	delete[] data;
}

glm::vec3 TerrainGenerator::calculateNormal(int x, int z)
{
	float heightL = perlin.GetHeight(x - 1, z);
	float heightR = perlin.GetHeight(x + 1, z);
	float heightD = perlin.GetHeight(x, z - 1);
	float heightU = perlin.GetHeight(x, z + 1);

	glm::vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
	normal = glm::normalize(normal);
	return normal;
}

TerrainGenerator::~TerrainGenerator()
{
}
