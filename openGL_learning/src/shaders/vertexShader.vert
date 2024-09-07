// Specifies the version and type of opengl being used
#version 330 core

// Sets/Specifies the inputs to the vertex shader via linking of buffer
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 xNormal;
layout (location = 3) in vec3 yNormal;
layout (location = 4) in vec3 zNormal;

out vec3 eachColor;

uniform float time;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform mat4 proview;

uniform vec3 direction;
uniform float intensity;

uniform vec3 lCentre;
uniform vec3 centre1;
uniform vec3 centre2;

out float times;

void main()
{
	vec4 position = proview * vec4(aPos,1.0);

	times = time;

	//position.x = sin(time * 1.5) * 0.5;
	//position.z = sin(time * 1.5) * 0.5;

	float thetaX = 0.0;
	float thetaY = 0.0;
	float thetaZ = 0.0;

	thetaX = dot(-xNormal, direction) / (length(-xNormal) * length(direction));
	thetaY = dot(-yNormal, direction) / (length(-yNormal) * length(direction));
	thetaZ = dot(-zNormal, direction) / (length(-zNormal) * length(direction));
    
	int a = 0;
	int b = 0;
	int c = 0;

	gl_Position = position;
	
	if(xNormal == 0.0 && yNormal == 0.0 && zNormal == 0.0 )
	{
		eachColor = aColor;
	}
	else
	{

		if(dot(xNormal, vec3(1.0, 0.0, 0.0)) == 1.0 || dot(xNormal, vec3(1.0, 0.0, 0.0)) == -1.0)
			a = 1;
		if(dot(yNormal, vec3(0.0, 1.0, 0.0)) == 1.0 || dot(yNormal, vec3(0.0, 1.0, 0.0)) == -1.0)
			b = 1;
		if(dot(zNormal, vec3(0.0, 0.0, 1.0)) == 1.0 || dot(zNormal, vec3(0.0, 0.0, 1.0)) == -1.0)
			c = 1;
		eachColor = aColor * intensity * (thetaX * a + thetaY * b + thetaZ * c + 0.5);
	}
}