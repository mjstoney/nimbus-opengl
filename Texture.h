#pragma once
#include <glad/glad.h>
#include "ShaderProgram.h"


class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
	~Texture();

	void TextureUnit(ShaderProgram& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};

