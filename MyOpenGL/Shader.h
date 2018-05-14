#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSouce;
};

class Shader {
private:
	unsigned int program;
	ShaderProgramSource ParseShader(const std::string& filepath);
	ShaderProgramSource ParseShader(const std::string& vertexPath, const std::string& fragmentPath);
	int GetUniformLocation(const std::string& name);

	unsigned int CompileShader(unsigned int type, const std::string& source);
	void CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
public:
	Shader(const std::string& filepath);
	Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	~Shader();

	void Bind() const;
	void Unbind() const;
	
	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
	void SetUniform3f(const std::string& name, float f0, float f1, float f2);
	void SetUniform3fv(const std::string& name, const glm::vec3 &value);
	void SetUniform4fv(const std::string& name, const glm::vec4 &value);
	void SetUniform1i(const std::string& name, int v0);
	void SetUniformMatrix4fv(const std::string& name, const glm::mat4 &mat);
	void SetUniform1f(const std::string& name, float v0);
};
