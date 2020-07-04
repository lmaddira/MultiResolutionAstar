#include "planner.h"
#include "visualisation.h"
#include <GL/glut.h>


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
    visualise vis;
    vis.Draw_path(path,start,goal);
    
    return 0;
}