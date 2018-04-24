#pragma once

#include "Renderer.h"
class Texture
{
private:
	unsigned int rendererID;
	std::string filePath;
	unsigned char* localBuffer;
	int width, height, bpp;
public:
	Texture(const std::string filePath, bool alpha);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind();

	inline int GetWidth() const { return width; };
	inline int GetHeight() const { return height; };
};

