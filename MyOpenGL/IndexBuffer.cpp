#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count, bool drawStatic) : count(count)
{
	//EBO
	glGenBuffers(1, &rendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	if (drawStatic)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);
	else
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &rendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
}
void IndexBuffer::updateBuffer(const void * data, unsigned int size) {
	count = size;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	void *ptr = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	// now copy data into memory
	memcpy(ptr, data, size);
	// make sure to tell OpenGL we're done with the pointer
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void IndexBuffer::Unblind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
