#pragma once

#include<iostream>
#include<utility>
using namespace std;

class GraphNode
{
	int cellWidth, cellHeight; // is 10 cm * 10cm at this point.
public:
	// Node should contain the centroid coordinates
	float xlow, xhigh, zlow, zhigh;
	float xcood, zcood;
	bool isObstacle;
	bool withinLane;
	// default constructor
	GraphNode();
	// constructor with float values
	GraphNode(float x, float z, int w=10,int h=10);
	// to get values about given cell for debugging
	// get details about the current Node
	void getCellParam();
	// tochange into obstacle
	void setObstacle();
	// check if a point is present in the cell;
	bool checkPresence(pair<float,float>&);
	// A bool to check if the node is an obstacle or not
	bool is_Obstacle();

	pair<int, int> getWidthHeight(); // returns width and height of cell in cm

};
