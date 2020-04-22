#include <ctime>
#include <iostream>
#include <vector>
#include "DataPoints.h"
#include "Image.h"
#include <string>


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

 ostream& operator<<(ostream& output, const vector<DataPoints> &histogram_points) {

	//printing clusters
	vector<vector<DataPoints> > clusters;
	int id_cluster = -1;

		for(int i = 0; i < 10; i++) {
			id_cluster++;
			vector<DataPoints> cluster;
			for(auto histogram_point = histogram_points.begin(); histogram_point != histogram_points.end(); histogram_point++) {
				DataPoints dataPoints = *histogram_point;
				int cluster_id = dataPoints.cluster;
				
				if(id_cluster == cluster_id) {
					cluster.push_back(dataPoints);
				}
		}

	clusters.push_back(cluster);
	}

	string output_clusters = "";

	for(int i = 0; i < clusters.size(); i++) {
		output_clusters +="cluster " + to_string(i) + ": ";
		for(int j = 0; j < clusters[i].size(); j++) {
			output_clusters += clusters[i][j].image_point.name;
			output_clusters += " ";
		}
		output_clusters += '\n';

	}

	output << output_clusters;

	// printing clusters
		
	return output;
}


