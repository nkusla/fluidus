#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <GL/glew.h>

#define INFO_LOG_SIZE 1024

class ShaderLoader {
	private:
		static std::string readShaderFromFile(std::string filepath);
		static void CompileShader(const GLuint& shaderProgram, std::string shaderPath, GLenum shaderType);

	public:
		ShaderLoader() = delete;

		static GLuint LoadShaders(
			std::string vertexShaderPath,
			std::string fragmentShaderPath,
			std::string geometryShaderPath = "");
};

#endif