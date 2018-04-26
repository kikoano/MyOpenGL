#include "Renderer.h"


void Renderer::Render(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {

	shader.Bind();
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}
void Renderer::Render(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, unsigned int type) const {
	shader.Bind();
	va.Bind();
	ib.Bind();
	glDrawElements(type, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}
void Renderer::RenderArrays(const VertexArray& va,const unsigned int count, const Shader& shader) const {
	shader.Bind();
	va.Bind();
	glDrawArrays(GL_TRIANGLES, 0, count);
}
void Renderer::RenderArrays(const VertexArray& va, const unsigned int count, const Shader& shader, unsigned int type) const {
	shader.Bind();
	va.Bind();
	glDrawArrays(type, 0, count);
}
void  Renderer::Clear() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::Clear(float color[4]) {
	glClearColor(color[0], color[1], color[2], color[2]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::Clear(glm::vec4 color) {
	glClearColor(color[0], color[1], color[2], color[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
