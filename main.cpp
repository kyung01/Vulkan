#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include "HelloTriangleApplication.h"

#pragma comment(lib,"user32.lib") 
#pragma comment(lib,"gdi32.lib") 
#pragma comment(lib,"shell32.lib") 


int main() { 
	HelloTriangleApplication app;
	try {
		app.run();
	}
	catch (const std::exception e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;

	}
	return EXIT_SUCCESS;

	/*
	*/
}