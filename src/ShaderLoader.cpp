#include "../include/ShaderLoader.hpp"

GLchar* ShaderLoader::readShaderFromFile(std::string filepath) {
	std::ifstream shaderFile;
	std::stringstream shaderStream;

	shaderFile.open(filepath);
	if (!shaderFile.is_open()) {
		std::cout << "Failed to open shader file: " << filepath << std::endl;
		return nullptr;
	}

	shaderStream << shaderFile.rdbuf();
	shaderFile.close();

	GLchar* shaderCode = (GLchar*) shaderStream.str().c_str();
	return shaderCode;
}

GLuint ShaderLoader::loadShaders(std::string vertexShaderPath, std::string fragmentShaderPath) {
	GLchar* vertexShaderCode = readShaderFromFile(vertexShaderPath);
	GLchar* fragmentShaderCode = readShaderFromFile(fragmentShaderPath);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgram);
	return shaderProgram;
}