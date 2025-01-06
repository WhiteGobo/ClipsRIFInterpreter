#include <stdio.h>
#include <unistd.h>

#include <ffi_clips_interface.h>
#include <ntriplesParser.h>
#include <resource_manager.h>
#include <iostream>
#include <stdexcept>

#define _USAGE "Usage: %s [-i input] [-o output] name\n"

char *input, *output;

static int parse(int argc, char* argv[]){
	int opt;
	input = NULL;
	output = NULL;
	while ((opt = getopt(argc, argv, "i:o:")) != -1){
		switch (opt){
			case 'i':
				input = optarg;
				break;
			case 'o':
				output = optarg;
				break;
			default:
				fprintf(stderr, _USAGE, argv[0]);
				return EXIT_FAILURE;
		}
	}
	if (optind < argc) { //extra argument after '-x' args
		fprintf(stderr, _USAGE, argv[0]);
		return EXIT_FAILURE;
	} else if (input == NULL) {
		fprintf(stderr, "-i required\n", argv[0]);
		return EXIT_FAILURE;
	} else if (output == NULL) {
		//fprintf(stderr, "-o required\n", argv[0]);
	}
	return 0;
}

int main(int argc, char* argv[]){
	std::string *logicAsString = nullptr;
	struct TriplesLinkedList *retFacts;
	if (0 != parse(argc, argv)) {
		exit(EXIT_FAILURE);
	}
	FILE *q = fopen(input, "r");
	if (q==NULL){
		fprintf(stderr, "failed opening input: %s\n", input);
		exit(EXIT_FAILURE);
	}
	retFacts = ntriples_parse_triples_f(q, 0);
	if (retFacts == NULL){
		fprintf(stderr, "couldnt load facts from input: %s\n", input);
	}
	fclose(q);
	try {
		logicAsString = generate_rif_logic(retFacts, NULL, NULL);
	} catch (const std::runtime_error& err){
		std::cerr << "generate rif logic failed: " << err.what();
		std::cerr << std::endl;
		exit(EXIT_FAILURE);
	}
	if (logicAsString == nullptr){
		fprintf(stderr, "generate rif logic failed.\n");
	} else {
		printf("%s", logicAsString->c_str());
		delete(logicAsString);
	}
	free_linked_list(retFacts);
	exit(EXIT_FAILURE);
}
