#include "VBO.h"
#include <iostream>
#include <glm/ext/vector_float3.hpp>

VBO::VBO(float *vertices, unsigned int size)
{
	
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);	
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

}

VBO::~VBO()
{
	glDeleteBuffers(1, &ID);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

