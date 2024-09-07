#pragma once

#ifndef EBO_CLASS
#define EBO_CLASS

#include <glad/glad.h>

class EBO
{
	GLuint ID;

	public:
		EBO(GLint* indices, GLsizeiptr size);
		void bind();
		void unbind();
		void del();
};

#endif