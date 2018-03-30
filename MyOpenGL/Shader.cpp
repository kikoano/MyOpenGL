#include "Shader.h"
#include <glad/glad.h>
#include <iostream>

Shader::Shader(const std::string& filePath)
{
	//CreateShader();
}
Shader::Shader(const char *vertexShaderSource, const char *fragmentShaderSource) {
	CreateShader(vertexShaderSource, fragmentShaderSource);
}

Shader::~Shader(){
	glDeleteProgram(program);
}

void Shader::Bind() const {
	glUseProgram(program);
}

void Shader::Unbind() const {
	glUseProgram(0);
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(id, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::"<<((type == GL_VERTEX_SHADER) ? "VERTEX": "FRAGMENT") <<"::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return id;
}
void Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

}

void Shader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3) {
	glUniform4f(GetUniformLocation(name), f0, f1, f2, f3);
}
void Shader::SetUniform4f(const std::string& name, const glm::vec4 &value) {
	glUniform4fv(GetUniformLocation(name),1, &value[0]);
}
void Shader::SetUniformMatrix4fv(const std::string& name, const glm::mat4 &mat) {
	glUniformMatrix4fv(GetUniformLocation(name), 1, false, &mat[0][0]);
}
unsigned int Shader::GetUniformLocation(const std::string& name) {
	unsigned int location = glGetUniformLocation(program, name.c_str());
	return location;
}
