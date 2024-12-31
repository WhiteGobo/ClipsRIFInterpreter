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
			case 'o':
				input = optarg;
				break;
			case 'i':
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
		fprintf(stderr, "-i required", argv[0]);
	} else if (output == NULL) {
		fprintf(stderr, "-o required", argv[0]);
	}
	return 0;
}

int main(int argc, char* argv[]){
	std::string *logicAsString = nullptr;
	struct TriplesLinkedList *retFacts;
	if (0 != parse(argc, argv)) {
		exit(EXIT_FAILURE);
	}
	printf("parsing worked. i: %s o: %s\n", input, output);
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
		std::cout << "generate rif logic failed: " << err.what();
		std::cout << std::endl;
		exit(EXIT_FAILURE);
	}
	if (logicAsString == nullptr){
		fprintf(stderr, "generate rif logic failed.\n");
	} else {
		delete(logicAsString);
	}
	free_linked_list(retFacts);
	exit(EXIT_FAILURE);
}
