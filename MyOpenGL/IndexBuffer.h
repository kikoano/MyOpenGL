#pragma once
class IndexBuffer
{
private:
	unsigned int count;
	unsigned int rendererID;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unblind() const;

	inline unsigned int GetCount() const { return count; }
};

