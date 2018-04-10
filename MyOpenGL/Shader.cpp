#include "Shader.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>


ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while(getline(stream, line)) 
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}
ShaderProgramSource Shader::ParseShader(const std::string& vertexPath, const std::string& fragmentPath) {

	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return { vertexCode.c_str(), fragmentCode.c_str() };
}
Shader::Shader(const std::string& filePath)
{
	ShaderProgramSource source = ParseShader(filePath);
	CreateShader(source.VertexSource, source.FragmentSouce);
}
Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	ShaderProgramSource source = ParseShader(vertexPath, fragmentPath);
	CreateShader(source.VertexSource, source.FragmentSouce);
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
