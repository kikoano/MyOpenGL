#include "Skybox.h"

Skybox::Skybox():Entity()
{

}
void Skybox::Init()
{
	va = std::make_unique<VertexArray>();
	vb = std::make_unique<VertexBuffer>(&vertices[0], vertices.size() * sizeof(vertices[0]), true);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	va->AddBuffer(*vb, layout);
	shader.Bind();
	shader.SetUniform1i("skybox", 0);
}

void Skybox::Update(double delta)
{
	shader.Bind();
	shader.SetUniformMatrix4fv("projection", projection);
	shader.SetUniformMatrix4fv("view", glm::mat3(view));
	shader.Unbind();
}

void Skybox::Render()
{
	glDepthFunc(GL_LEQUAL);
	shader.Bind();
	va->Bind();
	cubemap.BindCubeMap(0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	cubemap.UnbindCubeMap();
	va->Unbind();
	shader.Unbind();
	glDepthFunc(GL_LESS);
}



Skybox::~Skybox()
{

}
