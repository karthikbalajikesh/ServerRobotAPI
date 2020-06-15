#ifndef GRID2D_H
#define GRID2D_H
#endif

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include"GraphNode.h"
#include"Obstacle.h"

using std::vector;
using std::pair;
using std::priority_queue;

class Grid2D
{
public:
	vector<vector<GraphNode>> DiscretizedGrid;
	vector<Obstacle> ObstacleList;
	int Vehicle_size_z, Vehicle_size_x;
	int X_num_nodes;
	// default constructor
	Grid2D();
	// constructor with x and y fov and mesh size
	Grid2D(int xmax, int zmax, int cellWidth = 10, int cellHeight = 10, vector<pair<float, float>> coordinates = {});
	//One method to update obstacle from a list or heap into the grid
	void UpdateObstacles(vector<pair<float,float>>&, int i); // assume sorted list
	void UpdateObstacles(vector<pair<float, float>>&); // non sorted list
	void UpdateObstacles(priority_queue<pair<int, int>>); // replace with an object later
	// Consider creating an object called obstacle holding a sorted vector of coordinates.
	// One method to inflate cells the size of the robot
	void InflateObstacle(int i, int j);
	// viewing function
	void ViewNodeDetails(int index1, int index2);
};
