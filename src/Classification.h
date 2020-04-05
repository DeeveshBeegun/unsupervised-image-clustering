/**
* Classification header file
*/

#include <string>
#include <vector>

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
		void readDataset(const std::string directory_name);

		// reads images in the directory
		void readImages(const std::string &image_names, const std::string &directory_name);



	};

}

#endif