#ifndef PLANNER_H
#define PLANNER_H

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
    double res_size = 1; // default for now
    // for now consider 8 connected grid
    double m_res = (int) ceil(1/res_size);
    int NUMOFDIRS = 8;
    // int grid_x = (int) ceil(5/res_size);
    // int grid_y = (int) ceil(5/res_size);
    int grid_x = 5*m_res;
    int grid_y = 5*m_res;
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
        if(p.x>=0 && p.x<grid_x && p.y>=0 && p.y<grid_y)
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


class planner : public Env_res
{
public:
    point start;
    point goal;
    planner(){};
    ~planner(){};
    planner(point start,point goal)
    {
        this->goal = goal;
        this->start = start; 
    }
    Node s_start;
    double heuristics(point& p)//in continous space
    {// Euclidean dist currently for forward search
        return round(1000*sqrt(pow((p.x-goal.x),2)+pow((p.y-goal.y),2)))/1000;
    }
    double cost(point& p1,point& p2)//in continous space
    {// Euclidean dist currently for forward search
        return round(1000*sqrt(pow((p1.x-p2.x),2)+pow((p1.y-p2.y),2)))/1000;
    }
    

}; 

class partial_expansion_A_star : public planner
{
public:
    partial_expansion_A_star(){};
    ~partial_expansion_A_star()
    {
        OPEN.clear();
        CLOSED.clear();
    }
    partial_expansion_A_star(point start,point goal): planner(start,goal){}
       
    // Node s_goal; I don't think this is currently necessary
    vector<Node> OPEN;// relook into data structure of OPEN maybe binary tree 
    vector<Node> CLOSED;
    unordered_map<int,Node> Union;
    double w1 = 2; // weight
    bool goal_reached(Node& n)//in continous space
    {
        std::cout<<" n "<<n.S.x<<" ,"<<n.S.y<<" goal "<<goal.x<<" ,"<<goal.y<<"\n";
        if(abs(n.S.x-goal.x)< eps && abs(n.S.y- goal.y)<eps)
        {
            std::cout<<" got here \n";
            CLOSED.push_back(n);
            return true;
        }
        return false;
    }
    
    void Init_planner()
    {
       s_start.current_ID = 0;
       s_start.S = start;
       s_start.g =0;
       s_start.f = w1*round(1000*heuristics(start))/1000; 
       OPEN.clear(); 
       CLOSED.clear();
       OPEN.push_back(s_start);
       std::cout<<"intiated planner \n";
    }
    bool in_CLOSED(point& S)
    {
        // std::cout<<" in closed ";
        for(auto n :CLOSED )
        {
            // std::cout<<" ID "<<n.current_ID<<" fval "<<n.f<<"\n";
            if(n.S == S)
                return true;
        }
        return false;
    }

    bool in_OPEN_update(Node& min_node,point& succ)
    {
        // std::cout<<"in open ";
        for(auto n : OPEN)
        {
            // std::cout<<" ID "<<n.current_ID<<" fval "<<n.f<<"\n";
            if(n.S == succ)
            {
                // std::cout<<"found in open \n";
                return true;
            }
        }
        return false;
    }
    void get_minNode(Node& min_node)
    {
        std::make_heap(OPEN.begin(),OPEN.end(),compare());
        std::push_heap(OPEN.begin(),OPEN.end(),compare());
        min_node = OPEN.front();
        std::pop_heap(OPEN.begin(),OPEN.end(),compare());
        OPEN.pop_back();
        std::cout<<" new min_node "<<min_node.current_ID<<" min node "<<min_node.S.x<<" ,"<<min_node.S.y<<" f val "<<min_node.f<<"\n";
        return;
    }
    void add_node(int parent_ID,double& g,double& f,point& p)
    {
        Node n(parent_ID,p);
        n.g = g;
        n.f = round(f*1000)/1000;
        n.current_ID = OPEN.size()+CLOSED.size()+1;// to be changed with additional CSpace
        OPEN.push_back(n);
        std::cout<<" new node ID"<<n.current_ID<<" f val"<<f<<"point "<<n.S.x<<" ,"<<n.S.y<<" parent "<<n.parent_ID<<"\n";
        return ;
    }
    void PEAstar()
    {
        Init_planner();
        int count = 0;
        while(OPEN.size()!=0)
        {
            count++;
            Node min_node;
            get_minNode(min_node);// pops node from OPEN but doesn't push into CLOSED
            if(goal_reached(min_node))break;
            double next_best = INT16_MAX;
            vector<point> all_succ = get_successors(min_node.S);
            std::cout<<" no of succ "<<all_succ.size()<<"\n";
            std::cout<<" OPEN \n";
            for(auto n: OPEN)
            {
                std::cout<<" ID "<<n.current_ID;//<<" f val "<<n.f;
            }
            std::cout<<"in closed \n";
            for(auto n: CLOSED)
            {
                std::cout<<" ID "<<n.current_ID;//<<" f val "<<n.f;
            }
            std::cout<<"OPEN.size "<<OPEN.size()<<"\n";
            for(auto succ : all_succ)
            {
                if(inBounds(succ) && !in_CLOSED(succ))
                {
                    if(!in_OPEN_update(min_node,succ))
                    {
                        double g = min_node.g + cost(succ,min_node.S);
                        double f = g + w1* heuristics(succ);
                        f = round(1000*f)/1000;
                        // std::cout<<" f val "<<f;
                        if(min_node.f == f)
                            add_node(min_node.current_ID,g,f,succ);
                        else
                        {
                            if(next_best > f)
                                next_best = f;
                        }
                    }
                }
            }
            if(next_best<INT16_MAX)
            {
                min_node.f = next_best;
                OPEN.push_back(min_node);
                // std::cout<<" min_node ID "<<min_node.current_ID<<" f val "<<min_node.f<<"\n";
            }else
            {
                std::cout<<"\n entered closed "<<min_node.current_ID<<" with f val"<<min_node.f<<"\n";
                CLOSED.push_back(min_node);
            }
        }
    }
    vector<point> find_path()
    {
        vector<point> path; 
        Node n = CLOSED.back();
        if(goal == n.S)
        {
            for(auto n:OPEN)
                Union.insert(make_pair(n.current_ID,n));
                // Union.push_back(n);
            for(auto n:CLOSED)
                Union.insert(make_pair(n.current_ID,n));
                // Union.push_back(n);
            int current = n.current_ID;
            int count =0;
            while(current != s_start.current_ID)
            {
                count++;
                auto current_node = Union.at(current);
                path.push_back(current_node.S);
                std::cout<<"current "<<current<<"\n";
                current = current_node.parent_ID;
            }
            path.push_back(Union.at(current).S);
        }else
        {
            std::cout<<"path can't be found in this resolution\n";
        }
        
        return path;
    }
};



#endif