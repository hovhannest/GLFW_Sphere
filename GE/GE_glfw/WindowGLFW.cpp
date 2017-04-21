
#include "WindowGLFW.h"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
#include "..\GELog.h"
#include "../GEApp.h"
#include "Utils.h"
#include <iostream>

CWindowGLFW::CWindowGLFW(CGEApp* theApp) :
	m_Window(NULL),
	m_App(theApp)
{

}

CWindowGLFW::~CWindowGLFW()
{

}

void CWindowGLFW::Init()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		GELOG->Fatal(-1, "Failed to initialize GLFW");
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	m_Window = glfwCreateWindow(GEGetScreenWidth(), GEGetScreenHeight(), "Tutorial 01", NULL, NULL);
	if (m_Window == NULL)
	{
		glfwTerminate();
		GELOG->Fatal(-1, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.");
	}
	glfwMakeContextCurrent(m_Window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		GELOG->Fatal(-1, "Failed to initialize GLEW");
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwSwapInterval(1);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

void CWindowGLFW::Release()
{
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void CWindowGLFW::Update(float dt)
{

		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();
}

void CWindowGLFW::Render()
{
	if (m_Window)
	{
		glfwSwapBuffers(m_Window);
	}
}

bool CWindowGLFW::WindowShouldClose()
{
	if (m_Window)
	{
		return !(glfwGetKey(m_Window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(m_Window) == 0);
	}
	return true;
}

void CWindowGLFW::WaitEventsTimeout(float dt)
{
	glfwWaitEventsTimeout(dt);
}
