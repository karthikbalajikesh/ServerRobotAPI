#include "behavior.h"

using std::cout;
using std::vector;
using std::pair;
using std::string;
#define mp std::make_pair

BehaviorPlanner::BehaviorPlanner(){
    destination = mp(0,0);
    Maneuver = "Lane";
}

void BehaviorPlanner::getDestination(message &M){
    int left_size = M.LaneLeft.size();
    int right_size = M.LaneRight.size();
    destination = getMidPoint(M.LaneLeft[left_size-1],
                            M.LaneRight[right_size-1]);
    
}


// Function to find the midpoint of two coordinates
floatpair BehaviorPlanner::getMidPoint(floatpair &C1,
                                floatpair &C2){
    /*   
         The function finds the mid point of two coordinates
         we will use this to find the center of the final lane point
    */
    floatpair midpoint = mp(0,0);
    midpoint.first = (C1.first + C2.first)*0.5;
    midpoint.second = (C1.second + C2.second)*0.5;

    return midpoint;

}


