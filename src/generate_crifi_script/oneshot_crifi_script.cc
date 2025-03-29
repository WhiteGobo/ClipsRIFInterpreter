#include <stdio.h>
#include <unistd.h>

#include <ffi_clips_interface.h>
#include <iostream>
#include "crifi_raptor.h"
#include "crifi_import.h"

#define USAGE "Usage: %s [-d DATAPATH] sourcepath\n"

FILE* source = NULL;
FILE* data = NULL;
crifi_graph *graph = NULL;

CRIFI_IMPORT_MODEL_ID model = CRIFI_IMPORT_MODEL_UNDEFINED;

//const char *outformat = "turtle";
const char *outformat = "turtle";

/**
 * See `https://librdf.org/raptor/api/raptor-parsers.html`_ for more info.
 */
const char* format = "turtle";

/**
 * TODO: move this to parse input
 */
const char* baseuri = "http://example.com/";

static int parse(int argc, char* argv[]);
static int load_graph();
static int run();
static int postprocess();

static void print_parsing_error(int err);
static void print_serialize_turtle_error(int err);
static void print_serialize_script_error(int err);

int main(int argc, char* argv[]){
	int err = EXIT_SUCCESS;
	if (0 != parse(argc, argv)){
		err = EXIT_FAILURE;
	} else if (0 != load_graph()){
		err = EXIT_FAILURE;
	} else if (0 != run()){
		err = EXIT_FAILURE;
	} else if (0 != postprocess()){
		err = EXIT_FAILURE;
	}

	close_graph(graph);
	if (source != NULL) fclose(source);
	if (data != NULL) fclose(data);

	exit(err);
}

static int postprocess(){
	int ctrl;
	if (0 == strcmp("clipsscript", outformat)){
		ctrl = serialize_information_as_clips_script(stdout, graph);
		if (0 != ctrl) print_serialize_script_error(ctrl);
	} else {
		ctrl = crifi_serialize_all_triples(graph, stdout, outformat, "");
		if (0 != ctrl){
			print_serialize_turtle_error(ctrl);
			return ctrl;
		}
	}
	return ctrl;
}

static int run(){
	int number_rule_executions = run_rules(graph, -1);
	fprintf(stderr, "Number of rule executions: %d\n", number_rule_executions);

	if (graph_in_errorstate(graph, stderr)){
		fprintf(stderr, "Exiting after graph in errorstate: "
				"printing current information:\n");
		eval(graph, "(facts)");
		crifi_serialize_all_triples(graph, stderr, outformat, "");
		fprintf(stderr, "Exiting after graph in errorstate\n");
		return 1;
	}
	return 0;
}

static int load_graph(){
	int err;
	off_t script_size;
	char *script, *eo_script;
	graph = init_graph();
	if (graph == NULL) {
		fprintf(stderr, "Internal error. Failed to init_graph\n");
		return 1;
	}

	if (model != CRIFI_IMPORT_MODEL_UNDEFINED){
		if (0 != set_model_id_for_import(graph, model)){
			fprintf(stderr, "Invalid graph model.\n");
			return 1;
		}
	}

	if (fseeko(source, 0, SEEK_END) != 0) {
		fprintf(stderr, "Couldnt process given source\n");
		return 1;
	}
	script_size = ftello(source);
	if (fseeko(source, 0, SEEK_SET) != 0) {
		fprintf(stderr, "Couldnt process given source\n");
		return 1;
	}
	eo_script = script = (char*) malloc(script_size+1);
	while(fgets(eo_script, script_size, source)){
		eo_script = strchr(eo_script, '\0');
	}
	if(!load_script(graph, script)){
		fprintf(stderr, "loading script: \n%s\n\n", script);
		free(script);
		fprintf(stderr, "Couldnt load script.\n");
		return 1;
	}
	free(script);

	if (data != NULL){
		err = crifi_parse_to_triples(graph, data, format, baseuri);
		if (err != 0){
			print_parsing_error(err);
			return 1;
		}
	}
	return 0;
}

static int parse(int argc, char* argv[]){
	int opt;
	char *sourcepath, *datapath;
	while ((opt = getopt(argc, argv, "d:i:o:m:")) != -1){
		switch (opt){
			case 'i':
				format = optarg;
				break;
			case 'o':
				outformat = optarg;
				break;
			case 'd':
				data = fopen(optarg, "r");
				if (data==NULL){
					fprintf(stderr, "Couldnt open: '%s'\n",
							optarg);
					return 1;
				}
				break;
			case 'm':
				if (0 == strcmp(optarg, "rif")){
					model = CRIFI_IMPORT_MODEL_RIFGENERATOR;
				} else {
					fprintf(stderr, "'%s' isnt a valid "
							"model\n", optarg);
					fprintf(stderr, USAGE, argv[0]);
					return 1;
				}
				break;
			default:
				fprintf(stderr, "cant handle '%s %s'",
						argv[optind-1], optarg);
				fprintf(stderr, USAGE, argv[0]);
				return 1;
		}
	}
	/*
	if (script_as_string != NULL) {
		if (optind != argc-1) { //no positional arg if script as string
			fprintf(stderr, USAGE, argv[0]);
			return 1;
		}
		fmemopen(script_as_string);
	} else */
	if (optind == argc-1) {
		sourcepath = argv[optind];
		source = fopen(sourcepath, "r");
		if (source == NULL){
			fprintf(stderr, "Couldnt open: '%s'\n", sourcepath);
			return 1;
		}
	} else { //exactly one positional argument after opt
		fprintf(stderr, "Expects exactly one positional argument\n");
		fprintf(stderr, USAGE, argv[0]);
		return 1;
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
	print_serialize_turtle_error(err);
}

static void print_serialize_turtle_error(int err){
	if (err == CRIFI_SERIALIZE_NOERROR) return;
	fprintf(stderr, "crifi_serialize_all_triples failed,\n");
	switch (err){
		case CRIFI_SERIALIZE_TERM:
			fprintf(stderr, "Couldnt transform all terms"
					"(CRIFI_SERIALIZE_TERM)\n");
			break;
		case CRIFI_SERIALIZE_MISSING_FORMAT:
		case CRIFI_SERIALIZE_MISSING_BASE:
			fprintf(stderr, "Input error\n");
			break;
		default:
			fprintf(stderr, "unhandled error\n");
	}
}
