#include <ctime>
#include <iostream>
#include <vector>
#include "DataPoints.h"


using namespace std;

int DataPoints::squaredDistance(DataPoints dataPoints) {
	int distance = 0;
		for(int i = 0; i < 64; i ++) {
			distance += (dataPoints.points[i] - points[i]) * (dataPoints.points[i] - points[i]);
		}
		return distance;
}
