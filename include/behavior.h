#pragma once

#include<iostream>
#include<string>
#include "message.hpp"
#include<vector>
#include<utility>

using std::cout;
using std::vector;
using std::pair;
using std::string;
typedef pair<float,float> floatpair;

class BehaviorPlanner{
public:
    // variable to hold destination
    pair<float,float> destination;
    string Maneuver;

    // constructor
    BehaviorPlanner();
    BehaviorPlanner(message &M);

    // Function to decide Manuever
    void getDestination(message &M);
    void DecideManuever();
    void getHumanInput();
    // Check if the human input is viable
    void CheckValidity();

    // Function to find the mid point
    // of two coordinates
    floatpair getMidPoint(floatpair &C1,floatpair &C2);



};