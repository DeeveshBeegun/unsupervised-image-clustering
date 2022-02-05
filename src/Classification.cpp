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
CLASSIFICATION::Classification::Classification():number_of_images(0), max_value(0), image_size(0), binSize(0), 
clustersNumber(0), histogram_bin(nullptr) 
 {}

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
		imageFiles.push_back(filename);
		number_of_images++; // increment number of images by 1

	}

	}
	closedir(dir); // close directory

}

// read binary images in the dataset/Gradient_Numbers_PPMS
void CLASSIFICATION::Classification::readImages(const string &image_name, const string &directoryname) {
	
	string path = directoryname + "/" + image_name; // image file path;

	ifstream image_file(path.c_str(), ios::in | ios::binary);
	string header; // ppm file header
	int rows, cols; // rows and columns of images
	
	if(image_file.is_open()) {

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

		image_size = image.size;

		getline(image_file, header);
		max_value = stoi(header); // maximum value of pixels
		image.max_value = max_value;

		image.pixels = new IMAGE::Image::Rgb[rows * cols]; 
		image.greyscaleImage = new int[image.size];

		unsigned char pixel_float[3]; // stores the converted bytes to float

		for(int i = 0; i < image.size; i++) {
			
			image_file.read((char *)pixel_float, 3);

			image.pixels[i].red = pixel_float[0];
			image.pixels[i].green = pixel_float[1];
			image.pixels[i].blue = pixel_float[2];

			image.greyscaleImage[i] = convert_to_greyscale(image.pixels[i].red, image.pixels[i].green, image.pixels[i].blue);

		}
		images.push_back(image); // populate vector images with the greyscale intensities
	

	}

	image_file.close(); // close file

}
	

	 float CLASSIFICATION::Classification::convert_to_greyscale(const float &red, const float &green, const float &blue) const { 
	 	return (0.21*red + 0.72*green + 0.07*blue); 
	 }


	//build histogram for pixels intensities
	void CLASSIFICATION::Classification::build_histogram(const int bin_size, const bool colour, const bool addition) {
		 int maxValue = max_value+1;
		 binSize = bin_size;

		for(int i = 0; i < number_of_images; i ++) {
			images[i].histogram_bin = new int[maxValue/bin_size];
			int histogram_index = 0;
			int histogram[maxValue];
			
			for(int i = 0; i < maxValue; i++) {
				histogram[i] = 0; // fill histogram array with zeros
			}

		if(colour == false && addition == false) {
			for(int j = 0; j < image_size; j++) {
				int index = images[i].greyscaleImage[j]; // find index of pixel intensity in the histogram array
				histogram[index] += 1; // increment appropriate location in the histogram array 
			}
		}
		else if(colour == true && addition == false){

			for(int j = 0; j < image_size; j++) {
			int mean_rgb = (images[i].pixels[j].red + images[i].pixels[j].green + images[i].pixels[j].blue)/3;
			histogram[mean_rgb] += 1;
			}

		}

		else {
		 	histogram == sobel_edgeDetection(histogram, i);

		 }
		

			for(int x = 0; x < (maxValue/bin_size); x++) {
				int value = 0;
				for(int y = histogram_index; y < bin_size + histogram_index; y++) {
					value += histogram[y];
					
				}
			
				images[i].histogram_bin[x] = value;
				histogram_index = histogram_index + bin_size; // increment histogram_index by bin_size

			}
			DataPoints dataPoint(images[i]);
			dataPoint.histogram_binSize = bin_size;
			histogram_points.push_back(dataPoint); // histogram_points size = 100(number of images) historgram_bin size = 64
				
		}

	}

	void CLASSIFICATION::Classification::write_output_toFile(const vector<DataPoints> &histogram_points, const string &output_file) { 
		ofstream file;
		file.open(output_file);
		cout << "Writing output to file..." << endl;
		file << histogram_points;
		file.close(); // close file 
		cout << "Output written to " + output_file << endl;

	}


	void CLASSIFICATION::Classification::kMeansClusterer(const int &number_of_clusters) {
		vector<DataPoints> sumPoints, prevCentroids;

		clustersNumber = number_of_clusters;
		int histogram_binSize = max_value/binSize;

		int* tmp_bin = new int[histogram_binSize];
		for(int i = 0; i < number_of_clusters; i++){
			DataPoints dataPoint;

			for(int j = 0; j < histogram_binSize; j++)
				tmp_bin[j] = 0;

			for(int j = 0; j < histogram_binSize; j++) {
				dataPoint.image_point.histogram_bin= tmp_bin; // initialise histogram_bin with zeros
			}


				prevCentroids.push_back(dataPoint); // initialise prevCentroids with null dataPoints
		}

		DataPoints dataPoint;
		srand(time(0)); // randomize the assignment of random numbers
		 vector<DataPoints> centroids; // stores centroids
		 int index = 0, count = 0;


		 	 while(count != number_of_clusters) {

		 	 int random_number = rand() % imageFiles.size(); // generate random number between 0 to 10
		 	

		  	for(auto point = histogram_points.begin(); point != histogram_points.end(); point++) {
		  		DataPoints dataPoint = *point;
			  	if(imageFiles[random_number] == dataPoint.image_point.name) {
			  		count++;
			  		centroids.push_back(dataPoint); // generate random centroids

			  	}
			  	
		  }
		  imageFiles.erase(imageFiles.begin() + random_number);
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
	for(int i = 0; i < histogram_points.size(); i++) {
		histogram_points[i].number_of_clusters = clustersNumber;
	}

	cout << "output: " << endl << endl;
	cout << histogram_points << endl;

	delete[] tmp_bin;
}

	void CLASSIFICATION::Classification::kMeansClusterer(const int &number_of_clusters, const string &output_file) {
		vector<DataPoints> sumPoints, prevCentroids;

		clustersNumber = number_of_clusters;
		int histogram_binSize = max_value/binSize;

		int* tmp_bin = new int[histogram_binSize];
		for(int i = 0; i < number_of_clusters; i++){
			DataPoints dataPoint;

			for(int j = 0; j < histogram_binSize; j++)
				tmp_bin[j] = 0;

			for(int j = 0; j < histogram_binSize; j++) {
				dataPoint.image_point.histogram_bin= tmp_bin; // initialise histogram_bin with zeros
			}


				prevCentroids.push_back(dataPoint); // initialise prevCentroids with null dataPoints
		}

		DataPoints dataPoint;
		srand(time(0)); // randomize the assignment of random numbers
		 vector<DataPoints> centroids; // stores centroids
		 int index = 0, count = 0;


		 	 while(count != number_of_clusters) {

		 	 int random_number = rand() % imageFiles.size(); // generate random number between 0 to 10
		 	

		  	for(auto point = histogram_points.begin(); point != histogram_points.end(); point++) {
		  		DataPoints dataPoint = *point;
			  	if(imageFiles[random_number] == dataPoint.image_point.name) {
			  		count++;
			  		centroids.push_back(dataPoint); // generate random centroids

			  	}
			  	
		  }
		  imageFiles.erase(imageFiles.begin() + random_number);
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
	for(int i = 0; i < histogram_points.size(); i++) {
		histogram_points[i].number_of_clusters = clustersNumber;
	}

	write_output_toFile(histogram_points, output_file);

	delete[] tmp_bin;

}


 void CLASSIFICATION::Classification::assign_clusterId(const vector<DataPoints> &centroids, vector<DataPoints> &histogram_points) {
 	int count = -1; // id of clusters

	// caculate distance from centroid to data points
	for(auto centroid_point = centroids.begin(); centroid_point != centroids.end(); centroid_point++) {
		count++;
		int cluster_id = count; // cluster id

		for(auto point = histogram_points.begin(); point != histogram_points.end(); point++) {

			 DataPoints dataPoint = *point;
			int distance = dataPoint.squaredDistance(*centroid_point); // calculate squared distance 

			if(distance < dataPoint.min_distance) {
				dataPoint.min_distance = distance;
				dataPoint.cluster = cluster_id;
			
			}

			*point = dataPoint;
		}


	}

 }

 vector<DataPoints> CLASSIFICATION::Classification::sum_of_points(vector<DataPoints> &histogram_points, vector<int> &number_of_points) const{
	vector<DataPoints> sumVec; // sum of all points in a cluster
	int histogram_binSize = max_value/binSize;

	number_of_points.clear();

	int* tmp_bin = new int[histogram_binSize];

	for(int j = 0; j < histogram_binSize; j++) {
		tmp_bin[j] = 0;
	}

	for(int i = 0; i < clustersNumber; i++) {
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
delete[] tmp_bin;
return sumVec;

 }

 int* CLASSIFICATION::Classification::sobel_edgeDetection(int *histogram, const int i) const{
 	int gradient[image_size]; 

			for(int i = 0; i < image_size; i++) {
				gradient[i] = 0;
			}
			for(int j = 0; j < image_size; j++) {
				
				if(j > 4 && j < image_size-4) {
					int gx = 0, gy = 0;
					
					// apply sobel edge detection
					gx = images[i].greyscaleImage[j-1]*2 + images[i].greyscaleImage[j-2] + images[i].greyscaleImage[j-4] 
						- images[i].greyscaleImage[j+1]*2 - images[i].greyscaleImage[j+2] - images[i].greyscaleImage[j+4];


					gy = images[i].greyscaleImage[j-2] + images[i].greyscaleImage[j-3]*2 + images[i].greyscaleImage[j-4] 
									- images[i].greyscaleImage[j+2] - images[i].greyscaleImage[j+3]*2 - images[i].greyscaleImage[j+4];

					gradient[j] = (int)sqrt(gx*gx + gy*gy)%256;

				}

				else {
					gradient[j] = 0;
				}

		}


		for(int j = 0; j < image_size; j++) {
				if(gradient[j] > 1 || gradient[j] == 1) {
					gradient[j] = 1;
						
					}
					else 
						gradient[j] = 0;

			}

			// thinning operator
			vector<int> thinning{0,0,0,1,1,1,1}; // thinning matrix
			vector<int> right_thinning{0,0,0,1,1,1};

		for(int j = 0; j < image_size; j++) {
			if(j > 4 && j < image_size-4) {
				// left_thinning
				vector<int> thinning1Comp{gradient[j-4], gradient[j-3], gradient[j-2], gradient[j], 
					gradient[j+2], gradient[j+3], gradient[j+4]};

				if(thinning == thinning1Comp) {
					gradient[j] = 0;
				}

				// right_thinning
				vector<int> right_thinningComp1{
					gradient[j-2], gradient[j-3], gradient[j+1],
					gradient[j-1], gradient[j], gradient[j+3]
				};

				if(right_thinning == right_thinningComp1) {
					gradient[j] = 0;
				}

				// left_thinning rotated to 90 degrees
				vector<int> thinning2Comp{gradient[j-2], gradient[j+1], gradient[j+4], 
					gradient[j-4], gradient[j-1], gradient[j], gradient[j+2]};

					if(thinning == thinning2Comp) {
						gradient[j] = 0;
					}

				// right_thinning rotated to 90 degrees 
					vector<int> right_thinningComp2{
					gradient[j+1], gradient[j+3], gradient[j+4],
					gradient[j-1], gradient[j-3], gradient[j]
				};

				if(right_thinning == right_thinningComp2) {
					gradient[j] = 0;
				}

				// left_thinning rotated to 90 degrees
				vector<int> thinning3Comp{
					gradient[j+2], gradient[j+3], gradient[j+4],
					gradient[j], gradient[j-2], gradient[j-3], gradient[j-4]
				};

				if(thinning == thinning3Comp) {
					gradient[j] = 0;
				}

				// right thinning rotated to 90 degrees
				vector<int> right_thinningComp3{
					gradient[j-1], gradient[j+2], gradient[j+3],
					gradient[j-3], gradient[j], gradient[j+1]
				};

				if(right_thinning == right_thinningComp3) {
					gradient[j] = 0;
				}

				// left_thinning
				vector<int> thinning4Comp {
					gradient[j+6], gradient[j-1], gradient[j-4],
					gradient[j], gradient[j-2], gradient[j+1], gradient[j+4]
				};

				if(thinning == thinning4Comp) {
					gradient[j] = 0;
				}

				// right thinning
				vector<int> right_thinningComp4{
					gradient[j-1], gradient[j-3], gradient[j-4],
					gradient[j+3], gradient[j], gradient[j+1]
				};

				if(right_thinning == right_thinningComp4) {
					gradient[j] = 0;
				}

				}
				else {
					gradient[j] = 0;
				}

			histogram[gradient[j]] += 1;
		}
		return histogram; // return histogram to be clustered 

}






