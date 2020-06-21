#ifndef MRASTAR_H
#define MRASTAR_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "planner.h"

using namespace std;



vector<point> low_resolution_actions(point S_start);
vector<point> high_resolution_actions(point S_start);

struct resolution
{
    int no_of_resolutions; // no of resolutions
    vector<point> resolution; // each resolution in x,y,theta
    // resolution numbering is the index of vector
    // always 0- highest res, n- lowest res  and strict subsets of eachother to enhance max sharing
};


class MultiResolutionAstar
{
public:
    resolution R;
    point start;
    point goal;
    int current_resolution;
    vector<vector<Node>> OPEN_vector;
    vector<unordered_map<Node,double>> CLOSED_vector;
    MultiResolutionAstar(resolution R,point start,point goal)
    {
        this->R = R;
        this->start = start;
        this->goal = goal;
        this->current_resolution = NULL;
        for(int i=0;i<this->R.no_of_resolutions;i++)
        {
            vector<Node> OPEN;
            this->OPEN_vector.push_back(OPEN);
        }
        for(int i=0;i<this->no_of_resolutions;i++)
        {
            unordered_map<Node,double> CLOSED;
            this->CLOSED_vector.push_back(CLOSED);
        }
    }
    // will return all the resolutions this point S belongs to
    vector<int> GetSpaceIndices(point S)  
    {
        std::vector<int> index;
        for(i=0;i< R.no_of_resolutions;i++)
        {
            point P = R.resolution[i];
            if(P.x%S.x == 0 && P.y%S.y == 0 P.theta%S.theta == 0)
                index.push_back(i);
        }
        return index;
    }
    void ChooseQueue()
    {
        if(current_resolution == NULL) // its the first time to choose queue
            current_resolution = 0;
        else if (current_resolution+1 < R.no_of_resolutions)
            current_resolution++;
        else 
            current_resolution = 0;
        return;
    }
    bool OPENi_notNull()
    {
        for(int i=0;i<OPEN_vector.size();i++)
        {
            if(OPEN_vector[i].size() != 0)
                return true;
        }
        return false;
    }
    double heuristics(point& S)
    {
        return sqrt(pow((S.x-goal.x),2),pow((S.y-goal.y),2));
    }

    vector<point> find_path() // incomplete
    {   
        Node S_start; // make node with its ID as 0
        Node S_goal;
        S_start.current_ID = 0;
        S_start.S = start;
        S_start.g = 0;
        S_goal.S = goal; 
        vector<int> start_indices = GetSpaceIndices(start);
        for(int i=0;i< start_indices.size();i++)
        {
            OPEN_vector[start_indices[i]].push_back(S_start);
        }
        while(OPENi_notNull())
        {
            ChooseQueue();
            vector<Node> OPENi = OPEN_vector[current_resolution];
            vector<Node> OPEN0;
            make_heap(OPENi.begin(),OPENi.end(),Compare());
            push_heap(OPENi.begin(),OPENi.end(),Compare());
            Node min_node1 = OPENi.front();
            Node min_node2;
            if(current_resolution != 0)
            {
                OPEN0 = OPEN_vector[0];
                make_heap(OPEN0.begin(),OPEN0.end(),Compare());
                push_heap(OPEN0.begin(),OPEN0.end(),Compare());
                min_node2 = OPEN0.front();
                
            }

        }

    }



};



#endif
