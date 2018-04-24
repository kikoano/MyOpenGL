#pragma once
#include <glad\glad.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer {
public:
	void Render(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void RenderArrays(const VertexArray& va, const unsigned int count, const Shader& shader) const;
	void Clear();
	void Clear(float color[4]);
};

