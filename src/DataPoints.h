#include <vector>
#include <math.h>
#include <iostream>

#ifndef _DATAPOINTS_H
#define _DATAPOINTS_H

struct DataPoints {
	int* points;
	int cluster; // cluster id/name
	double min_distance; // minimum distance between centroid and points
	
	//default constuctor
	DataPoints():cluster(-1), min_distance(INFINITY) {};
	
	// constructor
	DataPoints(int* histogram_points):points(histogram_points), cluster(-1), min_distance(INFINITY) {};
	
	// calculates the square distance between two points(histogram)
	int squaredDistance(DataPoints vector_points);
};

#endif
