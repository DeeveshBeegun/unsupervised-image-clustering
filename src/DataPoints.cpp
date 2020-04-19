#include <ctime>
#include <iostream>
#include <vector>
#include "DataPoints.h"
#include "Image.h"


using namespace std;

int DataPoints::squaredDistance(DataPoints dataPoints) {
	int distance = 0;
	for(int j = 0; j < 64; j++) {
		distance += (dataPoints.image_point.histogram_bin[j] - image_point.histogram_bin[j]) * (dataPoints.image_point.histogram_bin[j] - image_point.histogram_bin[j]);
	}			
	return distance;
}

DataPoints DataPoints::operator+(DataPoints point) {
	DataPoints dataPoints;
	int* tmp_bin = new int[64];

	for(int j = 0; j < 64; j++) {
		tmp_bin[j] = 0;
	}
	for(int j = 0; j < 64; j++) {
		dataPoints.image_point.histogram_bin= tmp_bin;
	}
	for(int i = 0; i < 64; i++) {
		dataPoints.image_point.histogram_bin[i] = this->image_point.histogram_bin[i] + point.image_point.histogram_bin[i];

	}
	return dataPoints;
}

bool DataPoints::check_if_equal(vector<DataPoints> &prevCentroids, vector<DataPoints> &centroids) {
	int countTrue = 0;
	for(int j = 0; j < 10; j++) {
    for (int i = 0; i < 64; i++) 
        if (prevCentroids[j].image_point.histogram_bin[i] == centroids[j].image_point.histogram_bin[i]) 
            countTrue++;
	}
	prevCentroids.clear();
	if(countTrue == 640) {
		return true;
	}
	return false;
}

DataPoints DataPoints::mean(vector<DataPoints> sumVec, int number_of_points, int cluster_id) {
	DataPoints dataPoints;
	int* tmp_bin = new int[64];

	for(int j = 0; j < 64; j++) {
		tmp_bin[j] = 0;
	}
	for(int j = 0; j < 64; j++) {
		dataPoints.image_point.histogram_bin= tmp_bin;
	}
	for (int i = 0; i < 64; i++) {

	if(number_of_points == 0) {
		dataPoints.image_point.histogram_bin[i] = 0;
	}
	else {
		dataPoints.image_point.histogram_bin[i] = sumVec[cluster_id].image_point.histogram_bin[i]/number_of_points;
	}

	}

	return dataPoints;


}

// int DataPoints::mean_of_cluster(DataPoints dataPoints) {
// 	vector<int> number_of_points;
// 	vector<DataPoints> mean;

// for (int i = 0; i < 64; i++) {
// 	for(auto point = dataPoints.begin(); point != dataPoints.end(); point++) {
// 		DataPoints histogram_point = *point;

// 		int cluster_id = histogram_point.cluster;
// 		number_of_points[cluster_id] += 1;

// 		//sum[cluster_id].image_point.histogram_bin[i] += histogram_point.image_point.histogram_bin[i];

// 	}
// 	//mean[cluster_id].image_point.histogram_bin[i] /= number_of_points[cluster_id]
// }
// //return sum;
// }


// ostream& DataPoints::operator<<(ostream& os, DataPoints dataPoints) {
// 	os << dataPoints.cluster << " " << dataPoints.points.name << endl;
// }
