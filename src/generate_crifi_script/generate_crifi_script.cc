#include <stdio.h>
#include <unistd.h>

#include <ffi_clips_interface.h>
#include <ntriplesParser.h>
#include <resource_manager.h>
#include <iostream>
#include <stdexcept>
#include "crifi_raptor.h"

#define _USAGE "Usage: %s [-i input] [-o output] name\n"

const char *input, *output;

/**
 * See `https://librdf.org/raptor/api/raptor-parsers.html`_ for more info.
 * TODO: move this to parse input
 */
const char* format = "guess";

/**
 * TODO: move this to parse input
 */
const char* baseuri = "http://example.com/";
crifi_graph* graph = NULL;
struct TriplesLinkedList *retFacts = NULL;
std::string *logicAsString = nullptr;

static int parse(int argc, char* argv[]);
static int load_inputfile();
static int generate_logic();
static int print_logic();

static void print_parsing_error(int err);
static void print_serialize_script_error(int err);
static void print_serialize_turtle_error(int err);


int main(int argc, char* argv[]){
	int err = EXIT_SUCCESS;
	if (0 != parse(argc, argv))
		exit(EXIT_FAILURE);

	if (0 != load_inputfile())
		exit(EXIT_FAILURE);
	if (0 == generate_logic()){
		if (0 == print_logic()) {
			err = EXIT_FAILURE;
		} else {
			err = EXIT_SUCCESS;
		}
	} else {
		err = EXIT_FAILURE;
	}
	delete(logicAsString);
	//free_linked_list(retFacts);
	close_graph(graph);
	exit(err);
}


static int print_logic(){
	int ctrl = crifi_serialize_all_triples(graph, stdout, "turtle", "");
	if (0 == ctrl) print_serialize_turtle_error(ctrl);
	//int ctrl = serialize_information_as_clips_script(stdout, graph);
	//if (0 == ctrl) print_serialize_script_error(ctrl);
	return ctrl;
	/*
	if (logicAsString == nullptr) return 1;
	printf("%s", logicAsString->c_str());
	return 0;
	*/
}

static int generate_logic(){
	return 0;
	/*
	
	try {
		logicAsString = generate_rif_logic(retFacts, NULL, NULL);
	} catch (const std::runtime_error& err){
		std::cerr << "generate rif logic failed: " << err.what();
		std::cerr << std::endl;
		return 1;
	}
	if (logicAsString == nullptr){
		fprintf(stderr, "generate_rif_logic didnt return "
				"logic as string.\n");
		return 1;
	} else  {
		return 0;
	}
	*/
}


static int load_inputfile(){
	int err;
	FILE *q;
       
	if (graph != 0){
		fprintf(stderr, "Internal error: already existing graph\n");
		return 1;
	}

	q = fopen(input, "r");
	if (q == NULL){
		fprintf(stderr, "failed opening input: %s\n", input);
		return 1;
	}

	graph = init_graph();
	err = crifi_parse_to_triples(graph, q, format, baseuri);
	fclose(q);
	if (err != 0){
		print_parsing_error(err);
		return 1;
	}
	retFacts = get_facts(graph, NULL, NULL, NULL);
	//close_graph(graph);
	//graph = NULL;
	if (retFacts != NULL){
		return 0;
	} else {
		return 1;
	}
	/*

	retFacts = ntriples_parse_triples_f(q, 0);
	if (retFacts == NULL){
		fprintf(stderr, "couldnt load facts from input: %s\n", input);
		return 2;
	}
	fclose(q);
	return 0;
	*/
}


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
				return 1;
		}
	}
	if (optind < argc) { //extra argument after '-x' args
		fprintf(stderr, _USAGE, argv[0]);
		return 1;
	} else if (input == NULL) {
		fprintf(stderr, "-i required\n", argv[0]);
		return 1;
	} else if (output == NULL) {
		//fprintf(stderr, "-o required\n", argv[0]);
	}
	return 0;
}


static void print_parsing_error(int err){
	switch(err){
		case CRIFI_PARSE_NOERROR:
			break;
		case CRIFI_PARSE_INITERROR:
			fprintf(stderr, "Initialization of raptor framework failed.");
			break;
		case CRIFI_PARSE_BASEERROR:
			fprintf(stderr, "Couldnt parse given base as uri.");
			break;
		case CRIFI_PARSE_TERM_CONVERT:
			fprintf(stderr, "Couldnt convert some term to clipsvalue.");
			break;
		case CRIFI_PARSE_UNKNOWN:
			fprintf(stderr, "undescribed error");
			break;
		default:
			fprintf(stderr, "unhandled error");
	}
}
static void print_serialize_script_error(int err){
	switch (err){
		case CRIFI_SERIALIZE_SCRIPT_NOERROR:
			break;
		case CRIFI_SERIALIZE_BROKEN_GRAPH:
			fprintf(stderr, "Broken Graph");
			break;
		case CRIFI_SERIALIZE_MALLOC_ERROR:
			fprintf(stderr, "Malloc error");
			break;
		case CRIFI_SERIALIZE_SCRIPT_INPUT:
			fprintf(stderr, "Input has void pointer.");
			break;
		case CRIFI_SERIALIZE_SCRIPT_CANT_CREATE_NODE:
			fprintf(stderr, "Cant malloc new node.");
			break;
		case CRIFI_SERIALIZE_SCRIPT_CANT_CREATE_STRUCTS:
			fprintf(stderr, "Initialization problem.");
			break;
		case CRIFI_SERIALIZE_SCRIPT_UNHANDLED_PREDICATE:
			fprintf(stderr, "didnt recognize a predicate");
			break;
		case CRIFI_SERIALIZE_SCRIPT_SUBJECT:
			fprintf(stderr, "failed getting raptor term from subject");
			break;
		case CRIFI_SERIALIZE_SCRIPT_PREDICATE:
			fprintf(stderr, "failed getting raptor term from predicate");
			break;
		case CRIFI_SERIALIZE_SCRIPT_OBJECT:
			fprintf(stderr, "failed getting raptor term from object");
			break;
		case CRIFI_SERIALIZE_SCRIPT_FAILED_ADDING_NEW_NODE:
			fprintf(stderr, "Failed adding new node.");
			break;
		case CRIFI_SERIALIZE_SCRIPT_UNKNOWN:
		default:
			fprintf(stderr, "unhandled error");
	}
}
static void print_serialize_turtle_error(int err){
	switch (err){
		case CRIFI_SERIALIZE_NOERROR:
			break;
		case CRIFI_SERIALIZE_TERM:
			fprintf(stderr, "Couldnt transform all terms");
			break;
		case CRIFI_SERIALIZE_MISSING_FORMAT:
		case CRIFI_SERIALIZE_MISSING_BASE:
			fprintf(stderr, "Input error");
			break;
		default:
			fprintf(stderr, "unhandled error");
	}
}
