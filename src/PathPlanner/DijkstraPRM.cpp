#include "DijkstraPRM.h"

DijkstraPRM::DijkstraPRM(pair<float, float> destination, int numIterations, int zmax, int xmax, int cellWidth, int cellHeight, float radius, cood_vector coordinates) :
	PRM_Rad(numIterations, zmax, xmax, cellWidth, cellHeight, radius, coordinates), width(cellWidth), height(cellHeight) {
	// add the destination onto the roadmap
	addDestination(destination);
	vector<GraphNode> path = shortestPath();
	Pathway = path;
}

void DijkstraPRM::addDestination(pair<float, float>& dest) {
	// we need to get a minHeap structure of nodes.
	Queue distance_heap;
	GraphNode Destination(dest.second, dest.first, width, height); //bcoz constructor of graphnode needs (x,z)
	GraphNode* temp = NULL;
	network.AddVertex(Destination);
	int nodeIndex = 0;
	float weight = 0;
	distance_heap = FindDistance(Destination);
	int connections = 0;
	while ((!distance_heap.empty()) && connections < 4) {
		nodeIndex = distance_heap.top().second;
		weight = distance_heap.top().first;
		distance_heap.pop();
		// store the address of the closest node in a pointer
		temp = &network.Vertices[nodeIndex];
		// check if the closest node is below or equal in z axis from destination
		if (temp->zcood <= Destination.zcood) {
			bool collision = collisionCheck(Destination, *temp);
			if (!collision) {
				network.AddEdge(nodeIndex, (network.numVertices) - 1, weight);
				connections++;
			}
		}

	}
}

vector<GraphNode> DijkstraPRM::shortestPath() {
	vector<GraphNode> path;
	vector<int> previousNode(network.numVertices, -1);
	vector<float> distance_from_source(network.numVertices, INT8_MAX);
	// create the minHeap Data Structure
	Queue minHeap;
	int currentIndex = 0, destinationIndex = network.numVertices - 1;
	float currentDistance = 0;
	// add the source into the minHeap
	minHeap.push(make_pair(0, 0));
	while (!minHeap.empty()) {
		currentDistance = minHeap.top().first;
		currentIndex = minHeap.top().second;
		minHeap.pop();
		if (currentIndex == destinationIndex) {
			break;
		}
		else {
			relaxNode(minHeap, currentIndex, currentDistance, distance_from_source, previousNode);
		}
	}
	PathDistance = distance_from_source[network.numVertices - 1];
	path = retrievePath(previousNode);

	return path;
}

void DijkstraPRM::relaxNode(Queue& minHeap, int& currentIndex, float& currentDistance,
	vector<float>& distance_from_Source, vector<int>& previousNode) {
	int numEdges = network.Adjacency_list[currentIndex].size();
	int visitedIndex = 0;
	float newLength = 0;
	for (int edge = 0; edge < numEdges; edge++) {
		// check if a smaller distance is present for a node. If so, add to the heap
		visitedIndex = network.Adjacency_list[currentIndex][edge].first;
		newLength = currentDistance + network.Adjacency_list[currentIndex][edge].second;
		if (newLength < distance_from_Source[visitedIndex]) {
			distance_from_Source[visitedIndex] = newLength;
			previousNode[visitedIndex] = currentIndex;
			// Add to the heap
			minHeap.push(make_pair(distance_from_Source[visitedIndex], visitedIndex));
		}

	}
}

vector<GraphNode> DijkstraPRM::retrievePath(vector<int>& previousNode) {
	vector<GraphNode> Path;
	// backtrack from the last index
	int currentIndex = network.numVertices - 1;

	while (previousNode[currentIndex] != -1) {
		Path.push_back(network.Vertices[currentIndex]);
		currentIndex = previousNode[currentIndex];
	}
	Path.push_back(network.Vertices[0]); //add source to path

	return Path;
}

void DijkstraPRM::PrintPathDetails() {
	cout << "\n The Path to the destination  ( " <<
		network.Vertices[network.numVertices - 1].zcood << "  ,  " <<
		network.Vertices[network.numVertices - 1].xcood << "  ) is :" << endl;
	for (int node = 0; node < Pathway.size();node++) {
		cout << " ( " << Pathway[node].zcood << " , " << Pathway[node].xcood << " )" << endl;
	}
	cout << "Distance to the destination is " << PathDistance << endl;
}

vector<pair<float,float>> DijkstraPRM::GetPathVector(){
	vector<pair<float,float>> Coordinates(Pathway.size(),
									std::make_pair(0,0));
	int index = 0;
	for(auto node:Pathway){
		Coordinates[index].first = node.zcood;
		Coordinates[index].second = node.xcood;
		index+=1;
	}

	return Coordinates;
}
