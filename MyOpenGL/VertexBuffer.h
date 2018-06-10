#pragma once
class VertexBuffer
{
private:
	unsigned int rendererID;
	bool drawStatic;
public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size, bool drawStatic = true);
	~VertexBuffer();

	void Bind() const;
	void Unblind() const;
	void updateBuffer(const void* data, unsigned int size);
};

