#ifndef CONTINOUSPLANNER_H
#define CONTINOUSPLANNER_H

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstdio>
#include <ctime>
#include "environment.h"
#include "planner.h"
#include "../Dubins_Path/include/dubins.h"
using namespace std;

#if !defined(MAX)
#define	MAX(A, B)	((A) > (B) ? (A) : (B))
#endif

#if !defined(MIN)
#define	MIN(A, B)	((A) < (B) ? (A) : (B))
#endif

#define PI 3.141592654
#define MINSTEP 0.05
#define dubins_stepsize 0.05
int rand50() 
{ // rand() function will generate odd or even number with equal probability. If rand() generates odd number, the function will return 1 else it will return 0. 
    return rand() & 1; 
}  
bool rand75() 
{ // Random Function to that returns 1 with 75% probability and 0 with 25% probability using Bitwise OR 
    return rand50() | rand50(); 
} 
vector<point> path_points;
int pathConfiguration(double q[3], double x, void* user_data) {
  printf("%f, %f, %f, %f\n", q[0], q[1], q[2], x);
  point temp(q[0], q[1], q[2]);
  path_points.push_back(temp);
  return 0;
}

//the length of each link in the arm (should be the same as the one used in runtest.m)
// #define LINKLENGTH_CELLS 10
// Make something similar to bresenham_param to check validity of line segment
/*
typedef struct {
  int X1, Y1;
  int X2, Y2;
  int Increment;
  int UsingYIndex;
  int DeltaX, DeltaY;
  int DTerm;
  int IncrE, IncrNE;
  int XIndex, YIndex;
  int Flipped;
} bresenham_param_t;


void ContXY2Cell(double x, double y, short unsigned int* pX, short unsigned int *pY, int x_size, int y_size)
{
    double cellsize = 1.0;
	//take the nearest cell
	*pX = (int)(x/(double)(cellsize));
	if( x < 0) *pX = 0;
	if( *pX >= x_size) *pX = x_size-1;

	*pY = (int)(y/(double)(cellsize));
	if( y < 0) *pY = 0;
	if( *pY >= y_size) *pY = y_size-1;
}

void get_bresenham_parameters(int p1x, int p1y, int p2x, int p2y, bresenham_param_t *params)
{
  params->UsingYIndex = 0;

  if (fabs((double)(p2y-p1y)/(double)(p2x-p1x)) > 1)
    (params->UsingYIndex)++;

  if (params->UsingYIndex)
    {
      params->Y1=p1x;
      params->X1=p1y;
      params->Y2=p2x;
      params->X2=p2y;
    }
  else
    {
      params->X1=p1x;
      params->Y1=p1y;
      params->X2=p2x;
      params->Y2=p2y;
    }

   if ((p2x - p1x) * (p2y - p1y) < 0)
    {
      params->Flipped = 1;
      params->Y1 = -params->Y1;
      params->Y2 = -params->Y2;
    }
  else
    params->Flipped = 0;

  if (params->X2 > params->X1)
    params->Increment = 1;
  else
    params->Increment = -1;

  params->DeltaX=params->X2-params->X1;
  params->DeltaY=params->Y2-params->Y1;

  params->IncrE=2*params->DeltaY*params->Increment;
  params->IncrNE=2*(params->DeltaY-params->DeltaX)*params->Increment;
  params->DTerm=(2*params->DeltaY-params->DeltaX)*params->Increment;

  params->XIndex = params->X1;
  params->YIndex = params->Y1;
}

void get_current_point(bresenham_param_t *params, int *x, int *y)
{
  if (params->UsingYIndex)
    {
      *y = params->XIndex;
      *x = params->YIndex;
      if (params->Flipped)
        *x = -*x;
    }
  else
    {
      *x = params->XIndex;
      *y = params->YIndex;
      if (params->Flipped)
        *y = -*y;
    }
}

int get_next_point(bresenham_param_t *params)
{
  if (params->XIndex == params->X2)
    {
      return 0;
    }
  params->XIndex += params->Increment;
  if (params->DTerm < 0 || (params->Increment < 0 && params->DTerm <= 0))
    params->DTerm += params->IncrE;
  else
    {
      params->DTerm += params->IncrNE;
      params->YIndex += params->Increment;
    }
  return 1;
}

int IsValidLineSegment(double x0, double y0, double x1, double y1, double*	map,
		   int x_size,
 		   int y_size)

{
	bresenham_param_t params;
	int nX, nY; 
    short unsigned int nX0, nY0, nX1, nY1;

    //printf("checking link <%f %f> to <%f %f>\n", x0,y0,x1,y1);
    
	//make sure the line segment is inside the environment
	if(x0 < 0 || x0 >= x_size ||
		x1 < 0 || x1 >= x_size ||
		y0 < 0 || y0 >= y_size ||
		y1 < 0 || y1 >= y_size)
		return 0;

	ContXY2Cell(x0, y0, &nX0, &nY0, x_size, y_size);
	ContXY2Cell(x1, y1, &nX1, &nY1, x_size, y_size);

    //printf("checking link <%d %d> to <%d %d>\n", nX0,nY0,nX1,nY1);

	//iterate through the points on the segment
	get_bresenham_parameters(nX0, nY0, nX1, nY1, &params);
	do {
		get_current_point(&params, &nX, &nY);
		if(map[GETMAPINDEX(nX,nY,x_size,y_size)] == 1)
            return 0;
	} while (get_next_point(&params));

	return 1;
}
*/

class continuousPlanner : public partial_expansion_A_star
{
  public:
    continuousPlanner(){}
    ~continuousPlanner(){}
    continuousPlanner(point start, point goal): partial_expansion_A_star(start,goal){};
    double radius1 = 0.3; // this is the upper bound for extension of the point subject to changes later or can be an input from main
    double radius2 = 0.3; // ditto as above comment
    double weight = 1.1;
    double turning_radius = 0.4; // dubinspath turning radius
    
    point RandomSample()
    {
      point p;
      p.x = fmod(rand(),100*map_x-2)/100 +1.5; // random number between 1.5 to 4.5
      p.y = fmod(rand(),100*map_y-2)/100 + 2; // random number between 2 to 5

      int theta_index = fmod(rand(),NUMOFTHETAS);
      p.theta = Theta[theta_index]; // we can later change this to random number
      return p;
    }
    point obstacleSample()
    {
      point p;
      p.x = 2.3;
      p.y = 2;
      p.theta = goal.theta; // change later to arctan2(delX/delY);
      return p;
    }
    point goalSample()
    {
      return goal;
    } 

    void nearestNode(Node& nearNode,point& sample)
    {
        double min_dist = INT16_MAX;
        nearNode.S = start;
        for(int i=0;i<CLOSED.size();i++)
        {
            double dist = distance(sample,CLOSED[i].S);
            if(min_dist > dist)
            {
                min_dist = dist;
                nearNode = CLOSED[i];
            }else if(min_dist == dist && (abs(sample.theta - CLOSED[i].S.theta) < abs(sample.theta - nearNode.S.theta)))
            {
              min_dist = dist;
              nearNode = CLOSED[i];
            }
        }
        for(int i=0;i<CSPACE.size();i++)
        {
            double dist = distance(sample,CSPACE[i].S);

            if(min_dist > dist)
            {
                min_dist = dist;
                nearNode = CSPACE[i];
            }else if(min_dist == dist && (abs(sample.theta - CSPACE[i].S.theta) < abs(sample.theta - nearNode.S.theta)))
            {
              min_dist = dist;
              nearNode = CSPACE[i];
            }
        }
    }
    // extend using dubins path
    bool extend_dubinsPath_reconnect(Node& newNode,point sample) // true if new node has been found else false
    {
        Node nearNode;
        bool result = false;
        nearestNode(nearNode,sample);
        std::cout<<" nearest node is x "<<nearNode.S.x<<" y "<<nearNode.S.y<<" theta "<<nearNode.S.theta<<"\n";
        double dist = distance(nearNode.S,sample);
        double start[3] = {nearNode.S.x, nearNode.S.y, nearNode.S.theta}; // start from near node - {x,y,theta}
        double goal[3];
        if(dist > radius1)
        {
          double direction = atan2((nearNode.S.y - sample.y),(nearNode.S.x - sample.x));
          goal[0] = (start[0] + radius1 * cos(direction));
          goal[1] = (start[1] + radius1 * sin(direction));
          goal[2] = sample.theta;
        }else
        {
          goal[0] = sample.x;
          goal[1] = sample.y;
          goal[2] = sample.theta;
        }
        DubinsPath path;
        int res = dubins_shortest_path(&path, start, goal, turning_radius);
        if(res == 0)
        {
          path_points.clear();
          dubins_path_sample_many(&path, dubins_stepsize, pathConfiguration, NULL); // get the intermidiate points of path in path_points
          std::cout<<"found a path and interm points are "<<path_points.size()<<"\n";
          Node parent = nearNode;
          if(path_points.size() > 2)
          {
            for(int i=1;i<path_points.size();i++)
            {
              std::cout<<" in the loop point is "<< path_points[i].x<<" "<<path_points[i].y<<" "<<path_points[i].theta<<"\n"; 
              if(valid(path_points[i]))
              {
                std::cout<<" point is valid \n";
                newNode.S = path_points[i];
                add_node_CSPACE(parent,newNode);
                parent = newNode;
                if(!result) result = true;
              }
              else break;              
            }
          }

        }
        reconnectToGrid_dubinspath(newNode, nearNode); // see if it makes sense to try to reconnect to all interm points as well        
        return result;
    }
    bool reconnectToGrid_dubinspath(Node& newNode, Node& nearNode)
    {  
        // there can be a better way of doing this Check that
        double min_dist = radius2;
        for(int i=0;i<grid_x;i++)
        {
            for(int j=0;j< grid_y;j++)
            {
              double theta = goal.theta; // later change this to arctan2(delX/delY);
              point p(i*res_size,j*res_size,theta);
              double dist = distance(p,newNode.S);
              if(dist < radius2 && p!=nearNode.S && valid(p))
              {
                double start[] = {newNode.S.x,newNode.S.y,newNode.S.theta};
                double goal[] = {p.x,p.y,p.theta};
                DubinsPath path;
                int res = dubins_shortest_path(&path, start, goal, turning_radius);
                if(res == 0)
                {
                  path_points.clear();
                  dubins_path_sample_many(&path, dubins_stepsize, pathConfiguration, NULL);
                  Node parent = newNode;
                  Node child;
                  bool flag = true;
                  // enter in CSPACE only till last but one as last point would be the point in grid let that be connected in OPEN
                  for(int i=1;i<path_points.size()-1;i++)
                  {
                    if(valid(path_points[i]))
                    {
                      child.S = path_points[i];
                      add_node_CSPACE(parent,child);
                      parent = child;
                    }
                    else
                    {
                      flag = false;
                      break;
                    } 
                  }
                  if(flag)
                  {
                    addReconnectNodeToOPEN(newNode,p);
                    return true;
                  }
                }
              }
            }
        }
        return false;
    }
    // in general random extention
    bool extend(Node& newNode,point sample) // true if new node has been found else false
    {
        Node nearNode;
        bool result = false;
        nearestNode(nearNode,sample);
        std::cout<<" nearest node is x "<<nearNode.S.x<<" y "<<nearNode.S.y<<" theta "<<nearNode.S.theta<<"\n";
        double dist =0;
        point interm;
        int numofSamples = distance(nearNode.S,sample)/MINSTEP;
        std::cout<<"distance "<<distance(nearNode.S,sample)<<"\n";
        for(int i=0;i<numofSamples;i++)
        {
            interm.x = nearNode.S.x + ((double)(i)/(numofSamples-1))*(sample.x - nearNode.S.x); 
            interm.y = nearNode.S.y + ((double)(i)/(numofSamples-1))*(sample.y - nearNode.S.y);
            interm.theta = nearNode.S.theta + ((double)(i)/(numofSamples-1))*(sample.theta - nearNode.S.theta);
            std::cout<<"interm point "<<interm.x <<" "<<interm.y<<" "<<interm.theta;
            if(!valid(interm.x,interm.y) && i <= 1)
            {
                std::cout<<" this point not valid "<<interm.x<<" "<<interm.y<<" "<<interm.theta<<"\n";
                result = false;
                break;
            }    
            else if(distance(interm,nearNode.S) > radius1 || !valid(interm.x,interm.y))
            {
                result = true;
                break;
            }
        }
        if(result)
        {
            newNode.S = interm;
            add_node_CSPACE(nearNode,newNode);
        }
        return result;
    }
    bool reconnectToGrid(Node& newNode)
    {  
        // there can be a better way of doing this Check that
        double min_dist = radius2;
        for(int i=0;i<grid_x;i++)
        {
            for(int j=0;j< grid_y;j++)
            {
              double theta = goal.theta; // later change this to arctan2(delX/delY);
              point p(i*res_size,j*res_size,theta);
              double dist = distance(p,newNode.S);
              if(dist < radius2 && valid(p))
              {
                  addReconnectNodeToOPEN(newNode,p);
                  return true;
              }
            }
        }
        return false;
    }

    void cont_planner()
    {
        point r;
        if(rand75())
          if(rand50())
            r = RandomSample();
          else
            r = obstacleSample();
        else
          r = goalSample();
        std::cout<< "sample is x "<<r.x<<" y "<<r.y<<std::endl;
        Node newNode;
        bool result = extend_dubinsPath_reconnect(newNode,r);
        // bool result = extend(newNode,r); // adds new node to CSPACE as well
        // bool reconnectResult;
        // if(result)
        //     reconnectResult = reconnectToGrid(newNode);
    }
    void mixedPlan()
    {
      Init_planner();
      int count = 0;
      while(1)
      {
        count++;
        if(OPEN.size() != 0 && CLOSED.size() == 0)
        {
          Node min_node;
          get_minNode(min_node);
          if(goal_reached(min_node)) break;
          PEAstar(min_node);        
        }
        else{
          if(OPEN.size() == 0)
          {
            cont_planner();
          }
          else
          {

            Node min_node;
            get_minNode(min_node);
            if(goal_reached(min_node)) break;
            if( rand50() )
            {
              PEAstar(min_node);
            }else
            {
              cont_planner();
              OPEN.push_back(min_node);
            } 
          } 
        }
      }
    }
    

};




#endif