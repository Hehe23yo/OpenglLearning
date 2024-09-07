#pragma once

#ifndef VBO_CLASS
#define VBO_CLASS

#include <glad/glad.h>

class VBO
{
	public:
		
		GLuint ID;
	
		VBO(GLfloat* vertices, int size);
		void bind();
		void unbind();
		void del();
};

#endif // !VBO_CLASS

