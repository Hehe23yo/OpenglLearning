#include "VBO.h"

#include <iostream>

VBO::VBO(GLfloat* vertices, int size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);  // BUFFER DATA takes a pointer to the actual data, so you pass the vertices as it is... NOT the pointer's reference
}

void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::del()
{
	glDeleteVertexArrays(1, &ID);
}