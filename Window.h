#pragma once
#include <GL\glew.h>
//#include <GL\wglew.h>
#include <GLFW\glfw3.h>
#include <iostream>


#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 800
#endif

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 600
#endif

#ifndef WINDOW_NAME
#define WINDOW_NAME "OpenGL"
#endif

class Window
{
private:
	//initialize
	GLFWwindow *m_window;

public:
	bool Init()
	{
		//initialize glfw
		if (!glfwInit()) return false;
		////set glfw options
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		//create a window object
		m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);
		if (!m_window) { glfwTerminate(); return false; }
		glfwMakeContextCurrent(m_window);

		////set callback functions
		//glfwSetKeyCallback(m_window, key_callback);

		//glewExperimental ensures GLEW uses more modern techniques for managing OpenGL functionality.
		glewExperimental = GL_TRUE;
		//initialize GLEW.
		if (glewInit() != GLEW_OK) { glfwTerminate(); return false; }

		//define the viewport to transform processed coordinates from
		//the -1 to 1 range to screen coordinates
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		return true;
	}

	bool step()
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		return !glfwWindowShouldClose(m_window);
	}
	bool term()
	{
		glfwTerminate();
		return true;
	}



	int width() { return WINDOW_WIDTH; }
	int height() { return WINDOW_HEIGHT; }
	GLFWwindow *getHandle() { return m_window; }

	//void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
	//{
	//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	//		glfwSetWindowShouldClose(window, GL_TRUE);
	//}
};
