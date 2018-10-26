#include "classGen.h"

int main(int argc, char** argv) {
	int error_code(0);
	try {
		ClassGen gen(argc, argv);
		
		
	} catch(TCLAP::ArgException &e) {
		error_code = 1;
        std::cerr << "Error: " + e.error() + " " + e.argId();
	} catch(std::string &e) {
		error_code = 2;
        std::cerr << "Error: " + e << std::endl;
	}
	
	return error_code; // initialized to 0
}
