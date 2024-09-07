#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 0) in vec3 aColour;

uniform vec3 lightDir;

out vec3 eachColour;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	eachColour = aColour;
}
