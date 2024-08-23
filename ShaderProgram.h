#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/ext/vector_float3.hpp>
class ShaderProgram
{
public:
	unsigned int ID;
	ShaderProgram(const char* vertexPath, const char* fragmentPath);
	void Use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, const glm::vec3 &value) const;
private:
	void checkCompileErrors(unsigned int shader, std::string type);

};

