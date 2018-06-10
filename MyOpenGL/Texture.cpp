#include "Texture.h"
#include <stb\stb_image.h>


Texture::Texture(const std::string filePath, bool alpha, bool flip) :rendererID(0), filePath(filePath), localBuffer(nullptr), width(0), height(0), bpp(0)
{
	if (flip)
		stbi_set_flip_vertically_on_load(1);
	else
		stbi_set_flip_vertically_on_load(0);

	localBuffer = stbi_load(filePath.c_str(), &width, &height, &bpp, 0);
	GLenum format;
	if (bpp == 1)
		format = GL_RED;
	else if (bpp == 3)
		format = GL_RGB; // GL_RGB8 for future?
	else if (bpp == 4)
		format = GL_RGBA;

	glGenTextures(1, &rendererID);
	glBindTexture(GL_TEXTURE_2D, rendererID);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, localBuffer);

	glGenerateMipmap(GL_TEXTURE_2D);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	if (localBuffer)
		stbi_image_free(localBuffer);

}
Texture::Texture(const std::string paths[6])
{
	stbi_set_flip_vertically_on_load(false);

	glGenTextures(1, &rendererID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, rendererID);

	for (unsigned int i = 0; i < 6; i++)
	{
		localBuffer = stbi_load(paths[i].c_str(), &width, &height, &bpp, 0);
		if (localBuffer) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);
			stbi_image_free(localBuffer);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << paths[i] << std::endl;
			stbi_image_free(localBuffer);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}
Texture::~Texture()
{
	glDeleteTextures(1, &rendererID);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, rendererID);
}
void Texture::BindCubeMap(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, rendererID);
}
void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::UnbindCubeMap()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}