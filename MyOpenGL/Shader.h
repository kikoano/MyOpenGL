#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
private:
	unsigned int program;
	unsigned int GetUniformLocation(const std::string& name);

	unsigned int CompileShader(unsigned int type, const std::string& source);
	void CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
public:
	Shader(const std::string& filepath);
	Shader(const char *vertexShaderSource,const char *fragmentShaderSource);
	~Shader();

	void Bind() const;
	void Unbind() const;
	
	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
	void SetUniform4f(const std::string& name, const glm::vec4 &value);
	void SetUniformMatrix4fv(const std::string& name, const glm::mat4 &mat);
};
