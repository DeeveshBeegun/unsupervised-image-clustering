#include <iostream>
#include <string>
#include "Classification.h"
#include <time.h>

int main(int argc, char *argv[]) {
	using namespace std;

	CLASSIFICATION::Classification classification;

	if(argc > 1) {
		string directory_path = argv[1];
		cout << "Reading dataset..." << endl;
		classification.readDataset(directory_path); // read the image files in the directory
	
	}
	if (argc == 2) {
		int bin_size = 1; // default bin size 
		int number_of_clusters = 10; // default number of clusters
		bool colour = false, additional = false; 

		cout << "Building histogram..." << endl;
		classification.build_histogram(bin_size, colour, additional); // build histogram with bin size 1
		cout << "Applying k-means clustering..." << endl << endl;
		classification.kMeansClusterer(number_of_clusters); 
	}

	else if(argc == 3) {

		if((string(argv[2]) == "-colour")) {
			int number_of_clusters = 10, bin_size = 1; // default number of clusters and bin size
			bool additional = false, colour = true;

			cout << "Building histogram..." << endl;
			classification.build_histogram(bin_size, colour, additional);
			cout << "Applying k-means clustering..." << endl << endl;
			classification.kMeansClusterer(number_of_clusters);
		}
		else if((string(argv[2]) == "-additional"))  {
			int number_of_clusters = 10, bin_size = 1; // default number of clusters and bin size
			bool additional = true, colour = false;

			cout << "Building histogram..." << endl;
			classification.build_histogram(bin_size, colour, additional);
			cout << "Applying k-means clustering..." << endl << endl;
			classification.kMeansClusterer(number_of_clusters);
		}

		else {
		cout << "Command not found." << endl;
		cout << "Application can be invoked using the following command: " << endl;
		cout << "./clusterer <dataset> [-o output] [-k n] [-bin b] [-colour] [-additional]" << endl;
		cout << "Where the argument <dataset> must be provided and [-o output] [-k n] [-bin b] [-colour] and [-additional] are optional arguments." << endl;
	}
}
	
	else if (argc == 4) {
		if((string(argv[2]) == "-o")) {
			string output_file = string(argv[3]); // filename
			int number_of_clusters = 10;
			int bin_size = 1; // default number of clusters and bin size
			bool additional = false, colour = false;

			cout << "Building histogram..." << endl;
			classification.build_histogram(bin_size, colour, additional);
			cout << "Applying k-means clustering..." << endl << endl;
			classification.kMeansClusterer(number_of_clusters, output_file); // using overloaded kMenasClusterer method

		}
		else if((string(argv[2]) == "-k")) {
			int number_of_clusters = stoi(string(argv[3])), bin_size = 1; // defualt bin size 
			bool additional = false, colour = false;

			cout << "Building histogram..." << endl;
			classification.build_histogram(bin_size, colour, additional);
			cout << "Applying k-means clustering..." << endl << endl;
			classification.kMeansClusterer(number_of_clusters);

		}
		else if((string(argv[2]) == "-bin")) {
			int number_of_clusters = 10, bin_size = stoi(string(argv[3])); // default number of clusters
			bool additional = false, colour = false;

			cout << "Building histogram..." << endl;
			classification.build_histogram(bin_size, colour, additional);
			cout << "Applying k-means clustering..." << endl << endl;
			classification.kMeansClusterer(number_of_clusters);
		}
		
	}


	else {
		cout << "Command not found." << endl;
		cout << "Application can be invoked using the following command: " << endl;
		cout << "./clusterer <dataset> [-o output] [-k n] [-bin b] [-colour] [-additional]" << endl;
		cout << "Where the argument <dataset> must be provided and [-o output] [-k n] [-bin b] [-colour] and [-additional] are optional arguments." << endl;
	}
}