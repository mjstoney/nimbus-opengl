#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
Texture::Texture(const char* image, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = textureType;
	int imageWidth, imageHeight, numColorChannels;
	unsigned char* data = stbi_load(image, &imageWidth, &imageHeight, &numColorChannels, 0);
	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(textureType, ID);

	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
	
	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(textureType, 0, GL_RGBA, imageWidth, imageHeight, 0, format, pixelType, data);
	glGenerateMipmap(textureType);

	stbi_image_free(data);
	glBindTexture(textureType, 0);
}

Texture::~Texture()
{
	Delete();
}

void Texture::TextureUnit(ShaderProgram& shader, const char* uniform, GLuint unit)
{
	GLuint textureUnit = glGetUniformLocation(shader.ID, uniform);
	shader.Use();
	glUniform1i(textureUnit, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
