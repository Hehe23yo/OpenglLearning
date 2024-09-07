#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class shader
{
public:
	// Program ID
	GLuint ID;

public:
	// Constructor reads and builds the shader
	shader(const char* vertexPath, const char* fragmentPath);
	
	// Use the shader
	void use();

	void del();
	// Utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};

#endif