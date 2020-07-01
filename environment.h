#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>


using namespace std;
#define eps 0.001
typedef struct point 
{
    double x;
    double y;
    double theta;
    point(){};
    ~point(){};
    point(double x,double y)
    {
        this->x = x;
        this->y = y;
        this->theta = 0;
    }
    point(double x,double y,int theta)
    {
        this->x = x;
        this->y = y;
        this->theta = theta;
    }
    bool operator == (const point& rhs)const
    {
        if(abs(this->x - rhs.x)<eps && abs(this->y- rhs.y)<eps && abs(this->theta- rhs.theta)<eps)
            return true;
        return false;
    }
}point;

struct Node
{
public:
    int current_ID; // ID of the Node
    int parent_ID; // backpointer ID of the Node
    double g; // Node g val
    double f; // Node f val
    point S; // NOde (x,y,theta)
    Node()
    {
        this->current_ID = NULL;
        this->parent_ID = NULL;
        this->g = INT32_MAX;
        this->f = INT32_MAX;
        this->S = point();
    }
    // Node(point& S)
    // {
    //     this->S = S;
    // }
    Node(int P_ID,point S)
    {
        this->parent_ID = P_ID;
        this->S = S;
    }
    // Node(int P_ID,point& S,double& g)
    // {
    //     this->parent_ID = P_ID;
    //     this->S = S;
    //     this->g = g;
    // }
    bool operator ==(const Node& rhs)const
    {
        if(this->S == rhs.S)
            return true;
        return false;
    }
};
struct compare
{
    bool operator()(const Node& N1, const Node& N2)
    {   
        return N1.f > N2.f;
    }
};
struct mycomparator
{
    bool operator()(const Node& N1, const Node& N2)
    {   
        return N1.current_ID > N2.current_ID;
    }
};
template <typename T>
void print2DVector(vector<vector<T>> vec)
{
    for(int i=0;i<vec.size();i++)
    {
        for(int j=0;j<vec[0].size();j++)
        {
            std::cout<<vec[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}

class Env_res
{
public:
    double res_size = 0.5; // default for now
    // for now consider 8 connected grid
    double m_res = (int) ceil(1/res_size);
    int NUMOFDIRS = 8;
    // int grid_x = (int) ceil(5/res_size);
    // int grid_y = (int) ceil(5/res_size);
    int map_x = 5;
    int map_y = 5;
    int grid_x = map_x*m_res;
    int grid_y = map_y*m_res;
    vector<vector<int> > grid{ vector<vector<int>> (grid_x, vector<int> (grid_y,0))}; // initiated to 0
    double* dX = new double[NUMOFDIRS] {-1, -1, -1,  0,  0,  1, 1, 1};
    double* dY = new double[NUMOFDIRS] {-1,  0,  1, -1,  1, -1, 0, 1};
    // grid of 5,5 which is free in all cells but in 2nd row only a narrow space is left
    Env_res(){};
    ~Env_res(){};
    int get_grid_x(){return this->grid_x;}
    int get_grid_y(){return this->grid_x;}

    bool inBounds(point p)
    {
        if(p.x>=0 && p.x<map_x && p.y>=0 && p.y<map_y)
            return true;
        return false;
    }
    bool inBounds(double x, double y)
    {
        if(x>=0 && x<map_x && y>=0 && y<map_y)
            return true;
        return false;
    }

    bool valid(point p) // any point need not be in resolution space
    {  
        if(inBounds(p))
        {     
            if(p.y >= 1.5 && p.y <=2.5)
            {
                if(p.x <= 2 || p.x >=2.8)
                    return false;
            }
        }
        return true;
    }
     bool valid(double x, double y) // any point need not be in resolution space
    {  
        if(inBounds(x,y))
        {     
            if(y >= 1.5 && y <=2.5)
            {
                if(x <= 2 || x >=2.8)
                    return false;
            }
        }
        return true;
    }
    bool cont_to_disc(point p,point& p_g)
    {
        std::cout<<"\n multplied by "<<m_res<<" x "<<p.x*m_res<<" y "<< p.y*m_res<<"\n";
        // if(fmod((p.x*m_res), 1.0)<eps && fmod((p.y*m_res),1.0)<eps)
        {
            // p_g.x =(int) ceil(p.x/res_size);
            // p_g.y = (int) ceil(p.y/res_size);
            p_g.x =  round(p.x*m_res);
            p_g.y =  round(p.y*m_res);
            return true;
        }
        return false;
    }

    vector<point> get_successors(point s)
    {
        vector<point> succ_vec;
        for(int i =0;i<NUMOFDIRS;i++)
        {
            double x =  s.x + dX[i]*res_size;
            double y = s.y + dY[i]*res_size;
            point p(x,y);
            if(valid(p))
                succ_vec.push_back(p);
        }
        return succ_vec;
    }
    
    // 5x5 grid
    void grid_update()
    {
        for(int i=0;i<grid_x;i++)
        {
            for(int j=0;j< grid_y;j++)
            {
                point p(i*res_size,j*res_size,0);
                if(!valid(p))
                    grid[i][j] = 1;
                std::cout<<grid[i][j]<<" ";
            }
            std::cout<<"\n";
        }
        std::cout<<"\n";
        // point p(0.5,0.5);
        // vector<point> succ = get_successors(p);
        // for(int i = 0;i<succ.size();i++)
        // {
        //     point p = succ[i];
        //     point p_g;
        //     if(cont_to_disc(p,p_g))
        //     {
        //         // std::cout<<"p.x & p.y"<<p.x<<" "<<p.y<<"p_g.x & p_g.y"<<p_g.x<<" "<<p_g.y<<"\n";
        //         grid[p_g.x][p_g.y] = 8;
        //     }
        // }
        // for(int i=0;i<grid_x;i++)
        // {
        //     for(int j=0;j< grid_y;j++)
        //     {
        //         std::cout<<grid[i][j]<<" ";
        //     }
        //     std::cout<<"\n";
        // }

    }
    void grid_path_viz(vector<point> path)
    {
        for(auto p : path)
        {
            std::cout<<"p.x & p.y"<<p.x<<" "<<p.y;
            point p_g;
            if(!cont_to_disc(p,p_g))
            {
                std::cout<<"res is not right \n";
                break;
            }
            std::cout<<"p_g.x & p_g.y"<<p_g.x<<" "<<p_g.y<<"\n";
            grid[p_g.x][p_g.y] = 5;
        }
        print2DVector(grid);
    }
};

 

#endif