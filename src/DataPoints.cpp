#include <ctime>
#include <iostream>
#include <vector>
#include "DataPoints.h"
#include "Image.h"


using namespace std;

int DataPoints::squaredDistance(DataPoints dataPoints) {
	int distance = 0;
	for(int j = 0; j < 64; j++) {
		distance += (dataPoints.points.histogram_bin[j] - points.histogram_bin[j]) * (dataPoints.points.histogram_bin[j] - points.histogram_bin[j]);
	}			
	return distance;
}

// ostream& DataPoints::operator<<(ostream& os, DataPoints dataPoints) {
// 	os << dataPoints.cluster << " " << dataPoints.points.name << endl;
// }
