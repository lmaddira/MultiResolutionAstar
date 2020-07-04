#include "planner.h"
#include "visualisation.h"
#include <GL/glut.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char** argv)
{
    Env_res env;
    std::cout<< env.get_grid_x()<<" "<< env.get_grid_y()<<"\n";
    env.grid_update();
    point start(0,0);
    point goal(4,4);
    partial_expansion_A_star planner(start,goal);
    planner.PEAstar();
    vector<point> path = planner.find_path();
    env.grid_path_viz(path);

    GLFWwindow* window;
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}
    glutInit(&argc,argv);
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
	// glClearColor(0,100,255,1);
	//Loop until the user closes the window
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
		Draw_environment(env);
        Draw_path(env,path);
        writeText(env,start.x,start.y,"start");
        writeText(env,goal.x,goal.y,"goal");
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	// Close OpenGL window and terminate GLFW
	glfwTerminate();


    return 0;
}