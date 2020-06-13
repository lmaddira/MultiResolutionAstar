#ifndef MRASTAR_H
#define MRASTAR_H

#include <iostream>
#include <vector>

using namespace std;
typedef struct point 
{
    int x;
    int y;
    double theta;
    point()
    {
        this->x = NULL;
        this->y = NULL;
        this->theta = NULL;
    }
    point(int x,int y,int theta)
    {
        this->x = x;
        this->y = y;
        this->theta = theta;
    }
}point;

class node
{
public:
    int current_ID;
    int parent_ID;
    double g;
    double f;
    point S;
    node()
    {
        this->current_ID = NULL;
        this->parent_ID = NULL;
        this->g = INT32_MAX;
        this->f = INT32_MAX;
        this->S = point();
    }
    node(int P_ID,point S)
    {
        this->parent_ID = P_ID;
        this->S = S;
    }
    node(int P_ID,point S,double g)
    {
        this->parent_ID = P_ID;
        this->S = S;
        this->g = g;
    }
};

vector<point> low_resolution_actions(point S_start);
vector<point> high_resolution_actions(point S_start);

int main()
{
    // get the start point from the world
    node S;
    S
}


#endif
