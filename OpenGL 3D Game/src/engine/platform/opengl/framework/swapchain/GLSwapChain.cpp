#include "engine/prehistoric/core/util/Includes.hpp"
#include "GLSwapChain.h"
#include "engine/config/FrameworkConfig.h"
#include "engine/prehistoric/common/framework/Window.h"

void GLSwapchain::SetupSwapchain(Window* window)
{
	this->window = window;

	//Enabling GL_TEXTURE_2D is deprecated, in debug mode, it will cause the program to break
	//glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
}

void GLSwapchain::SwapBuffers()
{
	glfwSwapBuffers((GLFWwindow*)window->GetWindowHandle());
}

void GLSwapchain::SetVSync(bool vSync) const
{
	glfwSwapInterval(vSync ? 1 : 0);
}

void GLSwapchain::SetWindowSize(uint32_t width, uint32_t height)
{
	glViewport(0, 0, width, height);
	FrameworkConfig::windowWidth = width;
	FrameworkConfig::windowHeight = height;
}

void GLSwapchain::SetClearColor(const float& red, const float& green, const float& blue, const float& alpha)
{
	glClearColor(red, green, blue, alpha);
}

void GLSwapchain::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0);
}

void GLSwapchain::DeleteSwapchain(void* device)
{
	
}