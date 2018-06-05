#pragma once

#include "Renderer.h"
class Texture
{
private:
	unsigned int rendererID;
	std::string filePath;
	std::string type;
	unsigned char* localBuffer;
	int width, height, bpp;
public:

	static inline std::vector<Texture> Textures_loaded;
	Texture(const std::string filePath, bool alpha = true,bool flip=false);
	Texture(const std::string filePath,std::string type);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	static void Unbind();

	inline int GetWidth() const { return width; };
	inline int GetHeight() const { return height; };
	inline std::string GetType() const { return type; }
	inline std::string GetFilePath() const { return filePath; }
};

