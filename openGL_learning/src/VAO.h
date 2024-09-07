#pragma once

#ifndef VAO_CLASS
#define VAO_CLASS

#include <glad/glad.h>

#include "VBO.h"

class VAO
{
public:
	GLuint ID;

	public:

		VAO();
		void linkArray(VBO vbo, GLuint layout, GLint size, GLenum type, GLboolean normalize, GLsizeiptr stride, const void* pointerOffset);
		void bind();
		void unbind();
		void del();
};

#endif 
