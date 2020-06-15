#include "Graph.h"

Graph::Graph():Adjacency_list(), Reverse_list(), numVertices(0),Vertices(0) {
	// Initialize an empty adjacency list 
	// later maybe can use a heap

	
}

void Graph::AddEdge(int source, int dest, float weight) {

	// add the edge as the form index, weight to the corresponding source and dest
	Adjacency_list[source].push_back(make_pair(dest, weight));
	Reverse_list[dest].push_back(make_pair(source, weight));
}

void Graph::AddVertex(GraphNode& Node) {
	Vertices.push_back(Node);
	Adjacency_list.push_back({});
	Reverse_list.push_back({});
	numVertices++;
}

void Graph::RemoveLastVertex() {
	Vertices.erase(Vertices.end() - 1);
	Adjacency_list.erase(Adjacency_list.end()-1);
	Reverse_list.erase(Reverse_list.end()-1);
	numVertices--;
}

