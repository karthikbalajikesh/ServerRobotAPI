#pragma once

#include"Graph.h"
#define cood_vector vector<pair<float,float>>

typedef priority_queue<pdi, vector<pdi>, greater<pdi>> Queue;

class PRM_Rad
{
public:
	Graph network;
	Grid2D occupancy_grid;
	float radius_;

	// constructor
	PRM_Rad(int numIterations, int zmax = 3, int xmax = 2, int cellWidth = 10, int cellHeight = 10, float radius = 0.25, cood_vector coordinates = {});
	bool collisionCheck(GraphNode& node1, GraphNode& node2);
	void createLineEquation(float& A, float& B, float& C, GraphNode& node1, GraphNode& node2);
	bool checkDistanceMetric(float& A, float& B, float& C, Obstacle& square);
	float normDistance(float& A, float& B, float& C, float& z, float& x);
	GraphNode* getRandomNode(int&, int&);
	Queue FindDistance(GraphNode& Point);
	float L2Distance(GraphNode& Node1, GraphNode& Node2);
	vector<pid> createConnectivityVector(Queue& distanceHeap, int neighbours);
	bool checkDuplicateNode(Queue& Heap);
	void ConnectNeighbours(Queue& Heap, GraphNode& Point);
};
