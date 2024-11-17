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
	GLint success;
	GLchar infoLog[512];

	std::string vertexShaderCode = readShaderFromFile(vertexShaderPath);
	std::string fragmentShaderCode = readShaderFromFile(fragmentShaderPath);

	const char* vertexShaderSrc = vertexShaderCode.c_str();
	const char* fragmentShaderSrc = fragmentShaderCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	if(!geometryShaderPath.empty()) {
		std::string geometryShaderCode = readShaderFromFile(geometryShaderPath);
		const char* geometryShaderSrc = geometryShaderCode.c_str();

		GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometryShaderSrc, NULL);
		glCompileShader(geometryShader);

		glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
			return -1;
		}

		glAttachShader(shaderProgram, geometryShader);
		glDeleteShader(geometryShader);
	}

	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}