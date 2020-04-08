#ifndef _HISTOGRAM_H
#define _HISTOGRAM_H

#include "Image.h"

namespace HISTOGRAM {
	struct Histogram {
		int bin_size;
	};

	// build histogram representation
	void build_histogram(const int *pixels_intensities, const IMAGE::Image &image);

}

#endif