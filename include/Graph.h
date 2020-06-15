#pragma once

#include"Grid2D.h"


typedef pair<int, float> pid;
typedef pair<float,int> pdi;
class Graph
{
public:
	vector<GraphNode> Vertices;
	vector<vector<pid>> Adjacency_list;
	vector<vector<pid>> Reverse_list;
	int numVertices;

	// Default Constructor
	Graph();
	// Add Edge to the Graph
	void AddEdge(int source, int dest, float weight);
	void AddVertex(GraphNode& Node);
	void RemoveLastVertex();

};
