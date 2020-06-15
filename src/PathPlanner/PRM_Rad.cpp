#include<cstdlib>
#include<time.h>
#include<math.h>
#include "PRM_Rad.h"

PRM_Rad::PRM_Rad(int numIterations, int zmax, int xmax, int cellWidth, int cellHeight,
	float radius, cood_vector Obstacle_Coordinates):occupancy_grid(xmax,zmax,cellWidth,
		cellHeight,Obstacle_Coordinates), network(),radius_(radius) {
	int z_numNodes = occupancy_grid.DiscretizedGrid.size();
	int x_numNodes = occupancy_grid.DiscretizedGrid[0].size();
	Queue distance_heap;
	GraphNode* current = &occupancy_grid.DiscretizedGrid[0][occupancy_grid.X_num_nodes / 2];
	// add origin to the graph
	network.AddVertex(*current);
	srand(time(0));
	// repeat numIterations times
	for (int iteration = 0; iteration < numIterations; iteration++) {
		// generate a random node
		current = getRandomNode(z_numNodes, x_numNodes);
		// if the current node is not an obstacle
		if (current != NULL) {
			distance_heap = FindDistance(*current);
			// check if the node already exists.
			if (!checkDuplicateNode(distance_heap)) {
				network.AddVertex(*current);
				ConnectNeighbours(distance_heap, *current);
			}
			

		}
	}

}

void PRM_Rad::ConnectNeighbours(Queue& Heap, GraphNode& Point) {
	float distance = Heap.top().first;
	int connectionIndex = Heap.top().second;
	int currentIndex = network.numVertices - 1;
	bool collision = false;
	while (!Heap.empty()) {
		distance = Heap.top().first;
		// check if the distance is more than the radius
		if (distance > radius_) {
			return;
		}
		connectionIndex = Heap.top().second;
		Heap.pop();
		collision = collisionCheck(Point, network.Vertices[connectionIndex]);
		if (!collision) {
			if (Point.zcood <= network.Vertices[connectionIndex].zcood) {
				network.AddEdge(currentIndex, connectionIndex, distance);
			}
			else {
				network.AddEdge(connectionIndex, currentIndex, distance);
			}
		}
	}
}

// function to check if obstacle is present in between two nodes
bool PRM_Rad::collisionCheck(GraphNode& node1, GraphNode& node2) {
	// inputs are two grid nodes. we need to use the Obstacle list in Grid2D object for this. 

	// step 1: create equation of line
	float A = 0, B = 0, C = 0;
	createLineEquation(A, B, C, node1, node2);
	bool collision = false;
	for (int obstacle_number = 0;obstacle_number < occupancy_grid.ObstacleList.size();obstacle_number++) {
		collision = checkDistanceMetric(A, B, C, occupancy_grid.ObstacleList[obstacle_number]);
		if (collision == true) {
			return true;
		}
	}

	return collision;

}

void PRM_Rad::createLineEquation(float& A, float& B, float& C, GraphNode& node1, GraphNode& node2) {
	// line equation is AZ - BX + C = 0
	// where A is x2-x1, B is z2-z1, C is z2x1 - z1x2
	A = node2.xcood - node1.xcood;
	B = node2.zcood - node1.zcood;
	C = (node2.zcood * node1.xcood) + (node1.zcood * node2.xcood);


}

bool PRM_Rad::checkDistanceMetric(float& A, float& B, float& C, Obstacle& square) {
	float D1 = 0, D2 = 0, D3 = 0, D4 = 0;
	D1 = normDistance(A, B, C, square.zmin, square.xmin);
	D2 = normDistance(A, B, C, square.zmin, square.xmax);
	D3 = normDistance(A, B, C, square.zmax, square.xmax);
	D4 = normDistance(A, B, C, square.zmax, square.xmin);
	if ((D1 >= 0 && D2 >= 0 && D3 >= 0 && D4 >= 0) || (D1 <= 0 && D2 <= 0 && D3 <= 0 && D4 <= 0)) {
		return false;
	}
	else {
		return true;
	}

}

float PRM_Rad::normDistance(float& A, float& B, float& C, float& z, float& x) {
	// return the norm distance without the denominator
	return ((A * z) - (B * x) + (C));
}

// Function to pick random Node
GraphNode* PRM_Rad::getRandomNode(int& z_numNodes, int& x_numNodes) {
	// function creates a random node.
	// It checks if the node is an obstacle. 
	// If the node is an obstacle, null pointer is returned.
	// If the node is not an obstacle, pointer to a node is returned.

	GraphNode* node_pointer = NULL;
	int z_index = rand() % z_numNodes;
	int x_index = rand() % x_numNodes;
	if (!occupancy_grid.DiscretizedGrid[z_index][x_index].is_Obstacle()) {
		node_pointer = &occupancy_grid.DiscretizedGrid[z_index][x_index];
	}
	return node_pointer;
}

Queue PRM_Rad::FindDistance(GraphNode& Point) {
	// we will find the distance between each point in the Graph and the reference point and add to minHeap
	Queue Heap;
	float distance;
	for (int vertex = 0; vertex < network.Vertices.size(); vertex++) {
		distance = L2Distance(Point, network.Vertices[vertex]); // calculate L2 distance between ref point and current vertex
		Heap.push(make_pair(distance, vertex));
	}
	return Heap;
}

float PRM_Rad::L2Distance(GraphNode& Node1, GraphNode& Node2) {
	float distance = 0;
	distance += sqrt(pow((Node2.zcood - Node1.zcood), 2) + pow((Node2.xcood - Node1.xcood), 2));
	return distance;
}

bool PRM_Rad::checkDuplicateNode(Queue& Heap) {
	if (Heap.empty()) {
		return false;
	}
	if (Heap.top().first <= 0.000000005) {
		return true;
	}
	return false;
}
