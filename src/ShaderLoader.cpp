#include "../include/ShaderLoader.hpp"

std::string ShaderLoader::readShaderFromFile(std::string filepath) {
	std::ifstream shaderFile;
	std::stringstream shaderStream;

	shaderFile.open(filepath);
	if (!shaderFile.is_open()) {
		std::cout << "Failed to open shader file: " << filepath << std::endl;
		return nullptr;
	}

	shaderStream << shaderFile.rdbuf();
	shaderFile.close();

	return shaderStream.str();
}

GLuint ShaderLoader::loadShaders(std::string vertexShaderPath, std::string fragmentShaderPath, std::string geometryShaderPath) {

	GLuint shaderProgram = glCreateProgram();

	CompileShader(shaderProgram, vertexShaderPath, GL_VERTEX_SHADER);
	CompileShader(shaderProgram, fragmentShaderPath, GL_FRAGMENT_SHADER);
	if(geometryShaderPath != "") {
		CompileShader(shaderProgram, geometryShaderPath, GL_GEOMETRY_SHADER);
	}

	glLinkProgram(shaderProgram);

	return shaderProgram;
}

void ShaderLoader::CompileShader(const GLuint& shaderProgram, std::string shaderPath, GLenum shaderType) {
	GLint success;
	GLchar infoLog[INFO_LOG_SIZE];

	std::string shaderCode = readShaderFromFile(shaderPath);
	const char* shaderSrc = shaderCode.c_str();

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, INFO_LOG_SIZE, NULL, infoLog);
		std::cout << "ERRORR::SHADER::COMPILATION_FAILED - " << shaderPath << std::endl;
		std::cout << infoLog << std::endl;
		return;
	}

	glAttachShader(shaderProgram, shader);
	glDeleteShader(shader);
}