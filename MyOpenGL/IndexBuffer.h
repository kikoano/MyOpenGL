#pragma once
class IndexBuffer
{
private:
	unsigned int count;
	unsigned int rendererID;
	bool drawStatic;
public:
	IndexBuffer(const unsigned int* data, unsigned int count, bool drawStatic = true);
	~IndexBuffer();

	void Bind() const;
	void Unblind() const;

	inline unsigned int GetCount() const { return count; }
	void updateBuffer(const void * data, unsigned int size);

};

