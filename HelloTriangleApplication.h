#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cstring>>

class HelloTriangleApplication {
public:
	const int WIDTH = 800; 
	const int HEIGHT = 600;

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif


	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}
private:
	
	GLFWwindow* window;
	VkInstance instance;

	void initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		window = glfwCreateWindow(WIDTH,HEIGHT, "Vulkan", nullptr, nullptr);

	}
	void initVulkan() {
		createInstance();

	}
	void mainLoop() {
		while (!glfwWindowShouldClose(window)) { 
			glfwPollEvents(); 
		}

	}
	void cleanup() {
		vkDestroyInstance(instance, nullptr);
		glfwDestroyWindow(window); 
		glfwTerminate();
	}

	void createInstance() { 

		//Check required extensions before creating the instance 
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
			nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
			extensions.data());

		std::cout << "vector<VkExtensionProperties> extensions.size = " << extensions.size() << std::endl;
		

		VkApplicationInfo appInfo = {}; 
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO; 
		appInfo.pApplicationName = "Hello Triangle"; 
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine"; 
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0); 
		appInfo.apiVersion = VK_API_VERSION_1_0; 

		VkInstanceCreateInfo createInfo = {}; 
		
		///Validation layer settings start
		if (enableValidationLayers) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}
		//Validation layer settings end

		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO; 
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0; 
		auto glfwExtensions = getRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(glfwExtensions.size());
		createInfo.ppEnabledExtensionNames = glfwExtensions.data();

		//Below codes are deprecated in favor of using our getRequiredExtensions function
		//const char** glfwExtensions;
		//glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		//createInfo.enabledExtensionCount = glfwExtensionCount;
		//createInfo.ppEnabledExtensionNames = glfwExtensions;


		VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
		if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}
		else {
			std::cout << "Success: Created vulkan instance\n";
		}


		if (enableValidationLayers && !checkValidationLayerSupport()) {
			throw std::runtime_error("validation layers requested, but not available!");
		}
		else {
			std::cout << "Success: Requested validation layers are available\n";
		}
	

	}
	bool checkValidationLayerSupport() {
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
		for (const char* layerName : validationLayers) {
			bool layerFound = false;
			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}
			if (layerFound)
				return true;
		}
		return false;
	}

	std::vector<const char*> getRequiredExtensions() {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
		if (enableValidationLayers) {
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}
		return extensions;

	}
};