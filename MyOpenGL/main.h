#pragma once
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Vendor\imgui\imgui.h"
#include "Vendor\imgui\imgui_impl_glfw_gl3.h"
extern unsigned int WIDTH;
extern unsigned int HEIGHT;
static const std::string RESOURCES_PATH = "Resources\\"; //"../../MyOpenGL/Resources/"; //"F:\\Visual Studio Projects\\MyOpenGL\\MyOpenGL\\Resources\\"; //"C:\\Users\\151170\\source\\repos\\MyOpenGL\\MyOpenGL\\Resources\\"; //"../../MyOpenGL/Resources/";
static std::string getexepath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
}

