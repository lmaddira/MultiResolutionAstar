#include "planner.h"
#include "visualisation.h"
#include <GL/glut.h>


int main(int argc, char** argv)
{
    Env_res env;
    visualise vis;
    vis.initialise();
    // std::cout<< env.get_grid_x()<<" "<< env.get_grid_y()<<"\n";
    env.grid_update();
    point start(0,0);
    point goal(4,4);
    partial_expansion_A_star planner(start,goal);
    planner.PEAstar_standalone();
    vector<point> path = planner.find_path();
    env.grid_path_viz(path);

    // visualisation

    while(!glfwWindowShouldClose(vis.window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
		vis.Draw_environment();
        vis.Draw_path(path,start,goal);
        glfwSwapBuffers(vis.window);
        glfwPollEvents();
    }
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
    

    return 0;
}