#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &rendererID);
}
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),(const void*) offset);
		offset += element.count * VertexBufferElement::GetSeizeOfType(element.type);
	}
}
void VertexArray::Bind() const {
	glBindVertexArray(rendererID);
}
void VertexArray::Unbind() const {
	glBindVertexArray(0);
}
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &rendererID);
}
