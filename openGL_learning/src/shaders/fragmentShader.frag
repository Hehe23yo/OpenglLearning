#version 330 core
in vec3 eachColor;
out vec4 fragColor;
in float times;
void main()
{
	//eachColor.x += sin(times * 0.5) * 0.5;
	//vec3 newColor = fract(eachColor);
	
	fragColor = vec4(eachColor, 1.0f);
//	fragColor.r = sin(eachColor.r + times * 1.5) / 2.0;
//	fragColor.g = cos(eachColor.g + times * 1.5) / 2.0;
//	fragColor.b = sin(eachColor.b + times * 0.5) * 0.5;
}