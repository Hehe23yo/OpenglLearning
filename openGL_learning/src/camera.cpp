#include "camera.h"

#include <gtx/normal.hpp>

camera::camera(int width, int height, glm::vec3 position)
{
	// Setting camera position.

	camera::width = width;
	camera::height = height;
	camera::position = position;
}

void camera::matrix(float fov, float nearPlane, float farPlane, shader& shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	
	// using lookAt to set the position of the camera, the direction in which the camera looks.
	view = glm::lookAt(position, orientation, up); 
	
	// using perspective projection matrix to transform into screen coordinates
	projection = glm::perspective(glm::radians(fov), (float)(width / height), nearPlane, farPlane); 

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void camera::inputs(GLFWwindow* window)
{
	// Handle inputs

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		position += speed * -up;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		position += speed * up;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += speed * glm::normalize(glm::cross(orientation, up));
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position += speed * -glm::normalize(glm::cross(orientation, up));
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += speed * orientation;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position += speed * -orientation;

	// Changing orientation to rotate camera around its axis


	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		orientation = glm::rotate(orientation, glm::radians(0.5f), glm::vec3(0.0f, 1.0f, 0.0f)); 
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)				 
		orientation = glm::rotate(orientation, glm::radians(0.5f), glm::vec3(0.0f, -1.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		orientation = glm::rotate(orientation, glm::radians(0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		orientation = glm::rotate(orientation, glm::radians(0.5f), glm::vec3(-1.0f, 0.0f, 0.0f));

	//std::cout << orientation.x << orientation.z << std::endl;
}