/*
	https://www.khronos.org/opengl/wiki/Getting_Started#Downloading_OpenGL

	About manual loading of function pointers - https://www.reddit.com/r/opengl/comments/ai9k2u/manually_load_opengl_constants_and_functions/
*/

/*
	********** OPENGL **********
	
	- The opengl that comes with windows is NOT a library! It is a standard / specification that graphics driver will follow! It does not come with pre-defined functions
	- It DOES NOT contain the actual implementation of opengl.
	- The actual implementation of opengl is included with the graphics driver which needs to be queried / accessed at compile time and at run time both.
	- The compile time query is handled by glfw and the run time querying needs to be specified which is handled by things like glad.

	********** GLFW **********
	
	 - openGL is platform independant so the platform specific functionality needs to be specified glfw handles functions like creating a window,etc.
	 - glfw is tasked with creating and managing 'CONTEXT' in opengl applications (of windows and such).

	 ********** GLAD **********
	 
	 - Since there are many different opengl drivers according to the graphics driver, the location of the functions is not known at compile time and run time.
	 - While the compile time case is handled by glfw, the run time one is taken care of by GLAD.
	 - It holds the function pointers to the opengl functions and aids.
	 - Without something like GLAD we would have to manually specify / give the function pointers at run time. GLAD just simply eliminates the extra work!
*/

#include <iostream>
//#include <KHR/khrplatform.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h> // openGL is a platform independant library so the platform specific functionality needs to be specified
						// glfw handles functions like creating a window,etc.

#include <glm.hpp> // Math library for opengl
#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>
#include <ext/scalar_constants.hpp>
//#include <gtx/normal.hpp>

#include "shader.h"
#include "camera.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "light.h"

static void glfwError(int id, const char* description)
{
	std::cout << description << std::endl;
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(width, height, 0, 0);
}

int main()
{
	glfwSetErrorCallback(&glfwError);
	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw!" << std::endl;
	}
	else
	{
		std::cout << "Success!" << std::endl;
	}

	/*
		To set the required parameters prior to the usage of opengl
	*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	

	/*
		create a window with the given specifications
	*/
	GLFWwindow* window = glfwCreateWindow(800, 600, "yo", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwSetErrorCallback(&glfwError);
		std::cout << "Error : " << glfwGetError(NULL) << std::endl;
		glfwTerminate();
		return -1;
	}

	/*
		Changes the context to current which is the window newly created
	*/
    glfwMakeContextCurrent(window);
	
	/*
		Loads GLAD to be used with opengl
	*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize glad!" << std::endl;
		return -1;
	}
	
	/*
		Gives the specifications for the actual viewport, dimensions
	*/
	glViewport(0, 0, 800, 600);

	//glClearColor(1.0, 1.0, 0.0, 0.0);

	/*
		Allows setting the framebuffersizecallback to allow free resizing of window
	*/
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

	/*
		A shader class created to handle all operations related to shader loading
	*/
	shader sh1("D:\\VS_Codes\\openGL_learning\\openGL_learning\\src\\shaders\\vertexShader.vert", "D:\\VS_Codes\\openGL_learning\\openGL_learning\\src\\shaders\\fragmentShader.frag");
	shader sh2("D:\\VS_Codes\\openGL_learning\\openGL_learning\\src\\shaders\\lightShader.vert", "D:\\VS_Codes\\openGL_learning\\openGL_learning\\src\\shaders\\lightShader.frag");

	/*
		Defines the vertices for the shape to be drawn
	*/
	float vertices1[] = {
		0.0f, 0.5f, 0.0f,   0.5f, 0.5f, 0.5f,   -1.0f, 0.0f, 0.0f,   0.0f,  1.0f, 0.0f,   0.0f, 0.0f, -1.0f,// a 0
		0.5f, 0.5f, 0.0f,   0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,   0.0f,  1.0f, 0.0f,   0.0f, 0.0f, -1.0f,// b 1
		0.5f, 0.0f, 0.0f,   0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f, -1.0f,// c 2 
		0.0f, 0.0f, 0.0f,   0.5f, 0.5f, 0.5f,   -1.0f, 0.0f, 0.0f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f, -1.0f,// d 3
		0.0f, 0.5f, 0.5f,   0.5f, 0.5f, 0.5f,   -1.0f, 0.0f, 0.0f,   0.0f,  1.0f, 0.0f,   0.0f, 0.0f,  1.0f,// e 4
		0.5f, 0.5f, 0.5f,   0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,   0.0f,  1.0f, 0.0f,   0.0f, 0.0f,  1.0f,// f 5
		0.5f, 0.0f, 0.5f,   0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f,  1.0f,// g 6
		0.0f, 0.0f, 0.5f,   0.5f, 0.5f, 0.5f,   -1.0f, 0.0f, 0.0f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f,  1.0f // h 7
	};

	glm::vec3 rect1Centre = { 0.25f, 0.25f, 0.25f };

	int indices1[] = {
		// North
		3,0,1, // acd
		3,1,2, // abc

	    // South
		6,5,4, // feh
		6,4,7, // fhg

		// east
		7,4,0, // eah
		7,0,3, // adh

		// West
		2,1,5, // bfg
		2,5,6, // bgc

		// Top
		0,4,5, // aef 
		0,5,1, // afb

		// Bottom
		6,7,3, // dch ghd
		6,3,2 // cgh gdc

	};

	VAO vao1;
	vao1.bind();

	VBO vbo1(vertices1, sizeof(vertices1));
	EBO ebo1(indices1, sizeof(indices1));
	
	//vbo1.bind();

	vao1.linkArray(vbo1, 0, 3, GL_FALSE, GL_FALSE, 15 * sizeof(float), (void*)0);
	/*vao1.linkArray(vbo1, 1, 3, GL_FALSE, GL_FALSE, 15 * sizeof(float), (void*)(3 * sizeof(float)));
	vao1.linkArray(vbo1, 2, 3, GL_FALSE, GL_FALSE, 15 * sizeof(float), (void*)(6 * sizeof(float)));
	vao1.linkArray(vbo1, 3, 3, GL_FALSE, GL_FALSE, 15 * sizeof(float), (void*)(9 * sizeof(float)));
	vao1.linkArray(vbo1, 4, 3, GL_FALSE, GL_FALSE, 15 * sizeof(float), (void*)(12 * sizeof(float)));*/
	
	vao1.unbind();
	vbo1.unbind();
	ebo1.unbind();

	glm::vec3 dims = { 0.15f, 0.15f, 0.15f };
	
	glm::vec3 lightCentre = { -0.175, 0.675f, 0.875f };
	
	float vertices[] = {
			(lightCentre.x - dims.x / 2.0f), (lightCentre.y + dims.y / 2.0f), (lightCentre.z + dims.z / 2.0f),   1.0f, 1.0f, 1.0f,    0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
			(lightCentre.x + dims.x / 2.0f), (lightCentre.y + dims.y / 2.0f), (lightCentre.z + dims.z / 2.0f),   1.0f, 1.0f, 1.0f,	  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
			(lightCentre.x + dims.x / 2.0f), (lightCentre.y - dims.y / 2.0f), (lightCentre.z + dims.z / 2.0f),   1.0f, 1.0f, 1.0f,	  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
			(lightCentre.x - dims.x / 2.0f), (lightCentre.y - dims.y / 2.0f), (lightCentre.z + dims.z / 2.0f),   1.0f, 1.0f, 1.0f,	  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
			(lightCentre.x - dims.x / 2.0f), (lightCentre.y + dims.y / 2.0f), (lightCentre.z - dims.z / 2.0f),   1.0f, 1.0f, 1.0f,	  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
			(lightCentre.x + dims.x / 2.0f), (lightCentre.y + dims.y / 2.0f), (lightCentre.z - dims.z / 2.0f),   1.0f, 1.0f, 1.0f,	  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
			(lightCentre.x + dims.x / 2.0f), (lightCentre.y - dims.y / 2.0f), (lightCentre.z - dims.z / 2.0f),   1.0f, 1.0f, 1.0f,	  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
			(lightCentre.x - dims.x / 2.0f), (lightCentre.y - dims.y / 2.0f), (lightCentre.z - dims.z / 2.0f),   1.0f, 1.0f, 1.0f,	  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f
	};
	

	int indices2[] = {
		// North
		3,0,1, // acd
		3,1,2, // abc

		// South
		6,5,4, // feh
		6,4,7, // fhg

		// east
		7,4,0, // eah
		7,0,3, // adh

		// West
		2,1,5, // bfg
		2,5,6, // bgc

		// Top
		0,4,5, // aef 
		0,5,1, // afb

		// Bottom
		6,7,3, // dch ghd
		6,3,2 // cgh gdc

	};

	VAO lightVao1;

	lightVao1.bind();
	
	VBO lightVbo1(vertices, sizeof(vertices));
	EBO lightEbo1(indices2, sizeof(indices2));

	//lightVbo1.bind();
	
	lightVao1.linkArray(lightVbo1, 0, 3, GL_FALSE, GL_FALSE, 6 * sizeof(float), (void*)0);
	/*lightVao1.linkArray(lightVbo1, 1, 3, GL_FALSE, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	*/
	lightVao1.unbind();
	lightVbo1.unbind();
	lightEbo1.unbind();

	float vertices3[] = {
		-0.25f,  0.0f,  -0.25f,   0.5f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   0.0f,  1.0f, 0.0f,   0.0f, 0.0f, -1.0f,// a 0
		 0.75f,  0.0f,  -0.25f,   0.5f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,   0.0f,  1.0f, 0.0f,   0.0f, 0.0f, -1.0f,// b 1
		 0.75f, -0.3f,  -0.25f,   0.5f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f, -1.0f,// c 2 
		-0.25f, -0.3f,  -0.25f,   0.5f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f, -1.0f,// d 3
		-0.25f,  0.0f,   0.75f,   0.5f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   0.0f,  1.0f, 0.0f,   0.0f, 0.0f,  1.0f,// e 4
		 0.75f,  0.0f,   0.75f,   0.5f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,   0.0f,  1.0f, 0.0f,   0.0f, 0.0f,  1.0f,// f 5
		 0.75f, -0.3f,   0.75f,   0.5f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f,  1.0f,// g 6
		-0.25f, -0.3f,   0.75f,   0.5f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f,  1.0f // h 7
	};

	glm::vec3 rect2Centre = { 0.25f, -0.15f, 0.25f };

	VAO vao3;
	vao3.bind();

	VBO vbo3(vertices3, sizeof(vertices3));
	EBO ebo3(indices1, sizeof(indices1));

	//vbo3.bind();

	vao3.linkArray(vbo3, 0, 3, GL_FALSE, GL_FALSE, 15 * sizeof(float), (void*)0);
	/*vao3.linkArray(vbo3, 1, 3, GL_FALSE, GL_FALSE, 15 * sizeof(float), (void*)(3 * sizeof(float)));
	vao3.linkArray(vbo3, 2, 3, GL_FALSE, GL_FALSE, 15 * sizeof(float), (void*)(6 * sizeof(float)));
	vao3.linkArray(vbo3, 3, 3, GL_FALSE, GL_FALSE, 15 * sizeof(float), (void*)(9 * sizeof(float)));
	vao3.linkArray(vbo3, 4, 3, GL_FALSE, GL_FALSE, 15 * sizeof(float), (void*)(12 * sizeof(float)));*/

	vao3.unbind();
	vbo3.unbind();
	ebo3.unbind();

	float greenValue = 0.0;	
	float redValue = 0.0;	
	float blueValue = 0.0;	

	float dV = 0.003;

	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 view = glm::mat4(1.0);
	glm::mat4 proj = glm::mat4(1.0);

	view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
	proj = glm::perspective(90.0f, 600.0f / 800.0f, 0.1f, 1000.0f);

	float fov = 90.0f;
	float nearPlane = 0.1f;
	float farPlane = 1000.0f;

	float time = glfwGetTime();
	
	/*
		Disables drawing of triangles overlapping and on the farther side
	*/
	glEnable(GL_DEPTH_TEST);
	//float theta;

	float theta = 0.0f;

	camera cam(800, 600, glm::vec3(0.0f, 0.0f, 2.0f));

	glm::vec3 direction = glm::vec3(0.0f);
	float intensity = 0.5f;

	//light li(0.5f, glm::vec3(0.75f, 0.75f, 0.25f), vertices2, indices2);

	while (!glfwWindowShouldClose(window))
	{
		// *** Input ***
		
		// *** Remdering Commands ***

		//float vertices[] = {
		//	(lightCentre.x - dims.x / 2.0f), (lightCentre.y + dims.y / 2.0f), (lightCentre.z + dims.z / 2.0f),   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
		//	(lightCentre.x + dims.x / 2.0f), (lightCentre.y + dims.y / 2.0f), (lightCentre.z + dims.z / 2.0f),   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
		//	(lightCentre.x + dims.x / 2.0f), (lightCentre.y - dims.y / 2.0f), (lightCentre.z + dims.z / 2.0f),   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
		//	(lightCentre.x - dims.x / 2.0f), (lightCentre.y - dims.y / 2.0f), (lightCentre.z + dims.z / 2.0f),   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
		//	(lightCentre.x - dims.x / 2.0f), (lightCentre.y + dims.y / 2.0f), (lightCentre.z - dims.z / 2.0f),   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
		//	(lightCentre.x + dims.x / 2.0f), (lightCentre.y + dims.y / 2.0f), (lightCentre.z - dims.z / 2.0f),   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
		//	(lightCentre.x + dims.x / 2.0f), (lightCentre.y - dims.y / 2.0f), (lightCentre.z - dims.z / 2.0f),   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
		//	(lightCentre.x - dims.x / 2.0f), (lightCentre.y - dims.y / 2.0f), (lightCentre.z - dims.z / 2.0f),   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f
		//};

		//int indices2[] = {
		//	// North
		//	3,0,1, // acd
		//	3,1,2, // abc

		//	// South
		//	6,5,4, // feh
		//	6,4,7, // fhg

		//	// east
		//	7,4,0, // eah
		//	7,0,3, // adh

		//	// West
		//	2,1,5, // bfg
		//	2,5,6, // bgc

		//	// Top
		//	0,4,5, // aef 
		//	0,5,1, // afb

		//	// Bottom
		//	6,7,3, // dch ghd
		//	6,3,2 // cgh gdc

		//};

		/*VAO vao2;

		vao2.bind();

		VBO vbo2(vertices, sizeof(vertices));
		EBO ebo2(indices2, sizeof(indices2));

		vao2.linkArray(vbo2, 0, 1);

		vao2.unbind();
		vbo2.unbind();
		ebo2.unbind();*/

		/*
			Sets the rendering mode and the default color of the viewport
		*/
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currTime = glfwGetTime();
		if (currTime - time >= (1 / 60))
		{
			theta = 0.7f;
			time = currTime;
		}
	

		
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

		// APPLYING VARIOUS TRANSFORMATIONS ON THE POSITION OF OBJECT IN WORLD SPACE
		//model = glm::rotate(model, glm::radians(theta), glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, glm::radians(theta), glm::vec3(1.0f, 1.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(glm::sin(currTime) * 0.005f, glm::cos(currTime) * 0.005f, 0.0f));
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, glm::cos(currTime) * 0.005f));
		//model = glm::rotate(model, glm::radians(theta), glm::vec3(0.0f, 1.0f, 0.0f));

		/*GLuint modelLocation = glGetUniformLocation(sh.ID, "model");
		GLuint viewLocation = glGetUniformLocation(sh.ID, "view");
		GLuint projLocation = glGetUniformLocation(sh.ID, "proj");

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, &proj[0][0]);
		*/
		cam.inputs(window); // hande imputs
		cam.matrix(fov, nearPlane, farPlane, sh1, "proview");

		GLuint directionLocation = glGetUniformLocation(sh1.ID, "direction");
		GLuint intensityLocation = glGetUniformLocation(sh1.ID, "intensity");

		
		glUniform1f(intensityLocation, intensity);

		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
			lightCentre.y += 0.05f;
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
			lightCentre.x -= 0.05f;
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
			lightCentre.x += 0.05f;
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
			lightCentre.y -= 0.05f;
		
		direction = rect1Centre - lightCentre;
		glUniform3fv(directionLocation, 1, glm::value_ptr(direction));

		//direction = rect2Centre - lightCentre;
		
		/*glUniform3fv(glGetUniformLocation(sh1.ID, "lCentre"), 1, glm::value_ptr(lightCentre));
		glUniform3fv(glGetUniformLocation(sh1.ID, "centre1"), 1, glm::value_ptr(rect1Centre));
		glUniform3fv(glGetUniformLocation(sh1.ID, "centre2"), 1, glm::value_ptr(rect2Centre));*/

		sh1.use();

		/*for (int i = 0; i <= 36; i += 3)
		{
			glm::vec3 a = glm::vec3(vertices1[indices1[i]], vertices1[indices1[i]] + 1, vertices1[indices1[i]] + 2);
			glm::vec3 b = glm::vec3(vertices1[indices1[i + 1]], vertices1[indices1[i]] + 1, vertices1[indices1[i + 1]] + 2);
			glm::vec3 c = glm::vec3(vertices1[indices1[i + 2]], vertices1[indices1[i]] + 1, vertices1[indices1[i + 2]] + 2);

			glm::vec3 normal = glm::triangleNormal(a, b, c);
			li.lightup((glm::dot(normal, li.orientation)) / (glm::length(normal) * glm::length(li.orientation)));
		}*/

		vao1.bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices1), GL_UNSIGNED_INT, 0);

		vao3.bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices1), GL_UNSIGNED_INT, 0);

		//sh2.use();

		lightVao1.bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices2), GL_UNSIGNED_INT, 0);


		// *** Events and swap buffers ***
		glfwPollEvents();
		glfwSwapBuffers(window);
		
	}

	vao1.del();
	vbo1.del();
	ebo1.del();

	glfwDestroyWindow(window);

	glfwTerminate();

	//glfwSet

}