#include "planner.h"
#include "visualisation.h"
#include "continousPlanner.h"
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
    continuousPlanner planner(start,goal);
    // planner.PEAstar_standalone();
    planner.mixedPlan();
    vector<point> path = planner.find_path();
    env.grid_path_viz(path);
    std::cout<< "printing OPEN size "<<planner.OPEN.size()<<"\n";
    for(int i=0; i< planner.OPEN.size();i++)
    {
        std::cout<<" x "<<planner.OPEN[i].S.x<<" y "<<planner.OPEN[i].S.y<<"\n";
    }
    std::cout<< "printing CLOSED size "<<planner.CLOSED.size()<<"\n";
    for(int i=0; i< planner.CLOSED.size();i++)
    {
        std::cout<<" x "<<planner.CLOSED[i].S.x<<" y "<<planner.CLOSED[i].S.y<<"\n";
    }
    // std::cout<< "printing CSPACE size "<<planner.CSPACE.size()<<"\n";
    // for(int i=0; i< planner.CSPACE.size();i++)
    // {
    //     std::cout<<" x "<<planner.CSPACE[i].S.x<<" y "<<planner.CSPACE[i].S.y<<"\n";
    // }
    // visualisation

    while(!glfwWindowShouldClose(vis.window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
		vis.Draw_environment();
        vis.Draw_OPEN(planner.OPEN);
        vis.Draw_CLOSED(planner.CLOSED);
        vis.Draw_CSPACE(planner.CSPACE);
        // point p(2.3,2);
        // vis.Draw_point(p);
        vis.Draw_path(path,start,goal);
        glfwSwapBuffers(vis.window);
        glfwPollEvents();
    }
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
    

    return 0;
}