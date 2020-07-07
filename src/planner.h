#ifndef PLANNER_H
#define PLANNER_H

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include "environment.h"
// #include "continousPlanner.h"
using namespace std;

class planner : public Env_res
{
public:
    point start;
    point goal;
    planner(){
        OPEN.clear();
        CLOSED.clear();
        CSPACE.clear();
        Union.clear();
    }
    ~planner(){}
    vector<Node> OPEN;// relook into data structure of OPEN maybe binary tree 
    vector<Node> CLOSED;
    vector<Node> CSPACE;
    unordered_map<int,Node> Union;
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
    double distance(point& p1,point& p2)//in continous space
    {// Euclidean dist currently for forward search
        return round(1000*sqrt(pow((p1.x-p2.x),2)+pow((p1.y-p2.y),2)))/1000;
    }
    bool in_OPEN(point& succ)
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
    void add_node_OPEN(int parent_ID,double& g,double& f,point& p)
    {
        Node n(parent_ID,p);
        n.g = g;
        n.f = round(f*1000)/1000;
        n.current_ID = OPEN.size()+CLOSED.size()+CSPACE.size()+1;// to be changed with additional CSpace
        OPEN.push_back(n);
        std::cout<<" new node ID OPEn "<<n.current_ID<<" f val"<<f<<"point "<<n.S.x<<" ,"<<n.S.y<<" parent "<<n.parent_ID<<"\n";
        return ;
    }
    void add_node_CSPACE(Node& parent,Node& newNode)
    {
        newNode.parent_ID = parent.current_ID;
        newNode.g = parent.g + cost(parent.S,newNode.S);
        newNode.f = newNode.g + heuristics(newNode.S);
        newNode.current_ID = OPEN.size()+CLOSED.size()+CSPACE.size()+1;
        CSPACE.push_back(newNode);
        std::cout<<" new node ID cspace "<<newNode.current_ID<<" f val"<<newNode.f<<"point "<<newNode.S.x<<" ,"<<newNode.S.y<<" parent "<<newNode.parent_ID<<"\n";
        return;
    }
    void addReconnectNodeToOPEN(Node& parent,point& p)
    {
        if(valid(p) && !in_OPEN(p))
        {
            Node n(parent.current_ID,p);
            n.g = parent.g + cost(parent.S,p);
            n.f = n.g + heuristics(p);
            n.current_ID = OPEN.size()+CLOSED.size()+CSPACE.size()+1;// to be changed with additional CSpace
            OPEN.push_back(n);
            std::cout<<" new node ID reconnect "<<n.current_ID<<" f val"<<n.f<<"point "<<n.S.x<<" ,"<<n.S.y<<" parent "<<n.parent_ID<<"\n";
        }
        return ;
    }
    void generateUnion()
    {
        for(auto n:OPEN)
            Union.insert(make_pair(n.current_ID,n));
            // Union.push_back(n);
        for(auto n:CLOSED)
            Union.insert(make_pair(n.current_ID,n));
            // Union.push_back(n);
        for(auto n:CSPACE)
            Union.insert(make_pair(n.current_ID,n));
        return;
    }    

};

class partial_expansion_A_star : public planner
{
public:
    partial_expansion_A_star(){}
    ~partial_expansion_A_star(){}
    partial_expansion_A_star(point start,point goal): planner(start,goal){}
       
    // Node s_goal; I don't think this is currently necessary
    
    double w1 = 2; // weight
    bool goal_reached(Node& n)//in continous space
    {
        // std::cout<<" n "<<n.S.x<<" ,"<<n.S.y<<" goal "<<goal.x<<" ,"<<goal.y<<"\n";
        if(abs(n.S.x-goal.x)< eps && abs(n.S.y- goal.y)<eps)
        {
            std::cout<<" reached goal \n";
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
    void get_minNode_closed(Node& min_node)
    {
        std::make_heap(CLOSED.begin(),CLOSED.end(),compare());
        std::push_heap(CLOSED.begin(),CLOSED.end(),compare());
        min_node = CLOSED.front();
        // std::pop_heap(CLOSED.begin(),CLOSED.end(),compare());
        // CLOSED.pop_back();
        std::cout<<" new min_node closed "<<min_node.current_ID<<" min node "<<min_node.S.x<<" ,"<<min_node.S.y<<" f val "<<min_node.f<<"\n";
        return;
    }
    void PEAstar(Node& min_node)
    {
        double next_best = INT16_MAX;
        vector<point> all_succ = get_successors(min_node.S);
        // std::cout<<" no of succ "<<all_succ.size()<<"\n";
        std::cout<<" OPEN \n";
        for(auto n: OPEN)
        {
            std::cout<<" ID "<<n.current_ID;//<<" f val "<<n.f;
        }
        std::cout<<"\n in closed";
        for(auto n: CLOSED)
        {
            std::cout<<" ID "<<n.current_ID;//<<" f val "<<n.f;
        }
        std::cout<<"\n OPEN.size "<<OPEN.size()<<"\n";
        for(auto succ : all_succ)
        {
            if(inBounds(succ) && !in_CLOSED(succ))
            {
                if(!in_OPEN(succ))
                {
                    double g = min_node.g + cost(succ,min_node.S);
                    double f = g + w1* heuristics(succ);
                    f = round(1000*f)/1000;
                    // std::cout<<" f val "<<f;
                    if(min_node.f == f)
                        add_node_OPEN(min_node.current_ID,g,f,succ);
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
    void PEAstar_standalone()
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
            // std::cout<<" no of succ "<<all_succ.size()<<"\n";
            // std::cout<<" OPEN \n";
            // for(auto n: OPEN)
            // {
            //     std::cout<<" ID "<<n.current_ID;//<<" f val "<<n.f;
            // }
            // std::cout<<"in closed \n";
            // for(auto n: CLOSED)
            // {
            //     std::cout<<" ID "<<n.current_ID;//<<" f val "<<n.f;
            // }
            // std::cout<<"OPEN.size "<<OPEN.size()<<"\n";
            for(auto succ : all_succ)
            {
                if(inBounds(succ) && !in_CLOSED(succ))
                {
                    if(!in_OPEN(succ))
                    {
                        double g = min_node.g + cost(succ,min_node.S);
                        double f = g + w1* heuristics(succ);
                        f = round(1000*f)/1000;
                        // std::cout<<" f val "<<f;
                        if(min_node.f == f)
                            add_node_OPEN(min_node.current_ID,g,f,succ);
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
            generateUnion();
            int current = n.current_ID;
            int count =0;
            while(current != s_start.current_ID)
            {
                count++;
                auto current_node = Union.at(current);
                path.push_back(current_node.S);
                std::cout<<"current id "<<current<<" x "<<current_node.S.x<<" y "<<current_node.S.y<<"\n";
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