/**
* Classification header file
*/

#include <string>
#include <vector>
#include "Image.h"
#include "DataPoints.h"
#include <memory>

#ifndef _CLASSIFICATION_H
#define _CLASSIFICATION_H

namespace CLASSIFICATION {		
	
	class Classification {
		
		// public members
		public: 
			std::vector<IMAGE::Image> images;
			std::vector<DataPoints> histogram_points;
			int* histogram_bin;
			int number_of_images = 0;
	
		Classification(); // default constructor
		~Classification(); // destructor

		// reads name of images in the directory
		void readDataset(const std::string &directory_name);

		// reads images in the directory
		void readImages(const std::string &image_names, const std::string &directory_name);

		// converts a rgb image into greyscale image
		float convert_to_greyscale(float red, float green, float blue);

		// build histogram representation
		void build_histogram(const int bin_size);

		// write output to file
		void write_output(std::string output_file);

		// clusters the data into different cluster centroids
		void kMeansClusterer();


	};


}

#endif