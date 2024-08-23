#pragma once
#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	unsigned int ID;
	VAO();
	~VAO();
	void LinkAttrib(VBO& vbo, unsigned int layout, unsigned int size, unsigned int stride, void* offset);
	void Enable(unsigned int layout);
	void Bind();
	void Unbind();
};

