#include <vector>
#include <math.h>
#include <iostream>
#include "Image.h"

#ifndef _DATAPOINTS_H
#define _DATAPOINTS_H

struct DataPoints {
	IMAGE::Image points;
	int cluster; // cluster id/name
	double min_distance; // minimum distance between centroid and points
	
	//default constuctor
	DataPoints():cluster(-1), min_distance(INFINITY) {};
	
	// constructor
	DataPoints(IMAGE::Image histogram_points):points(histogram_points), cluster(-1), min_distance(INFINITY) {};
	
	// calculates the square distance between two points(histogram)
	int squaredDistance(DataPoints vector_points);

	// friend ostream& operator<<(ostream& os, DataPoints dataPoints);
};

#endif
