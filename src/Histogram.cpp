#include "Histogram.h"
#include "Image.h"
#include <iostream>

using namespace std;

	// build histogram for pixels intensities
	void HISTOGRAM::build_histogram(const int *pixels_intensities, const IMAGE::Image &image) {
		
		int histogram[image.size+1];

		// fill histogram array with zeros
		for(int i = 0; i < image.max_value+1; i++) {
			histogram[i] = 0;
			//cout << i << endl;
		}

		for(int i = 0; i < image.size; i++) {
			int index = pixels_intensities[i]; // find index of pixel intensity in the histogram array
			histogram[index] += 1; // increment appropriate location in the histogram array 
		}

		for(int i = 0; i < image.max_value+1; i++) {
			cout << histogram[i] << " ";
		}

	}

