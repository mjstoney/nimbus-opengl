#include "Window.h"
#include <iostream>
#include "VBO.h"
#include "VAO.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "EBO.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Loader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

Window::Window()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Interesting Title", NULL, NULL);
	if (window == NULL) {
		std::cout << "sdlkasl;dkaskd";
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//==================================================================++
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	
	//==================================================================++
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	glEnable(GL_DEPTH_TEST);

	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

}

void Window::run()
{
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};

	// Indices for vertices order
	unsigned int indices[] =
	{
		0, 2, 1, // Upper triangle
		0, 3, 2 // Lower triangle
	};
	Mesh m = LoadOBJ("D:/dev/cplusplus/nimbus/resources/bunny.obj");
	std::cout << m.vertices.size() << " " << m.texCoords.size()<< " " << m.normals.size()<< " " << m.indices.size();
	//==================================================================
	VAO bunnyVAO;
	bunnyVAO.Bind();
	VBO bunnyVBO(m.vertices.data(), sizeof(m.vertices[0])*m.vertices.size());
	EBO bunnyEBO(m.indices.data(), sizeof(m.indices[0]) * m.indices.size());
	VBO bunnyNormalsVBO(m.normals.data(), sizeof(m.normals[0]) * m.normals.size());

	bunnyEBO.Bind();
	bunnyVAO.LinkAttrib(bunnyVBO, 0, 3, 3 * sizeof(float), (void*)0);
	bunnyVAO.LinkAttrib(bunnyNormalsVBO, 1, 3, 3 * sizeof(float), (void*)0);


	bunnyVAO.Enable(0);
	bunnyVAO.Enable(1);
	bunnyVAO.Unbind();
	bunnyVBO.Unbind();

	//==================================================================
	VAO lightVAO;
	VBO lightVBO(vertices, sizeof(vertices));
	lightVAO.Bind();
	lightVBO.Bind();
	lightVAO.LinkAttrib(lightVBO, 0, 3, 3 * sizeof(float), (void*)0);
	lightVAO.Unbind();	
	
	//==================================================================
	ShaderProgram defaultShader("D:/dev/cplusplus/nimbus/shaders/default.vert", "D:/dev/cplusplus/nimbus/shaders/default.frag");
	defaultShader.Use();
	defaultShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
	defaultShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	defaultShader.setVec3("lightPos", lightPos);
	//==================================================================
	ShaderProgram lightingShader("D:/dev/cplusplus/nimbus/shaders/lighting.vert", "D:/dev/cplusplus/nimbus/shaders/lighting.frag");
	
	glm::mat4 model1(1.0f);
	glm::mat4 model2(1.0f);
	model2 = glm::translate(model2, lightPos);
	model2 = glm::scale(model2, glm::vec3(0.2f));
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		
		glClearColor(0.2, 0.3, 0.4, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		view = camera.getViewMatrix();
		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		defaultShader.Use();
		glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model1));
		glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		bunnyVAO.Bind();
		glDrawElementsBaseVertex(GL_TRIANGLES, m.numIdxVert, GL_UNSIGNED_INT, (void*)(0), 0);
		glDrawElementsBaseVertex(GL_TRIANGLES, m.numIdxNorm, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int)* (m.numIdxVert + m.numIdxTex)), m.vertices.size());

		
		//glDrawElements(GL_TRIANGLES, m.indices.size(), GL_UNSIGNED_INT, 0);
		bunnyVAO.Unbind();

		lightingShader.Use();
		glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model2));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		lightVAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		lightVAO.Unbind();



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}


void Window::processInput(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset, true
	);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}