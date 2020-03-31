#include "Classification.h"
#include <string>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <fstream>

using namespace std;

// constructor
CLASSIFICATION::Classification::Classification() {};

// destructor
CLASSIFICATION::Classification::~Classification() {};



// read content of directory
void CLASSIFICATION::Classification::readDataset(const string directory_name) {
	string line;
	DIR *dir = opendir(directory_name.c_str()); // opens directory
	struct dirent *dp;
	while ((dp = readdir(dir)) != NULL) {
		if(dp -> d_name == "." || dp -> d_name == "..")
			continue;
		cout << "here" << endl;
		readImages(dp->d_name, directory_name);

	}
	closedir(dir);

}

// read binary images in the dataset/Gradient_Numbers_PPMS
void CLASSIFICATION::Classification::readImages(const string image_name, const string directory_name) {
	string line;
	string image = directory_name + "/" + image_name;

        ifstream image_file(image, ios::in | ios::binary | ios::ate);
        if(image_file.is_open()) {
        	while(true) {


           	}
        	image_file.close();
		}
        else 
            cout << "Image file " << image_name << " not found!" << endl;
        

}