/**
* Image header file
*/
#ifndef _IMAGE_H
#define _IMAGE_H

namespace IMAGE {
	class Image {
	public: // public members

	int width, height; // dimension of image
	int size, max_value;

	// default constructor
	Image(); // creates an empty image

	// constructor
	Image(const unsigned int &rows, const unsigned int &cols);

	// destructor
	~Image();

	struct Rgb {
		float red, green, blue;

		// creates an image of diffrent rgb values depending on the rgb value
		Rgb(float r, float g, float b): red(r), green(g), blue(b) {};

		// creates an image of a single colour e.g 1 for white and 0 for black
		Rgb(float colour): red(colour), green(colour), blue(colour)  {}

		// creates an empty image
		Rgb(): red(0), green(0), blue(0) {}


		Rgb &operator *= (const Rgb &rgb) {
		red *= rgb.red;
		green *= rgb.green;
		blue *= rgb.blue;
		return *this;
	}

 	};

 	const Rgb &operator [] (const unsigned int &i);

 	Rgb *pixels;

	}; 

} // namespace _IMAGE_H

#endif
