#pragma once
#include <glad/glad.h>
class EBO
{
public:
	unsigned int ID;
	EBO(unsigned int* indices, GLsizeiptr size);
	~EBO();
	void Bind();
	void Unbind();

};

