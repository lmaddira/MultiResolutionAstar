// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
#include "visualisation.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


// Include GLM
#include <glm/glm.hpp>
using namespace glm;


int main( void )
{
	GLFWwindow* window;
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}
	// Open a window and create its OpenGL context
	window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Display", NULL, NULL);
	if( !window){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

    
    glViewport(0 ,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,SCREEN_WIDTH,0,SCREEN_HEIGHT,0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	Env_res env;
	// glClearColor(0,100,255,1);
	//Loop until the user closes the window
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
		Draw_environment(env);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

