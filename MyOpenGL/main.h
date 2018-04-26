#pragma once
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
extern unsigned int WIDTH;
extern unsigned int HEIGHT;
static const std::string RESOURCES_PATH = "F:\\Visual Studio Projects\\MyOpenGL\\MyOpenGL\\Resources\\"; //"F:\\Visual Studio Projects\\MyOpenGL\\MyOpenGL\\Resources\\"; //"C:\\Users\\\\source\\repos\\MyOpenGL\\MyOpenGL\\Resources\\"; //"../../MyOpenGL/Resources/";
static std::string getexepath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
}

