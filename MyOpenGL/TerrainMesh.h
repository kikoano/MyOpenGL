#pragma once
#include "Entity.h"
#include "Mesh.h"
#include <string>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "main.h"
#include "TerrainGenerator.h"
#include "Light.h"
#include "Camera.h"

class TerrainMesh :
	public Entity
{
private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::unique_ptr<VertexArray> va;
	std::unique_ptr<VertexBuffer> vb;
	std::unique_ptr<IndexBuffer> ib;
	Shader shader = Shader("terrain.vert", "terrain.frag");
	Texture texture1 = Texture(RESOURCES_PATH + "Textures\\grass.png", false);
	Texture texture2 = Texture(RESOURCES_PATH + "Textures\\snow.jpg", false);
	Texture blendMap = Texture(RESOURCES_PATH + "Textures\\Maps\\terrainBlendMap.bmp", false, true);
	Texture specularTexture = Texture(RESOURCES_PATH + "Textures\\grass.png", false);
	glm::mat4 model = glm::mat4(1.0f);
	float shininess = 256.0f;

public:
	static TerrainGenerator generator;
	TerrainMesh(glm::vec3 position);
	void Init();
	void Update(double delta);
	void UpdateLight(Light &light, Camera &camera, int scaleTiles);
	void Render();
	void Generate(int vertexCount, int size);
	~TerrainMesh();
};

