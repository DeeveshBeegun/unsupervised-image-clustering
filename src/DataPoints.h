#include <vector>
#include <math.h>
#include <iostream>
#include "Image.h"

#ifndef _DATAPOINTS_H
#define _DATAPOINTS_H

struct DataPoints {
	IMAGE::Image image_point;
	int cluster; // cluster id/name
	double min_distance; // minimum distance between centroid and points
	
	//default constuctor
	DataPoints():image_point(), cluster(-1), min_distance(INFINITY) {};
	
	// constructor
	DataPoints(IMAGE::Image histogram_points):image_point(histogram_points), cluster(-1), min_distance(INFINITY) {};
	
	// calculates the square distance between two points(histogram)
	int squaredDistance(DataPoints vector_points);

	// calculates the sum of all the histogram_bin in the cluster
	DataPoints sum(std::vector<DataPoints> histogram_points, int cluster_id);

	// overload the + operator to add two DataPoints object
	DataPoints operator+(DataPoints point);

	// overload the / operator to calculate the mean of the clusters
	DataPoints operator/(DataPoints point);

	// // calculates the mean of points near the cluster
	// int  mean_of_cluster(std::vector<DataPoints> dataPoints);

	// friend ostream& operator<<(ostream& os, DataPoints dataPoints);
};

#endif
