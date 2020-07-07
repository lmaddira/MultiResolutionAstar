#include "planner.h"
#include "continousPlanner.h"


class mixedPlanner : public continousPlanner, public partial_expansion_A_star
{
public:
    std::vector<point> mixedPlan()
    {
        while(1)
        {
            if(OPEN.size() != 0 && CLOSED.size() == 0)
            {

            }
        }

    }

};