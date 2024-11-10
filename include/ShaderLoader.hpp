#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <GL/glew.h>

class ShaderLoader {
	public:
		ShaderLoader() = delete;
		static GLchar* readShaderFromFile(std::string filepath);
		static GLuint loadShaders(std::string vertexShaderPath, std::string fragmentShaderPath);
};

#endif