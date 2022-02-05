---------------------------------------------------------------------------------------------------------------------------
						Unsupervised Image Clustering
---------------------------------------------------------------------------------------------------------------------------
Date: 06/05/2020
Student Number: BGNDEE001

Description:
Using a simple unsupervised classification scheme - K-means clustering - to classify images into different categoties/types.

Driver file: Clusterer.cpp
Classifcation(k-means clustering): Classification.cpp, (header) Classification.h
Images: Image.cpp, (header) Image.h
Data points: DataPoints.cpp, (header) DataPoints.h


File functionality:
- Clusterer.cpp: The driver file; takes command line from user.
- Classification.cpp: read datasets, reads images and convert to greyscale, build histogram, assign cluster id to dataPoints, performs k means clustering and perform sobel edge detection and thinning.
- Images.cpp: contains the image size, the pixles, name, width and height of the image.
- DataPoints.cpp: represent a point which is a histogram.


Makefile includes:
- a compile run that compiles and links the project (default)
- a clean rule that removes both the object code(.o) files and the "driver" executable

Run instructions:
- open terminal
- navigate to the directory "unsupervised_image_clutering" and run the command "make"
- input the following command:

	./clusterer <dataset> [-o output] [-k n] [-bin b] [-colour] [-additional]

Where the argument <dataset> must be provided and [-o output] [-k n] [-bin b] [-colour] and [-additional] are optional arguments.

More Complex feature:
ref: https://en.wikipedia.org/wiki/Sobel_operator
https://homepages.inf.ed.ac.uk/rbf/HIPR2/thin.htm

In this part i used the sobel edge detection operator. This algorithm helps to extract the edges 
from the images. However, after extraction the images contain thick edges with a lot of pixels, thus
the thinning algorithm is used to convert the pixles into a single pixel.
