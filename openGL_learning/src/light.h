#ifndef CLASS_LIGHT
#define CLASS_LIGHT
#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>

#include "shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class light
{
	public:

		glm::vec3 position;
		glm::vec3 orientation = glm::vec3(-1.0f, -1.0f, 0.0f);
		
		GLfloat intensity;

		VAO vao;

		light(float intensity, glm::vec3 position, GLfloat* vertices, GLint* indices);
		void lightup(float angleFactor, shader& sh);
		
		void lbind();
};

#endif