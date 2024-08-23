#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO& vbo, unsigned int layout, unsigned int size, unsigned int stride, void* offset)
{
	vbo.Bind();
	glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.Unbind();
}

void VAO::Enable(unsigned int layout) {
	glEnableVertexAttribArray(layout);
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}
