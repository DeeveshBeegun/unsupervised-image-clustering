#include <iostream>
#include <string>
#include "Classification.h"


int main(int argc, char *argv[]) {
	using namespace std;

	//string directory_path = "./Gradient_Numbers_PPMS";
	CLASSIFICATION::Classification classification;

	// clusterer <dataset> [-o output]
	// clusterer <dataset> [-o output][-k n]
	// clusterer <dataset> [-k n]
	// clusterer <dataset> [-o output][-k n][-bin b]
	// clusterer <dataset> [-o output][-bin b]
	// clusterer <dataset> [-bin b]
	if(argc > 1) {
		string directory_path = argv[1];
		cout << "Reading dataset..." << endl;
		classification.readDataset(directory_path); // read the image files in the directory
	
	}
 if(argc == 4 && (string(argv[2]) == "-bin")) {
	//int bin_size = 1; // default bin size 
		 int bin_size = stoi(string(argv[3]));
		 classification.build_histogram(bin_size);

	}
	else if (argc == 6 && (string(argv[4]) == "-bin")) {
		int bin_size = stoi(string(argv[5]));
		classification.build_histogram(bin_size);
	}

	else if(argc == 8 && (string(argv[6]) == "-bin")) {
		int bin_size = stoi(string(argv[7]));
		classification.build_histogram(bin_size);
	}

	else if ((argc == 4 && (string(argv[2]) != "-bin")) || (argc == 6 && (string(argv[4]) != "-bin")) || (string(argv[6]) != "-bin")) {
		int bin_size = 10; // default number of bins
		cout << "building histogram..." << endl;
		classification.build_histogram(bin_size); // use default number of bins
	}


	if ((argc == 4 && (string(argv[2]) == "-k"))) {
		// int number_of_clusters = 10; // default number of clusters
		int number_of_clusters = stoi(string(argv[3]));
		classification.kMeansClusterer(number_of_clusters); // write output to terminal
	 	//classification.write_output(); // write output to terminal
	 }
	else if ((argc == 4 && (string(argv[2]) == "-o")) && (argc == 6 && (string(argv[4]) == "-k"))) {
		int number_of_clusters = stoi(string(argv[5]));
		string output_file = string(argv[3]);
		classification.kMeansClusterer(number_of_clusters, output_file); // write output to file
		//classification.write_output(output_file); // write output to file
	}
	else if ((argc == 4 && (string(argv[2]) == "-o")) && ((argc == 4 && (string(argv[2]) != "-k")) || (argc == 6 && (string(argv[4]) != "-k")))) {
		int number_of_clusters = 10; // default number_of_clusters
		classification.kMeansClusterer(number_of_clusters); // use default number of clusters
		//classification.write_output(output_file); // write output to file
	}	

	
	else {
		cout << "Command not found." << endl;
		cout << "Application can be invoked using the following command: " << endl;
		cout << "./clusterer <dataset> [-o output] [-k n] [-bin b]" << endl;
		cout << "Where the argument <dataset> must be provided and [-o output] [-k n] [-bin b] are optional arguments." << endl;
	}


}