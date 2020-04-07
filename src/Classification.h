/**
* Classification header file
*/

#include <string>
#include <vector>
#include "Image.h"

#ifndef _CLASSIFICATION_H
#define _CLASSIFICATION_H

namespace CLASSIFICATION {

	class Classification {
	
	//private members
		

	// public members
	public:
		Classification(); // default constructor
		~Classification(); // destructor


		// reads name of images in the directory
		void readDataset(const std::string &directory_name);

		// reads images in the directory
		void readImages(const std::string &image_names, const std::string &directory_name);

		// converts a rgb image into greyscale image
		float convert_to_greyscale(float red, float green, float blue);

		// build histogram representation
		void build_histogram(const int *pixels_intensities, const IMAGE::Image &image);



	};

}

#endif