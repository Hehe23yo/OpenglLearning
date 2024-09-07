#version 330 core

in vec3 eachColour;
out vec4 Colour;

void main()
{
	Colour = vec4(eachColour, 1.0);
}