#include "light.h"

light::light(float intensity, glm::vec3 position, GLfloat* vertices, GLint* indices)
{
	light::intensity = intensity;
	light::position = position;

	

	
	vao.bind();

	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));

	

	vao.unbind();
	vbo.unbind();
	ebo.unbind();
}

void light::lightup(float angleFactor, shader& sh)
{
	glUniform1f(glGetUniformLocation(sh.ID, "angleFactor"), angleFactor);
	glUniform1f(glGetUniformLocation(sh.ID, "intensity"), intensity);
}

void light::lbind()
{
	vao.bind();
}