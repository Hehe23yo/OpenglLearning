#include "VAO.h"

#include <iostream>

// Generates VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links the data to shader, such as position, colour, etc.
void VAO::linkArray(VBO vbo, GLuint layout, GLint size, GLenum type, GLboolean normalize, GLsizeiptr stride, const void* pointerOffset)
{
	//glVertexAttribPointer(layout, size, type, normalize, stride, pointerOffset); // position
	//glEnableVertexAttribArray(layout);
	vbo.bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(12 * sizeof(float)));
	glEnableVertexAttribArray(4);
	vbo.unbind();
}

// Binds VAO
void VAO::bind()
{
	glBindVertexArray(ID);
}

// Unbinds VAO
void VAO::unbind()
{
	glBindVertexArray(0);
}

// Deletes VAO
void VAO::del()
{
	glDeleteVertexArrays(1, &ID);
}