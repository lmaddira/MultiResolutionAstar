#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
// Include GLM
#include <glm/glm.hpp>
#include "environment.h"

void Draw_lines(Env_res& env, int& border,GLfloat& x1,GLfloat& x2,GLfloat& y1,GLfloat& y2)
{
    glColor3ub(0,255,0);
    glBegin(GL_LINES);
    glPointSize(100);
    for(int i=0;i<env.grid_y + 1;i++)
    {
        glVertex2f(x1,y1+ i*border);
        glVertex2f(x2,y1+ i*border);
    }
    for(int i=0;i<env.grid_x + 1;i++)
    {
        glVertex2f(x1+ i*border,y1);
        glVertex2f(x1 + i*border,y2);
    }
    
    glEnd();

}
void Draw_obstacles(GLfloat& x1,GLfloat& x2,GLfloat& y1,GLfloat& y2,int& scaling_factor,int& border)
{
    float y_obst_start = y1 + (1.5 * scaling_factor) + border/2;
    float y_obst_end = y1 + 2.5 * scaling_factor + border/2;
    float x_interm1 = x1 + 2* scaling_factor + border/2;
    float x_interm2 = x1 + 2.8* scaling_factor + border/2;
    GLfloat polygonVertices1[] =
    {
        x1,y_obst_start,0,
        x_interm1,y_obst_start,0,
        x_interm1,y_obst_end,0,
        x1,y_obst_end,0
    };
    GLfloat polygonVertices2[] =
    {
        x2,y_obst_start,0,
        x_interm2,y_obst_start,0,
        x_interm2,y_obst_end,0,
        x2,y_obst_end,0
    };
    glColor3ub(0,255,255);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,polygonVertices1);
    glDrawArrays(GL_POLYGON,0,4);
    glVertexPointer(3,GL_FLOAT,0,polygonVertices2);
    glDrawArrays(GL_POLYGON,0,4);
    glDisableClientState(GL_VERTEX_ARRAY);

}

void Draw_path(Env_res &env, std::vector<point>& path)
{
    int scaling_factor = 60;
    // lets start the window (0,0) at (50,50) 
    int border = (env.res_size*scaling_factor);
    GLfloat x1 = 200-border/2 ,y1 = 100 - border/2;
    GLfloat x2 = x1+ (scaling_factor* env.map_x)+ border;
    GLfloat y2 = y1 + (scaling_factor* env.map_y) + border;
    glColor3ub(0,0,255);
    glBegin(GL_LINE_STRIP);
    glPointSize(100);
    for(int i=0;i<path.size();i++)
    {
        float x = x1 + border/2+( path[i].x * scaling_factor);
        float y = y1 + border/2+( path[i].y * scaling_factor);
        glVertex2f(x,y);
    }    
    glEnd();
}
void writeText(Env_res& env, int x, int y, char *string)
{
    int scaling_factor = 60;
    // lets start the window (0,0) at (50,50) 
    int border = (env.res_size*scaling_factor);
    GLfloat x1 = 200-border/2 ,y1 = 100 - border/2;
    GLfloat x2 = x1+ (scaling_factor* env.map_x)+ border;
    GLfloat y2 = y1 + (scaling_factor* env.map_y) + border;
    glColor3f( 0, 0, 0 );
    
    glRasterPos2f(x1+ (x*scaling_factor), y1+(y*scaling_factor));
    int len, i;
    len = (int)strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
    }
}

void Draw_environment(Env_res& env) 
{
    int scaling_factor = 60;
    // lets start the window (0,0) at (50,50) 
    int border = (env.res_size*scaling_factor);
    GLfloat x1 = 200-border/2 ,y1 = 100 - border/2;
    GLfloat x2 = x1+ (scaling_factor* env.map_x)+ border;
    GLfloat y2 = y1 + (scaling_factor* env.map_y) + border;

    GLfloat polygonVertices[] =
    {
        x1,y1,0,
        x2,y1,0,
        x2,y2,0,
        x1,y2,0
    };
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glColor3ub(255,255,255);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,polygonVertices);
    glDrawArrays(GL_POLYGON,0,4);
    glDisableClientState(GL_VERTEX_ARRAY);
    Draw_lines(env,border,x1,x2,y1,y2);
    Draw_obstacles(x1,x2,y1,y2,scaling_factor,border);
    
}