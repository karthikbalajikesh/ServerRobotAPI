#pragma once

#include "path.hpp"
#include "tcp.h"
#include "behavior.h"
#include<vector>
#include<utility>
#include "message.hpp"
#include  "Dijkstra.h"
#include "DijkstraPRM.h"
#include<chrono>
#include<boost/asio.hpp>
#include<string>

using std::cout;
using std::endl;
using std::string;
using std::pair;
using std::vector;

#define mp std::make_pair
typedef std::pair<float,float> floatpair;
#define SOCKET boost::asio::ip::tcp::socket

class Server: public TCP,public BehaviorPlanner{
private:
    int numSamples =800; // number of sample points
    int zmax = 3;
    int xmax = 3;
    int cellwidth = 10;
    int cellheight = 10;
    float radius = 0.25;



public:
    // Variables. 
    /* We need one variable consisting of obstacles from server*/
    message Data;
    // We need to make a vector of obstacles in double
    vector<floatpair> ObstacleVector;
    DijkstraPRM PathPlanner;
    vector<floatpair> Pathway;
    vector<float> Velocity;
    // will have to include behavioral planner (Inherited)
    // will have to include path.
    Path Waypoints;


    // Default Constructor
    Server();
    void Communicate();
    void setupConnection();
    void readMessage();
    void deSerialize(boost::asio::streambuf &buf);
    void CreateObstacleVector();
    void getTrajectory();
    void PlanPath();
    void sendMessage();


};