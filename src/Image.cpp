#include <cstdlib>
#include <cstdio>
#include "Image.h"
#include <iostream>
using namespace std;
// default constructor
IMAGE::Image::Image(): width(0), height(0), pixels(nullptr) {}

//constructor: create an image with width, height
IMAGE::Image::Image(const unsigned int &rows, const unsigned int &cols): width(rows), height(cols), pixels(nullptr) {
	pixels = new Rgb[width * height];
	for(int i = 0; i < width * height; i++) 
		pixels[i] = Rgb(0); // assigns pixels with all 0s
}

// destructor
IMAGE::Image::~Image() {
	if(pixels != NULL) 
		delete [] pixels;
}

// overloads the [] operator
const IMAGE::Image::Rgb &IMAGE::Image::operator [] (const unsigned int &i) {
	return pixels[i];
}
