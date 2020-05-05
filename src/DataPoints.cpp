#include <ctime>
#include <iostream>
#include <vector>
#include "DataPoints.h"
#include "Image.h"
#include <string>
#include "Classification.h"


using namespace std;

int DataPoints::squaredDistance(const DataPoints &dataPoints) const {
	int distance = 0, histogram_binSize = ((dataPoints.image_point.max_value+1)/dataPoints.histogram_binSize);

	for(int j = 0; j < histogram_binSize; j++) {
		distance += (dataPoints.image_point.histogram_bin[j] - image_point.histogram_bin[j]) * (dataPoints.image_point.histogram_bin[j] - image_point.histogram_bin[j]);
	}			
	return distance;
}

DataPoints DataPoints::operator+(const DataPoints &point) const {
	DataPoints dataPoints;
	int histogram_binSize = ((point.image_point.max_value+1)/point.histogram_binSize);
	int* tmp_bin = new int[histogram_binSize];

	for(int j = 0; j < histogram_binSize; j++) {
		tmp_bin[j] = 0;
	}
	for(int j = 0; j < histogram_binSize; j++) {
		dataPoints.image_point.histogram_bin= tmp_bin;
	}
	for(int i = 0; i < histogram_binSize; i++) {
		dataPoints.image_point.histogram_bin[i] = this->image_point.histogram_bin[i] + point.image_point.histogram_bin[i];

	}
	return dataPoints;
}

bool DataPoints::check_if_equal(vector<DataPoints> &prevCentroids, const vector<DataPoints> &centroids) const{
	int countTrue = 0, histogram_binSize = 0;

	for(int j = 0; j < centroids.size(); j++) {
		histogram_binSize = (centroids[j].image_point.max_value+1)/centroids[j].histogram_binSize;
    for (int i = 0; i < histogram_binSize; i++) 
        if (prevCentroids[j].image_point.histogram_bin[i] == centroids[j].image_point.histogram_bin[i]) 
            countTrue++;
	}
	prevCentroids.clear(); // clear previous centroid
	if(countTrue == histogram_binSize*centroids.size()) {
		return true;
	}
	return false;
}

DataPoints DataPoints::mean(const vector<DataPoints> &sumVec, const int &number_of_points, const int &cluster_id) const {
	DataPoints dataPoints;
	int histogram_binSize = (dataPoints.image_point.max_value+1)/dataPoints.histogram_binSize;
	int* tmp_bin = new int[histogram_binSize];

	for(int j = 0; j < histogram_binSize; j++) {
		tmp_bin[j] = 0;
	}
	for(int j = 0; j < histogram_binSize; j++) {
		dataPoints.image_point.histogram_bin= tmp_bin;
	}
	for (int i = 0; i < histogram_binSize; i++) {

	if(number_of_points == 0) {
		dataPoints.image_point.histogram_bin[i] = 0;
	}
	else {
		dataPoints.image_point.histogram_bin[i] = sumVec[cluster_id].image_point.histogram_bin[i]/number_of_points;
	}

	}

	return dataPoints;


}

 ostream& operator<<(ostream& output, const vector<DataPoints> &histogram_points){

	//printing clusters
	vector<vector<DataPoints> > clusters;
	int id_cluster = -1;

	int number_of_clusters = histogram_points[0].number_of_clusters;

		for(int i = 0; i < number_of_clusters; i++) {
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


