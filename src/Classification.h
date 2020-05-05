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
			std::vector<std::string> imageFiles;
			std::unique_ptr<int []> histogram_bin;
			int* tmp_bin;
			int number_of_images, max_value, image_size, binSize, clustersNumber;
	
	
		Classification(); // default constructor
		~Classification(); // destructor

		// reads name of images in the directory
		void readDataset(const std::string &directory_name);

		// reads images in the directory
		void readImages(const std::string &image_names, const std::string &directory_name);

		// converts a rgb image into greyscale image
		float convert_to_greyscale(const float &red, const float &green, const float &blue) const;

		// build histogram representation
		void build_histogram(const int bin_size, const bool colour, const bool addition);

		// write output to file
		void write_output_toFile(const std::vector<DataPoints> &dataPoints, const std::string &output_file);

		// clusters the data into different cluster centroids and output result in terminal
		void kMeansClusterer(const int &number_of_clusters);

		// overloaded method of kMeansClusterer to output results in a file
		void kMeansClusterer(const int &number_of_clusters, const std::string &output_file);

		// clusters point to a specific centroid
		void assign_clusterId(const std::vector<DataPoints> &centroids, std::vector<DataPoints> &histogram_point);

		// calculate sum of points in a particular centroid
		std::vector<DataPoints> sum_of_points(std::vector<DataPoints> &dataPoints, std::vector<int> &number_of_points) const;

		int* sobel_edgeDetection(int *histogram, const int i) const;

	};


}

#endif