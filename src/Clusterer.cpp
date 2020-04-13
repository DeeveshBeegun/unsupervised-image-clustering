#include <iostream>
#include <string>
#include "Classification.h"


int main(int argc, char *argv[]) {
	using namespace std;

	//string directory_path = "./Gradient_Numbers_PPMS";
	CLASSIFICATION::Classification classification;

	if(argc > 1 && (argv[1] != "-o" || argv[1] != "-k" || argv[1] != "-bin" )) {
		string directory_path = argv[1];
		cout << "Reading dataset..." << endl;
		classification.readDataset(directory_path); // read the image files in the directory
	
	}

	if (argc == 4 && (string(argv[2]) == "-o")) {
		string output_file = string(argv[3]);
		//classification.write_output(output_file);
	}

	else if ((argc == 4 && (string(argv[2]) == "-k")) || (argc == 6 && (string(argv[4]) == "-k")) || argc > 1) {
		int number_of_clusters = 10; // default number of clusters
		if(argc == 4)
			 number_of_clusters = stoi(string(argv[3]));
		else 
			 number_of_clusters = stoi(string(argv[5]));

	}

	if(argc == 4 && (string(argv[2]) == "-bin") || (argc == 8 && (string(argv[6]) == "-bin")) || (argc ==6
		&& (string(argv[4]) == "-bin"))) {

		int bin_size = 1; // default bin size 
		if(argc == 4) {
			 bin_size = stoi(string(argv[3]));
			 classification.build_histogram(bin_size);
			}
		else if(argc == 8) {
			 bin_size = stoi(string(argv[7]));
			 classification.build_histogram(bin_size);
			}
		else if(argc == 6) {
			bin_size = stoi(string(argv[5]));
			classification.build_histogram(bin_size);
		}
	

			
	}

	else {
		cout << "Command not found." << endl;
		cout << "Application can be invoked by usign the following command: " << endl;
		cout << "./clusterer <dataset> [-o output] [-k n] [-bin b]" << endl;
		cout << "Where the argument <dataset> must be provided and [-o output] [-k n] [-bin b] are optional arguments." << endl;
	}


}