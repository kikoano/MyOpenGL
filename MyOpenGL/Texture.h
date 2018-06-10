#pragma once

#include "Renderer.h"
#include <map>
	struct TextureInfo {
		GLuint texture;
		std::string mode;
	};
class Texture
{
private:
	unsigned int rendererID;
	std::string filePath;
	unsigned char* localBuffer;
	int width, height, bpp;
public:
	static inline std::map<std::string, TextureInfo> LoadedTextures;
	Texture(const std::string filePath, bool alpha = true,bool flip=false);
	Texture(const std::string paths[6]);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void BindCubeMap(unsigned int slot = 0) const;
	static void Unbind(); //temp static for tests
	void UnbindCubeMap();

	inline int GetWidth() const { return width; };
	inline int GetHeight() const { return height; };
	inline std::string GetFilePath() const { return filePath; }
};

