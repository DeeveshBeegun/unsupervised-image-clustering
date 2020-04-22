#include "Classification.h"
#include <string>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <fstream>
#include "Image.h"
#include <sstream>
#include <array>
#include <vector>
#include "DataPoints.h"
#include <memory>
#include <time.h>
#include <math.h>
#include <fstream>

using namespace std;

// constructor
CLASSIFICATION::Classification::Classification() {
	vector<IMAGE::Image> images;
	vector<DataPoints> histogram_points;
	int* histogram_bin = nullptr;
	int number_of_images = 0; // number of images in the directory
}

// destructor
CLASSIFICATION::Classification::~Classification() {}

// read content of directory
void CLASSIFICATION::Classification::readDataset(const string &directory_name) {
	string line;
	DIR *dir = opendir(directory_name.c_str()); // opens directory
	struct dirent *dp;
	while ((dp = readdir(dir)) != NULL) {

		string filename = dp->d_name; // name of image file in directory
		if(filename == "." || filename == "..") {
			continue;	
		}
		else {
		readImages(filename, directory_name);
		number_of_images++; // increment number of images by 1

	}

	}
	closedir(dir);

}

// read binary images in the dataset/Gradient_Numbers_PPMS
void CLASSIFICATION::Classification::readImages(const string &image_name, const string &directoryname) {
	
	string path = directoryname + "/" + image_name; // image file path;

	ifstream image_file(path.c_str(), ios::in | ios::binary);
	string header; // ppm file header
	int rows, cols; // rows and columns of images
	
	if(image_file.is_open()) {
		//unique_ptr<IMAGE::Image> image(new IMAGE::Image);

		IMAGE::Image image;

		image.name = image_name;

		getline(image_file, header);
		string magicNumber = header; // "p6" ppm file

		// check if "P6" ppm file
		if(header != "P6")
			cout << "Unrecognised file format." << endl; // not a p6 ppm file

		getline(image_file, header);
		while(header[0] == '#') // skip comments
			getline(image_file, header);
		
		stringstream dimensions; // dimension of image

		dimensions << header;
		dimensions >> rows >> cols; // rows and columns making up the image matrix i.e matrix dimensions.

		image.width = rows; // width of image
		image.height = cols; // height of image

		image.size = rows * cols; // size of image

		getline(image_file, header);
		int max_value = stoi(header); // maximum value of the pixels
		image.max_value = max_value;

		image.pixels = new IMAGE::Image::Rgb[rows * cols]; 

		image.greyscaleImage = new int[image.size];

		unsigned char pixel_float[3]; // stores the converted bytes to float

		for(int i = 0; i < image.size; i++) {
			
			image_file.read((char *)pixel_float, 3);

			image.pixels[i].red = pixel_float[0];
			//cout << "red: " << image.pixels[i].red << endl;
			image.pixels[i].green = pixel_float[1];
			//cout << "green: " << image.pixels[i].green << endl;
			image.pixels[i].blue = pixel_float[2];
			//cout << "blue: " << image.pixels[i].blue << endl;

			image.greyscaleImage[i] = convert_to_greyscale(image.pixels[i].red, image.pixels[i].green, image.pixels[i].blue);
			//cout << "grey: " << image.greyscaleImage[i] << endl;

		}
		images.push_back(image); // populate array with the greyscale intensities

	}

	image_file.close();

}
	
	 // converts a rgb image into greyscale image
	 float CLASSIFICATION::Classification::convert_to_greyscale(float red, float green, float blue) { 
	 	return (0.21*red + 0.72*green + 0.07*blue); 
	 }


	//build histogram for pixels intensities
	void CLASSIFICATION::Classification::build_histogram(const int bin_size, bool colour) {
		int max_value = 256;
		int size = 1024;

		for(int i = 0; i < number_of_images; i ++) {
			images[i].histogram_bin = new int[max_value/bin_size];
			int histogram_index = 0;
			int histogram[max_value];
			
			for(int i = 0; i < max_value; i++) {
				histogram[i] = 0; // fill histogram array with zeros
			}

		if(colour == false) {
			for(int j = 0; j < size; j++) {
				int index = images[i].greyscaleImage[j]; // find index of pixel intensity in the histogram array
				histogram[index] += 1; // increment appropriate location in the histogram array 
			}
		}
		else {
				for(int j = 0; j < size; j++) {

				int red_index = images[i].pixels[j].red;
				histogram[red_index] += 1;

				int green_index = images[i].pixels[j].green;
				histogram[green_index] += 1;

				int blue_index = images[i].pixels[j].blue;
				histogram[blue_index] += 1;

			}

		}


			for(int x = 0; x < (max_value/bin_size); x++) {
				int value = 0;
				for(int y = histogram_index; y < bin_size + histogram_index; y++) {
					value += histogram[y];
					
				}
			
				images[i].histogram_bin[x] = value;
				histogram_index = histogram_index + bin_size; // increment histogram_index by bin_size

			}
			
			histogram_points.push_back(DataPoints(images[i])); // histogram_points size = 100(number of images) historgram_bin size = 64
				
		}

	}


	// write output to file
	void CLASSIFICATION::Classification::write_output_toFile(vector<DataPoints> histogram_points, string output_file) { 
		ofstream file;
		file.open(output_file);
		file << histogram_points;
		cout << "Writing output to file..." << endl;
		file.close();
		cout << "Output written to " + output_file << endl;

	}

	void CLASSIFICATION::Classification::kMeansClusterer() {
		vector<DataPoints> sumPoints;
		vector<DataPoints> prevCentroids;

		int* tmp_bin = new int[64];
		for(int i = 0; i < 10; i++){
			DataPoints dataPoint;

			for(int j = 0; j < 64; j++)
				tmp_bin[j] = 0;

			for(int j = 0; j < 64; j++) {
				dataPoint.image_point.histogram_bin= tmp_bin;
			}

				prevCentroids.push_back(dataPoint);
		}

		DataPoints dataPoint;

		srand(time(0)); // randomize the assignment of random numbers
		 vector<DataPoints> centroids; // stores centroids
		 for(int i = 0; i < 10; i++) {
		 	int random_number = rand() % 100; // generate random number between 0 to 99
	 		centroids.push_back(histogram_points[random_number]); // generate random centroids

		 }

		assign_clusterId(centroids, histogram_points); // assign cluster_id to points

	int times = 0;
	bool mean_not_same = true;
	while(mean_not_same) {
		vector<int> number_of_points; // number of points in a specific cluster
		sumPoints = sum_of_points(histogram_points, number_of_points);
		int count = -1;

		if (dataPoint.check_if_equal(prevCentroids, centroids) == true) {
			mean_not_same = false;
		}
		
		for(auto centroid_point = centroids.begin(); centroid_point != centroids.end(); centroid_point++) {
			DataPoints dataPoint = *centroid_point;
			count++;
			int cluster_id = count;
			prevCentroids.push_back(dataPoint);

			*centroid_point = dataPoint.mean(sumPoints, number_of_points[cluster_id], cluster_id);

		}

		assign_clusterId(centroids, histogram_points);
	
	} 

	cout << histogram_points << endl;


}
// 	void CLASSIFICATION::Classification::kMeansClusterer(int number_of_clusters, string output_file) {
// 		vector<DataPoints> sumPoints;
// 		vector<DataPoints> prevCentroids;

// 		int* tmp_bin = new int[64];
// 		for(int i = 0; i < 10; i++){
// 			DataPoints dataPoint;

// 			for(int j = 0; j < 64; j++)
// 				tmp_bin[j] = 0;

// 			for(int j = 0; j < 64; j++) {
// 				dataPoint.image_point.histogram_bin= tmp_bin;
// 			}

// 				prevCentroids.push_back(dataPoint);
// 		}

// 		DataPoints dataPoint;

// 		srand(time(0)); // randomize the assignment of random numbers
// 		 vector<DataPoints> centroids; // stores centroids
// 		 for(int i = 0; i < 10; i++) {
// 		 	int random_number = rand() % 100; // generate random number between 0 to 99
// 	 		centroids.push_back(histogram_points[random_number]); // generate random centroids

// 		 }

// 		assign_clusterId(centroids, histogram_points); // assign cluster_id to points

// 	int times = 0;
// 	bool mean_not_same = true;
// 	while(mean_not_same) {
// 		vector<int> number_of_points; // number of points in a specific cluster
// 		sumPoints = sum_of_points(histogram_points, number_of_points);
// 		int count = -1;

// 		if (dataPoint.check_if_equal(prevCentroids, centroids) == true) {
// 			mean_not_same = false;
// 		}
		
// 		for(auto centroid_point = centroids.begin(); centroid_point != centroids.end(); centroid_point++) {
// 			DataPoints dataPoint = *centroid_point;
// 			count++;
// 			int cluster_id = count;
// 			prevCentroids.push_back(dataPoint);

// 			*centroid_point = dataPoint.mean(sumPoints, number_of_points[cluster_id], cluster_id);

// 		}

// 		assign_clusterId(centroids, histogram_points);
	
// 	} 

// 	cout << histogram_points << endl;


// }

 void CLASSIFICATION::Classification::assign_clusterId(vector<DataPoints> &centroids, vector<DataPoints> &histogram_points) {
 	int count = -1; // id of clusters

	// caculate distance from centroid to data points
	for(auto centroid_point = centroids.begin(); centroid_point != centroids.end(); centroid_point++) {
		count++;
		int cluster_id = count;

		for(auto point = histogram_points.begin(); point != histogram_points.end(); point++) {

			 DataPoints dataPoint = *point;
			int distance = dataPoint.squaredDistance(*centroid_point);

			if(distance < dataPoint.min_distance) {
				dataPoint.min_distance = distance;
				dataPoint.cluster = cluster_id;
			
			}

			*point = dataPoint;


		}

	}

 }

 vector<DataPoints> CLASSIFICATION::Classification::sum_of_points(vector<DataPoints> &histogram_points, vector<int> &number_of_points) {
	vector<DataPoints> sumVec; // sum of all points in a cluster
	number_of_points.clear();

	int* tmp_bin = new int[64];

	for(int j = 0; j < 64; j++) {
		tmp_bin[j] = 0;
	}

	for(int i = 0; i < 10; i++) {
		DataPoints dataPoint;
		number_of_points.push_back(0); // initialise number_of_points vector with zeros
		sumVec.push_back(dataPoint);
		sumVec[i].image_point.histogram_bin = tmp_bin;

	}

	int count = -1;
	for(auto histogram_point = histogram_points.begin(); histogram_point != histogram_points.end(); histogram_point++) {
		DataPoints point = *histogram_point;
		count++;
		int cluster_id = point.cluster;

		number_of_points[cluster_id] += 1;
		sumVec[cluster_id] = sumVec[cluster_id] + point;

		histogram_point -> min_distance = INFINITY; // reset the distance of the points to infinity

	
}
return sumVec;

 }

 void CLASSIFICATION::Classification::printVector(vector<DataPoints> dataPoints) {
	int count = -1;
	 	for(auto points = dataPoints.begin(); points != dataPoints.end(); points++) {
	 		count ++;
	 		cout << count << ": ";
	 		 for(int i = 0; i < 64; i++) {
	 		DataPoints dataPoints = *points;
	 		cout << dataPoints.image_point.histogram_bin[i] << " ";
	 	}
	 	cout << "" << endl;
	 }
 }


