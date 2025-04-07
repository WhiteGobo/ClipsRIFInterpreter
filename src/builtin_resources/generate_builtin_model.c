#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "ffi_constants.h"
#include "crifi_builtin_resources.h"
#include "crifi_raptor.h"
#include "crifi_graph_models.h"

#define _CRIFI_MODELA_DATA_BASEURI_ "http://white.gobo/crifi/built_resources/data_modela#"
#define _CRIFI_BUILTIN_MODEL_GENERATE_MODELA_ _CRIFI_MODELA_DATA_BASEURI_ "crifi_modelA"

typedef enum {
	GBM_ERROR = -1,
	GBM_UNKNOWN_MODEL,
	GBM_MODELA = 'a',
	GBM_MODELB = 'b'
} MODEL_TYPE;

MODEL_TYPE modeltype = GBM_UNKNOWN_MODEL;
crifi_graph* graph = NULL;
FILE *out_f;
int verbosity = 0;

static int parse(int argc, char* argv[]);
static int init_graph_with_import();
static int import_base_information();
static int printout_generated_rules();
static int run_imported_rules();

int main(int argc, char* argv[]){
	int err = EXIT_SUCCESS;
	out_f = stdout;
	if (0 != parse(argc, argv)){
		exit(EXIT_FAILURE);
	}
	switch (modeltype){
		case GBM_MODELA:
		case GBM_MODELB:
			break;
		default:
			fprintf(stderr, "No model chosen\n");
			exit(EXIT_FAILURE);
	}
	if (0 != init_graph_with_import()){
		err = EXIT_FAILURE;
	} else if (0 != import_base_information()){
		err = EXIT_FAILURE;
	} else if (0 != run_imported_rules()){
		err = EXIT_FAILURE;
	} else if (0 != printout_generated_rules()){
		err = EXIT_FAILURE;
	}
	close_graph(graph);
	//if (err != EXIT_SUCCESS) fprintf(stderr, "brubru7\n");
	exit(err);
}

static int printout_generated_rules(){
	bool errorstate;
	struct DynamicValue retval;
	retval = eval(graph, "(create-script-rif-logic \"mydescription\")");

	errorstate = graph_in_errorstate(graph, stderr);
	switch(retval.type){
		case CTC_DYNAMIC_STRING:
			if (0 == strcmp(retval.val.string, "")) {
				fprintf(stderr, "no output\n");
				return 1;
			}
			fprintf(out_f, retval.val.string);
			break;
		case CTC_DYNAMIC_ERROR:
			fprintf(stderr, "oops something went wrong\n");
			return 1;
		default:
			fprintf(stderr, "oop somethign went wrong2\n");
			return 1;
	}
	if(errorstate){
		fprintf(stderr, "graph ended in errorstate after rules have run.");
		return 1;
	}
	return 0;
	/*
	CRIFI_SERIALIZE_SCRIPT_RET err;
	err = serialize_information_as_clips_script(out_f, graph);
	switch(err){
		case CRIFI_SERIALIZE_SCRIPT_NOERROR:
			break;
		case CRIFI_SERIALIZE_MALLOC_ERROR:
		case CRIFI_SERIALIZE_BROKEN_GRAPH:
		case CRIFI_SERIALIZE_SCRIPT_CANT_CREATE_NODE:
		case CRIFI_SERIALIZE_SCRIPT_CANT_CREATE_STRUCTS:
		case CRIFI_SERIALIZE_SCRIPT_UNHANDLED_PREDICATE:
		case CRIFI_SERIALIZE_SCRIPT_SUBJECT:
		case CRIFI_SERIALIZE_SCRIPT_PREDICATE:
		case CRIFI_SERIALIZE_SCRIPT_FAILED_ADDING_NEW_NODE:
		case CRIFI_SERIALIZE_SCRIPT_OBJECT:
		case CRIFI_SERIALIZE_SCRIPT_INPUT:
		case CRIFI_SERIALIZE_SCRIPT_UNKNOWN:
		default:
			fprintf(stderr, "Unhandled error during serialization "
					"of graphinformation as clips script.");
			return 1;
	}
	return 0;
	*/
}

static int run_imported_rules(){
	bool errorstate;
	run_rules(graph, -1);
	if(graph_in_errorstate(graph, stderr)){
		fprintf(stderr, "graph ended in errorstate after rules have run.");
		return 1;
	}
	if (verbosity > 0){
		fprintf(stderr, "printing information after rules have run\n");
		crifi_serialize_all_triples(graph, stderr, "turtle", "");
	}
	return 0;
}

static int init_graph_with_import(){
	//graph = init_graph();
	//graph = init_graph_first();
	graph = init_graph_model_first();
	if (graph == NULL){
		fprintf(stderr, "Couldnt initialize graph. Broken library?\n");
		return 1;
	}
	if(!add_builtin_resources(graph)){
		fprintf(stderr, "Coudldnt add builtin resources. "
				"Broken library?n\n");
		return 1;
	}
	return 0;
}

static char *cmd_import_modelA = "(<"_CRIFI_import_"> <"_CRIFI_BUILTIN_MODEL_GENERATE_MODELA_"> <"_RIFENTAIL_SIMPLE_">)";

static int import_base_information(){
	bool errorstate;
	char *command;
	struct DynamicValue retval;
	switch (modeltype){
		case GBM_MODELA:
			retval = eval(graph, cmd_import_modelA);
			break;
		default:
			fprintf(stderr, "Given model isnt implemented.\n");
			return 1;
	}
	errorstate = graph_in_errorstate(graph, stderr);
	switch (retval.type){
		case CTC_DYNAMIC_ERROR:
			switch (retval.val.error){
				case CTC_CTD_PARSING_ERROR:
					fprintf(stderr, "parsing error? test broken? "
							"crifi:import is maybe not "
							"loaded as "
							"user defined function");
					return 1;
				case CTC_CTD_PROCESSING_ERROR:
				fprintf(stderr, "failed processing command.");
					return 1;
				case CTC_CTD_CANTTRANSLATE:
					fprintf(stderr, "Cant process returned "
						"CLIPSValue to DynamicType");
					return 1;
				default:
					fprintf(stderr, "eval import failed. "
						"Unhandled error.");
					return 1;
			}
			break;
		case CTC_DYNAMIC_BOOL:
			if(!retval.val.boolean){
				fprintf(stderr, "Crifi:import failed. Used:\n");
				return 1;
			}
			break;
		default:
			fprintf(stderr, "crifi:import return unexpected value.");
			return 1;
	}
	if (errorstate){
		fprintf(stderr, "graph ended up in errorstate after import\n");
		return 1;
	}
	if (verbosity > 1){
		fprintf(stderr, "printing information after base import "
				"before rules run\n");
		crifi_serialize_all_triples(graph, stderr, "turtle", "");
	}
	return 0;
}

static struct option parse_options[] = {
	{"modelA", no_argument, NULL, GBM_MODELA},
	{"modelB", no_argument, NULL, GBM_MODELB},
	{NULL, 0, NULL, 0}
};

static int parse(int argc, char* argv[]){
	int c;
	int option_index = 0;
	while (1){
		c = getopt_long(argc, argv, "abv",
				       parse_options, &option_index);
		if (c == -1){
			break;
		}
		switch (c){
			case GBM_MODELA:
			case GBM_MODELB:
				if (modeltype != GBM_UNKNOWN_MODEL
						&& modeltype != c){
					fprintf(stderr, "only one model can "
							"be chosen.\n");
					return 1;
				}
				modeltype = c;
				break;
			case 'v':
				verbosity++;
				break;
			default:
				fprintf(stderr, "wrong argument\n");
				return 1;
		}
	}
	return 0;
}
