#include "Grid2D.h"
#include<chrono>
typedef pair<float,float> pd;
using namespace std::chrono;


// first is the default constructor
Grid2D::Grid2D() {
	// The function should create a 2D vector of graph Nodes.
	// The size of the graph nodesis currently a 2x3m grid
	// The size of each cell is 10cm. Hence we will require a 30x20 grid (y*x)

	vector<vector<GraphNode>> temp(30);
	float z_cood = -0.05, x_cood = 0; // -0.05 as the first element will become 0.5 in the for loop
	for (int z_index = 0; z_index < 30;z_index++) {
		x_cood = -1.05;
		z_cood += 0.1; // convert coordinate to meters
		for (int x_index = 0; x_index < 20;x_index++) {
			// we have divided by 20,so that we have the coordinate of the centroid
			x_cood += 0.1;
			temp[z_index].push_back(GraphNode(x_cood, z_cood));
		}
	}
	DiscretizedGrid = temp;
	Vehicle_size_x = 20;
	Vehicle_size_z = 20;
	vector<Obstacle> temp1;
	ObstacleList = temp1;
	
}

Grid2D::Grid2D(int xmax, int zmax, int cellWidth, int cellHeight, vector<pd> coordinates) {
	// xmax in meters 
	// zmax in meters
	// cellWidth and cellHeight in cm
	// check default constructor for more details
	
	float z_cood = -(float)cellHeight/200;
	float x_cood = -(float)cellWidth / 200;
	int num_z = (int)((float)zmax / ((float)cellHeight/100));  // number of cells in z
	int num_x = (int)((float)xmax / ((float)cellWidth/100));   // number of cells in x
	X_num_nodes = num_x;
	vector<vector<GraphNode>> temp(num_z);
	for (int z_index = 0; z_index < num_z;z_index++) {
		x_cood = (-(float)cellWidth / 200) - ((float)xmax / 2);  // to shift the axis from -xmax/2 to xmax/2
		z_cood += ((float)(cellHeight) / 100); // convert to meters 
		for (int x_index = 0; x_index < num_x;x_index++) {
			x_cood += ((float)cellWidth / 100);
			temp[z_index].push_back(GraphNode(x_cood, z_cood,cellWidth,cellHeight));
		}
	}
	DiscretizedGrid = temp;
	Vehicle_size_x = 20; // in cm
	Vehicle_size_z = 20;
	vector<Obstacle> temp1;
	ObstacleList = temp1;
	UpdateObstacles(coordinates);
	

}

void Grid2D::ViewNodeDetails(int z_index, int x_index) {
	
	DiscretizedGrid[z_index-1][x_index-1].getCellParam();// convert to 0 based indexing
}

void Grid2D::UpdateObstacles(vector<pd>& coordinates,int i) {
	// we assume the coordinates vector is sorted acoording to our need.
	// we will go through the entire 2Dgrid and assign values
	// when a value is assigned, we will also have to inflate the cell 
	// to the size of the car.

	// coordinates must be z first and then x.
	int cood_ind = 0;  // current coordinate index
	for (int z_index = 0; z_index < DiscretizedGrid.size(); z_index++) {
		for (int x_index = 0; x_index < DiscretizedGrid[z_index].size(); x_index++) {
			// we will check if the coordinate is present in the current cell
			if (DiscretizedGrid[z_index][x_index].checkPresence(coordinates[cood_ind])) {
				cood_ind++;
				DiscretizedGrid[z_index][x_index].setObstacle();
				InflateObstacle(z_index, x_index);
				while (1) {
					// skid through other vertices in this  
					if (cood_ind < coordinates.size()) {
						if (DiscretizedGrid[z_index][x_index].checkPresence(coordinates[cood_ind])) {
							cood_ind++;
						}
						else {
							break;
						}
					}
					else {
						return;
					}
					
				}
			}
		}

	}

}

// Function to set a given node as obstacle in the 2D grid
void Grid2D::UpdateObstacles(vector<pd>& coordinates) {
	// This is an O(m*n^2) naive implementation 
	for (int z_index = 0; z_index < DiscretizedGrid.size(); z_index++) {
		for (int x_index = 0; x_index < DiscretizedGrid[z_index].size(); x_index++) {
			// we will check if the coordinate is present in the current cell
			for (int obstacle = 0;obstacle < coordinates.size();obstacle++) {
				if (DiscretizedGrid[z_index][x_index].checkPresence(coordinates[obstacle])) {
					DiscretizedGrid[z_index][x_index].setObstacle();
					InflateObstacle(z_index, x_index);
				}
			}
		}

	}

}

void Grid2D::InflateObstacle(int z_index, int x_index) {
	// we must make a circle of radius 20cm, i.e 2 grid
	int padding_z = Vehicle_size_z/DiscretizedGrid[z_index][x_index].getWidthHeight().second;
	int padding_x = Vehicle_size_x/DiscretizedGrid[z_index][x_index].getWidthHeight().first;
	Obstacle current;
	
	for (int z = z_index - padding_z; z <= z_index + padding_z;z++) {
		for (int x = x_index - padding_x; x <= x_index + padding_x;x++) {
			if ((x >= 0 && x < DiscretizedGrid[z_index].size()) && (z >= 0 && z < DiscretizedGrid.size())) {
				DiscretizedGrid[z][x].setObstacle();
				current.UpdateCoordinates(DiscretizedGrid[z][x]);
			}
		}
	}

	ObstacleList.push_back(current);
}