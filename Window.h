#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <glm/vec3.hpp>


class Window
{
public:
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	GLFWwindow* window;
	Window();
	void run();
	void processInput(GLFWwindow* window);
};

