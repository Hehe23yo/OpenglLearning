#ifndef CAMERA_CLASS
#define CAMERA_CLASS
#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>

#include "shader.h"

class camera
{
	public:
		glm::vec3 position;
		glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		int width;
		int height;

		float speed = 0.01f;
		float sensitivity = 100.0f;

		camera(int width, int height, glm::vec3 position);

		void matrix(float fov, float nearPlane, float farPlane, shader& shader, const char* uniform);

		void inputs(GLFWwindow* window);
};

#endif