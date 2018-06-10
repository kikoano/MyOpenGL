#pragma once
#include "Entity.h"
#include "Mesh.h"
#include <string>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "main.h"
class Skybox :
	public Entity
{
private:
	const std::string paths[6] = {
		RESOURCES_PATH + "Textures\\Skybox\\right.jpg",
		RESOURCES_PATH + "Textures\\Skybox\\left.jpg",
		RESOURCES_PATH + "Textures\\Skybox\\top.jpg",
		RESOURCES_PATH + "Textures\\Skybox\\bottom.jpg",
		RESOURCES_PATH + "Textures\\Skybox\\front.jpg",
		RESOURCES_PATH + "Textures\\Skybox\\back.jpg",
	};
	const std::vector<float> vertices = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	std::unique_ptr<VertexArray> va;
	std::unique_ptr<VertexBuffer> vb;
	Texture cubemap = Texture(paths);
	Shader shader = Shader("skybox.vert", "skybox.frag");
	
public:
	Skybox();
	void Init();
	void Update(double delta);
	void Render();
	~Skybox();
};

