#pragma once

#include "PRM_Rad.h"
class DijkstraPRM :
	public PRM_Rad
{
	vector<GraphNode> Pathway;
public:
	float PathDistance;
	int width, height;
	// constructor
	DijkstraPRM(pair<float, float> destination, int numIterations = 100, int zmax = 1, int xmax = 2,
		int cellWidth = 10, int CellHeight = 10, float radius = 0.25, cood_vector coordinates = {});
	void addDestination(pair<float, float>& dest);
	vector<GraphNode> shortestPath(); // will get the shortest path between node 0 and last node
	void relaxNode(Queue& minHeap, int& currentIndex, float& currentDistnce,
		vector<float>& distance_from_Source, vector<int>& previousNode);
	vector<GraphNode> retrievePath(vector<int>& previoius);
	// function to print the node coordinates of the path
	void PrintPathDetails();
};
