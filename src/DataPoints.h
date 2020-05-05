#include <vector>
#include <math.h>
#include <iostream>
#include "Image.h"

#ifndef _DATAPOINTS_H
#define _DATAPOINTS_H

class DataPoints {
public:
	IMAGE::Image image_point;
	double min_distance; // minimum distance between centroid and points
	int histogram_binSize, cluster;
	int number_of_clusters = 0;
	
	//default constuctor
	DataPoints():image_point(), cluster(-1), min_distance(INFINITY) {};
	
	// constructor
	DataPoints(IMAGE::Image histogram_points):image_point(histogram_points), cluster(-1), min_distance(INFINITY) {};
	
	// calculates the square distance between two points (histograms)
	int squaredDistance(const DataPoints &dataPoints) const;

	// overload the + operator to add two DataPoints object
	DataPoints operator+(const DataPoints &point) const;

	// mean of the sum of points in a cluster
	DataPoints mean(const std::vector<DataPoints> &sumVec, const int &number_of_points, const int &cluster_id) const;

	bool check_if_equal(std::vector<DataPoints> &prevCentroids, const std::vector<DataPoints> &centroids) const;

	// output to terminal 
	friend std::ostream& operator<<(std::ostream& os, const std::vector<DataPoints> &dataPoints);
};


#endif
