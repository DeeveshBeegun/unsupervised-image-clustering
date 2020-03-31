#include <iostream>
#include <string>
#include "Classification.h"


int main(int argc, char *argv[]) {
	using namespace std;
	
	string directory_path = "./Gradient_Numbers_PPMS";

	CLASSIFICATION::Classification classification;
	classification.readDataset(directory_path);


}