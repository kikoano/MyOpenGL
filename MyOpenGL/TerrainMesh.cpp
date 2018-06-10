#include "TerrainMesh.h"

TerrainMesh::TerrainMesh(glm::vec3 position) :Entity(position)
{

}
void TerrainMesh::Init()
{
	model = glm::translate(model, position);
	va = std::make_unique<VertexArray>();
	vb = std::make_unique<VertexBuffer>(&vertices[0], vertices.size() * sizeof(vertices[0]), true);
	ib = std::make_unique<IndexBuffer>(&indices[0], indices.size() * sizeof(indices[0]), true);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);
	shader.Bind();
	shader.SetUniform1i("material.diffuse", 0);
	shader.SetUniform1i("material.diffuse2", 1);
	shader.SetUniform1i("material.blendMap", 2);
	shader.SetUniform1i("material.specular", 3);
}

void TerrainMesh::Update(double delta)
{
	shader.Bind();
	shader.SetUniformMatrix4fv("projection", projection);
	shader.SetUniformMatrix4fv("view", view);
	shader.SetUniformMatrix4fv("model", model);
	shader.SetUniform3fv("skyColor", glm::vec3(0.87f, 0.91f, 0.94f));
	shader.Unbind();
}

void TerrainMesh::UpdateLight(Light &light, Camera &camera, int scaleTiles)
{
	shader.Bind();
	shader.SetUniform3fv("light.position", light.GetPosition());
	shader.SetUniform3fv("viewPos", camera.GetPosition());

	shader.SetUniform3f("light.ambient", 0.1f, 0.1f, 0.1f);
	shader.SetUniform3fv("light.diffuse", light.GetDiffuse());
	shader.SetUniform3fv("light.specular", light.GetSpecular());

	shader.SetUniform1f("material.shininess", shininess);
	shader.SetUniform1i("scaleTiles", scaleTiles);
	shader.Unbind();
}

void TerrainMesh::Render()
{
	shader.Bind();
	va->Bind();
	texture1.Bind(0);
	texture2.Bind(1);
	blendMap.Bind(2);
	specularTexture.Bind(3);
	ib->Bind();
	glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr);
	va->Unbind();
	shader.Unbind();
}

void TerrainMesh::Generate(int vertexCount, int size)
{
	generator.Generate(vertices, indices, vertexCount, size);
}


TerrainMesh::~TerrainMesh()
{

}
