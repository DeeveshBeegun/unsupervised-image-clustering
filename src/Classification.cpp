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

using namespace std;

// constructor
CLASSIFICATION::Classification::Classification() {
	vector<IMAGE::Image> images;
	vector<DataPoints> histogram_points;
	int* histogram_bin = nullptr;
	int number_of_images = 0; // number of images in the directory
}

// destructor
CLASSIFICATION::Classification::~Classification() {
	// delete[] pixels_intensities;
	// delete[] histogram_bin;
}

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
			image.pixels[i].green = pixel_float[1];
			image.pixels[i].blue = pixel_float[2];

			image.greyscaleImage[i] = convert_to_greyscale(image.pixels[i].red, image.pixels[i].green, image.pixels[i].blue);

		}
		images.push_back(image); // populate array with the greyscale intensities

		// delete[] image.pixels;
		// delete[] image.greyscaleImage;

	}

	image_file.close();

}
	
	 // converts a rgb image into greyscale image
	 float CLASSIFICATION::Classification::convert_to_greyscale(float red, float green, float blue) { 
	 	return (0.21*red + 0.72*green + 0.07*blue); 
	 }


	//build histogram for pixels intensities
	void CLASSIFICATION::Classification::build_histogram(const int bin_size) {

	// 		for(int i = 0; i < number_of_images; i++) {
	// 		for(int j = 0; j < 1024; j++) {
	// 		cout << images[i].greyscaleImage[j] << " ";
	// 	} 
	// 	cout << " " << endl << endl;
	// }


		int max_value = 256;
		int size = 1024;

		for(int i = 0; i < number_of_images; i ++) {
			images[i].histogram_bin = new int[max_value/bin_size];
			int histogram_index = 0;
			int histogram[max_value];
			
			for(int i = 0; i < max_value; i++) {
				histogram[i] = 0; // fill histogram array with zeros
			}

			for(int j = 0; j < size; j++) {
				int index = images[i].greyscaleImage[j]; // find index of pixel intensity in the histogram array
				histogram[index] += 1; // increment appropriate location in the histogram array 
			}


			for(int x = 0; x < (max_value/bin_size); x++) {
				int value = 0;
				for(int y = histogram_index; y < bin_size + histogram_index; y++) {
					value += histogram[y];
					
				}
			
				images[i].histogram_bin[x] = value;
				histogram_index = histogram_index + bin_size; // increment histogram_index by bin_size

			}

			// 	for(int j = 0; j < 64; j++) {
			// 		cout << images[i].histogram_bin[j] << " ";
			
			// }
			// cout << " " << endl;
			
			
			histogram_points.push_back(DataPoints(images[i])); // histogram_points size = 100(number of images) historgram_bin size = 64
				
		}
		// 	for(int i = 0; i < number_of_images; i++) {
		// for(int j = 0; j < 64; j++) {
		// 	cout << histogram_points[i].image_point.histogram_bin[j] << " ";
		// }
		// cout << " " << endl << endl;

	//}

		kMeansClusterer();

	}

	// write output to file
	void CLASSIFICATION::Classification::write_output(string output_file) { cout << output_file << endl; }

	void CLASSIFICATION::Classification::kMeansClusterer() {
		//srand(time(0));
		 vector<DataPoints> centroids; // stores centroids
		 for(int i = 0; i < 10; i++) {

		 	int random_number = rand() % 100 + 1;

		 	centroids.push_back(histogram_points[random_number]); // generate random centroids

		 }

	 	int count = -1; // id of clusters
	 	
		// caculate distance from centroid to data points
		for(auto centroid_point = centroids.begin(); centroid_point != centroids.end(); centroid_point++) {
			count++;
			int cluster_id = count;

			for(auto histogram_point = histogram_points.begin(); histogram_point != histogram_points.end(); histogram_point++) {

				 DataPoints dataPoint = *histogram_point;
				int distance = dataPoint.squaredDistance(*centroid_point);

				if(distance < dataPoint.min_distance) {
					dataPoint.min_distance = distance;
					dataPoint.cluster = cluster_id;

				}

				*histogram_point = dataPoint;


			}

	}

	//DataPoints dataPoint;
	vector<int> number_of_points;
	vector<DataPoints> sumVec;
	vector<DataPoints> mean;
	int* tmp_bin = new int[64];

	for(int j = 0; j < 64; j++) {
		tmp_bin[j] = 0;
	}

	
	for(int i = 0; i < 10; i++) {
		DataPoints dataPoint;
		number_of_points.push_back(0); // initialise number_of_points vector with zeros
		sumVec.push_back(dataPoint);
			
	}

	for(int j = 0; j < 10; j++) {
		sumVec[j].image_point.histogram_bin = tmp_bin;

	}
	int index = -1;
	for(auto histogram_point = histogram_points.begin(); histogram_point != histogram_points.end(); histogram_point++) {
		DataPoints point = *histogram_point;
		index++;
		int cluster_id = point.cluster;
		if(cluster_id == 5) {
		//cout << "index: " << index << " = " << cluster_id << "| ";
	}

		number_of_points[cluster_id] += 1;

		sumVec[cluster_id] = sumVec[cluster_id] + point;

		mean[cluster_id] = point.mean(sumVec[cluster_id], number_of_points[cluster_id]);
		  
	}

for() {

}

// 	cout << "" << endl << endl;

// 	int indexx = -1;

// 	for(auto points = histogram_points.begin(); points != histogram_points.end(); points++) {
// 		indexx++;
// 				cout << "index: " << indexx << "| ";
// 		for(int i = 0; i < 64; i++) {
// 		DataPoints dataPoint = *points;

// 		cout << dataPoint.image_point.histogram_bin[i] << " ";
// }
// cout << "" << endl << endl;

// }



// for(auto i = sumVec.begin(); i != sumVec.end(); i++) {
// 	DataPoints dataPoint = *i;
// 	for(int j = 0; j < 64; j++) {

// 	cout << dataPoint.image_point.histogram_bin[j] << " ";

// }
// cout << " " << endl << endl;
// }


 }


