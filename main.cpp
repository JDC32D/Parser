#include <fstream>
#include "Parser.h"

int main(int argc,char** argv) {
	Parser parser;

	if(argc > 1) {
		std::FILE * file = std::fopen(argv[1],"r");
		if(!file) {
			std::printf("Error opening file: \"%s\", exiting\n"
				,argv[1]);
			return -1;
		}
		parser.GetFile(file);
		if(parser.Parse()) {
			std::printf("Parser completed execution\n");
		}
		else 
			std::printf("Parsing could not complete\n");

		std::fclose(file);
	} else {
		parser.GetFile(stdin);
		if(parser.Parse()) {
			std::printf("Parser completed execution\n");
		}
		else {
			std::printf("Parser could not complete\n");
		}
	}

	/*
	Include the scanner
	Call the parser function
	Keep calling it until the scanner is out of tokens
	Parser should ensure that the token matches the grammar rules
	*/

	return 0;
}