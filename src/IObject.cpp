#include "../include/IObject.hpp"

void IObject::SelectShaderProgram(const char* name) {
	if (shaderPrograms.empty()) {
		return;
	}

	if (name == nullptr) {
		selectedProgram = shaderPrograms.begin()->second;
		return;
	}

	selectedProgram = shaderPrograms[name];
}

std::vector<const char*> IObject::GetShaderProgramNames() {
	std::vector<const char*> programNames;
	for (auto &shaderProgram : shaderPrograms) {
		programNames.push_back(shaderProgram.first);
	}

	return programNames;
}

IObject::~IObject() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	for (auto &shaderProgram : shaderPrograms) {
		glDeleteProgram(shaderProgram.second);
	}
}