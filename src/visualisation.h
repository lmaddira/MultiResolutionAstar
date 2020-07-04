#ifndef VISUALISATION_H
#define VISUALISATION_H
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
// Include GLM
#include <glm/glm.hpp>
#include "environment.h"



class visualise : public Env_res
{
public:
    int SCREEN_WIDTH = 640;
    int SCREEN_HEIGHT = 480;
    int scaling_factor = 60;
    // lets start the window (0,0) at (200,100) 
    int border = (res_size*scaling_factor);
    GLfloat x1 = 200-border/2 ,y1 = 100 - border/2;
    GLfloat x2 = x1+ (scaling_factor* map_x)+ border;
    GLfloat y2 = y1 + (scaling_factor* map_y) + border;
    GLFWwindow* window;
        
    void initialise();
    void Draw_lines();
    void Draw_obstacles();
    void Draw_path(std::vector<point>& path,point& start, point& goal);
    void writeText(int x, int y, char *string);
    void Draw_environment(); 
};

#endif