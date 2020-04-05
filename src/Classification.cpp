#include "Classification.h"
#include <string>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <fstream>
#include "Image.h"
#include <sstream>

using namespace std;

// constructor
CLASSIFICATION::Classification::Classification() {};

// destructor
CLASSIFICATION::Classification::~Classification() {};

// read content of directory
void CLASSIFICATION::Classification::readDataset(const string &directory_name) {
	string line;
	DIR *dir = opendir(directory_name.c_str()); // opens directory
	struct dirent *dp;
	while ((dp = readdir(dir)) != NULL) {

		string filename = dp->d_name;
		if(filename == "." || filename == "..") {
			continue;	
		}
		else {
		readImages(filename, directory_name);
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


		IMAGE::Image image;

		image.width = rows; // width of image
		image.height = cols; // height of image

		image.size = rows * cols; // size of image

		getline(image_file, header);
		//int max_value = stoi(header); // maximum value of the pixels

		image.pixels = new IMAGE::Image::Rgb[rows * cols]; 

		unsigned char pixel_float[3]; // stores the converted bytes to float

		for(int i = 0; i < image.size; i++) {
			
			image_file.read((char *)pixel_float, 3);

			image.pixels[i].red = pixel_float[0] / 255.f;
			image.pixels[i].green = pixel_float[1] / 255.f;
			image.pixels[i].blue = pixel_float[2] / 255.f;

		}

		image_file.close();
 
	}

}
