#include<cstdlib>
#include<time.h>
#include<math.h>
#include "PRM.h"

PRM::PRM(int numIterations, int zmax, int xmax, int cellWidth, int cellHeight,  int neighbours, cood_vector coordinates):
	occupancy_grid(xmax, zmax, cellWidth, cellHeight, coordinates), network() {
	// extract the size of the occupancy grid
	int z_numNodes = occupancy_grid.DiscretizedGrid.size();
	int x_numNodes = occupancy_grid.DiscretizedGrid[0].size();
	Queue distance_Heap;
	bool collision;
	GraphNode* current = &occupancy_grid.DiscretizedGrid[0][occupancy_grid.X_num_nodes/2];
	// add the origin into the graph as we will always plan from the origin.
	
	network.AddVertex(*current);
	vector<pid> Connectivity_vector(neighbours);
	srand(time(0));
	// repeat n times
	for (int iteration = 0; iteration < numIterations; iteration++) {
		// generate a random Node
		current = getRandomNode(z_numNodes, x_numNodes);
		// if the generated node is not an obstacle
		if (current != NULL) {
			// step 1 is to check the distance values of all the other nodes in the graph.
			distance_Heap = FindDistance(*current);
			// step 2 is to pick the first N(neighbours) values of the distance array. 
			Connectivity_vector = createConnectivityVector(distance_Heap,neighbours);
			// add vertex to the graph
			if (checkDuplicateNode(distance_Heap)) {
				continue;
			}
			network.AddVertex(*current);
			// for every Neighbour
			for (int neighbour = 0; neighbour < neighbours; neighbour++) {
				
				// Do collision check of the first N Neighbours edges
				if (Connectivity_vector[neighbour].first != -1){
					collision = collisionCheck(*current, network.Vertices[Connectivity_vector[neighbour].first]);
					// Create an appropriate edge in the Adjacency graph.
					if (!collision) {
						if (current->zcood <= network.Vertices[Connectivity_vector[neighbour].first].zcood) {
							network.AddEdge((network.numVertices) - 1, Connectivity_vector[neighbour].first, Connectivity_vector[neighbour].second);
						}
						else {
							network.AddEdge( Connectivity_vector[neighbour].first, (network.numVertices) - 1, Connectivity_vector[neighbour].second);
						}
					}
				}
				else {
					break;
				}
			}
			

		}
	}

	
}

// function to check if obstacle is present in between two nodes
bool PRM::collisionCheck(GraphNode& node1, GraphNode& node2) {
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

void PRM::createLineEquation(float& A, float& B, float& C, GraphNode& node1, GraphNode& node2) {
	// line equation is AZ - BX + C = 0
	// where A is x2-x1, B is z2-z1, C is z2x1 - z1x2
	A = node2.xcood - node1.xcood;
	B = node2.zcood - node1.zcood;
	C = (node2.zcood * node1.xcood) + (node1.zcood * node2.xcood);


}

bool PRM::checkDistanceMetric(float& A, float& B, float& C, Obstacle& square) {
	float D1 = 0, D2 = 0, D3 = 0, D4 = 0;
	D1 = normDistance(A, B, C, square.zmin, square.xmin);
	D2 = normDistance(A, B, C, square.zmin, square.xmax);
	D3 = normDistance(A, B, C, square.zmax, square.xmax);
	D4 = normDistance(A, B, C, square.zmax, square.xmin);
	if ((D1 >= 0 && D2 >= 0 && D3 >= 0 && D4 >= 0)|| (D1 <= 0 && D2 <= 0 && D3 <= 0 && D4 <= 0)) {
		return false;
	}
	else {
		return true;
	}
	
}

float PRM::normDistance(float& A, float& B, float& C, float& z, float& x) {
	// return the norm distance without the denominator
	return ((A*z)-(B*x)+(C));
}

// Function to pick random Node
GraphNode* PRM::getRandomNode(int& z_numNodes, int& x_numNodes) {
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

Queue PRM::FindDistance(GraphNode& Point) {
	// we will find the distance between each point in the Graph and the reference point and add to minHeap
	Queue Heap;
	float distance;
	for (int vertex = 0; vertex < network.Vertices.size(); vertex++) {
		distance = L2Distance(Point, network.Vertices[vertex]); // calculate L2 distance between ref point and current vertex
		Heap.push(make_pair(distance, vertex));
	}
	return Heap;
}

float PRM::L2Distance(GraphNode& Node1, GraphNode& Node2) {
	float distance = 0;
	distance += sqrt(pow((Node2.zcood - Node1.zcood), 2) + pow((Node2.xcood - Node1.xcood), 2));
	return distance;
}

vector<pid> PRM::createConnectivityVector(Queue& distanceHeap, int neighbours) {
	// will create a vector of indices to connect.
	vector<pid> ConnectivityVector(neighbours, { -1,-1 });
	int temp_index = 0; // this will increase in the while loop
	int index = 0;
	float distance = 0;
	while (temp_index < neighbours && !distanceHeap.empty()) {
		distance = distanceHeap.top().first;
		index = distanceHeap.top().second;
		distanceHeap.pop();
		ConnectivityVector[temp_index] = make_pair(index, distance);
		temp_index++;
	}
	return ConnectivityVector;

}

// This is to check if the current node already exists in the graph.
bool PRM::checkDuplicateNode(Queue& Heap) {
	if (Heap.empty()) {
		return false;
	}
	if (Heap.top().first <= 0.000000005) {
		return true;
	}
	return false;
}
	