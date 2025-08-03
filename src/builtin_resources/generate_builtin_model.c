#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include "ffi_constants.h"
#include "crifi_builtin_resources.h"
#include "crifi_raptor.h"
#include "crifi_graph_models.h"
#include <time.h>

#define _CRIFI_MODELA_DATA_BASEURI_ "http://white.gobo/crifi/built_resources/data_modela#"
#define _CRIFI_BUILTIN_MODEL_GENERATE_MODELA_ _CRIFI_MODELA_DATA_BASEURI_ "crifi_modelA"
#define _CRIFI_BUILTIN_MODEL_GENERATE_MODELA_CHECKER_ _CRIFI_MODELA_DATA_BASEURI_ "crifi_modelA_checker"

typedef enum {
	GBM_ERROR = -1,
	GBM_UNKNOWN_MODEL,
	GBM_MODELA = 'a',
	GBM_MODELA_CHECKER = 'A',
	GBM_MODELB = 'b',
	HELP
} MODEL_TYPE;

MODEL_TYPE modeltype = GBM_UNKNOWN_MODEL;
crifi_graph* graph = NULL;
FILE *out_f;
char *out_filename_after_run_info = NULL;
int verbosity = 0;
long long cycle_size = 100000;
long long maximal_number_rules_run = 0;
bool use_alternative_building_model = false;

static int parse(int argc, char* argv[]);
static int init_graph_with_import();
static int import_base_information();
static int printout_generated_rules();
static int run_imported_rules();
static void print_help(char* argv[]);

int main(int argc, char* argv[]){
	int err = EXIT_SUCCESS;
	out_f = stdout;
	if (0 != parse(argc, argv)){
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

static int printout_generated_rules_first();
static int printout_generated_rules_stable();

static int printout_generated_rules(){
	if (!use_alternative_building_model){
		return printout_generated_rules_first();
	} else {
		return printout_generated_rules_stable();
	}
}
static int printout_generated_rules_first(){
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
			fprintf(out_f, "%s\n", retval.val.string);
			break;
		case CTC_DYNAMIC_ERROR:
			fprintf(stderr, "oops something went wrong\n");
			return 1;
		default:
			fprintf(stderr, "oop somethign went wrong2\n");
			return 1;
	}
	if(errorstate){
		fprintf(stderr, "graph ended in errorstate "
				"after rules have run.\n");
		return 1;
	}
	return 0;
}

static int printout_generated_rules_stable(){
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
}

static int run_imported_rules(){
	int err = 0;
	bool errorstate;
	long long number_rules_run = 1;
	long long total_number = 0;
	FILE* out_f_after_run_info = NULL;
	time_t now;
	time(&now);
	fprintf(stderr, "Starting rules at %s", ctime(&now));
	while (number_rules_run > 0){
		fprintf(stderr, "next run\n");
		if (verbosity > 3){
			fprintf(stdout, "current agenda:\n");
			eval(graph, "(agenda MAIN)");
		}
		number_rules_run = run_rules(graph, cycle_size);
		time(&now);
		fprintf(stderr, "Run further %d at %s\n", number_rules_run, ctime(&now));
		if(graph_in_errorstate(graph, stderr)){
			fprintf(stderr, "graph ended in errorstate after "
					"rules have run.\n");
			err = 1;
			number_rules_run = -1;
			break;
		}
		total_number += number_rules_run;
		if (
				maximal_number_rules_run > 0
				&& total_number > maximal_number_rules_run)
		{
			fprintf(stderr, "maximal number of rule execution "
					"reached.\n");
			err = 1;
			number_rules_run = -1;
			break;
		}
	}
	time(&now);
	fprintf(stderr, "Run in total %d rules at %s\n",
			total_number, ctime(&now));
	if (out_filename_after_run_info != NULL) {
		out_f_after_run_info = fopen(out_filename_after_run_info, "w");
		if (out_f_after_run_info != NULL){
			crifi_serialize_all_triples(graph,
					out_f_after_run_info,
					"turtle", "");
			fclose(out_f_after_run_info);
		}
	}
	if (verbosity > 3){
		fprintf(stderr, "printing information after run:\n");
		crifi_serialize_all_triples(graph, stderr, "turtle", "");
	}
	return err;
}

static int init_graph_with_import(){
	if (!use_alternative_building_model){
		graph = init_graph_model_first();
	} else {
		graph = init_graph_stable_model();
	}
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

static char *cmd_import_modelA = "(<"_CRIFI_import_"> <"_CRIFI_BUILTIN_MODEL_GENERATE_MODELA_"> <"_RIFENTAIL_RIF_">)";
static char *cmd_import_modelA_checker = "(<"_CRIFI_import_"> <"_CRIFI_BUILTIN_MODEL_GENERATE_MODELA_CHECKER_"> <"_RIFENTAIL_RIF_">)";

static int import_base_information(){
	bool errorstate;
	char *command;
	struct DynamicValue retval;
	switch (modeltype){
		case GBM_MODELA:
			retval = eval(graph, cmd_import_modelA);
			break;
		case GBM_MODELA_CHECKER:
			retval = eval(graph, cmd_import_modelA_checker);
			break;
		default:
			fprintf(stderr, "No valid model chosen.\n");
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
		fprintf(stderr, "printing information before rules run\n");
		crifi_serialize_all_triples(graph, stderr, "turtle", "");
	}
	return 0;
}

static struct option parse_options[] = {
	{"help", no_argument, NULL, HELP},
	{"modelA", no_argument, NULL, GBM_MODELA},
	{"modelAchecker", no_argument, NULL, GBM_MODELA_CHECKER},
	{"modelB", no_argument, NULL, GBM_MODELB},
	{"save-info-in", required_argument, NULL, 's'},
	{"alternative-builder", no_argument, NULL, 'x'},
	{NULL, 0, NULL, 0}
};

static int parse(int argc, char* argv[]){
	int c;
	int option_index = 0;
	while (1){
		c = getopt_long(argc, argv, "aAbvs:",
				parse_options, &option_index);
		if (c == -1){
			break;
		}
		switch (c){
			case GBM_MODELA:
			case GBM_MODELA_CHECKER:
			case GBM_MODELB:
				if (modeltype != GBM_UNKNOWN_MODEL
						&& modeltype != c){
					print_help(argv);
					fprintf(stderr, "only one model can "
							"be chosen.\n");
					return 1;
				}
				modeltype = c;
				break;
			case 'x':
				use_alternative_building_model = true;
				break;
			case 'v':
				verbosity++;
				break;
			case 's':
				out_filename_after_run_info = optarg;
				break;
			case HELP:
				print_help(argv);
				return 1;
			default:
				fprintf(stderr, "wrong argument\n");
				print_help(argv);
				return 1;
		}
	}
	return 0;
}


static void print_help(char* argv[]){
	fprintf(stderr, "Usage: %s [options] model [--help]\n"
			"  --help Printout this help and exit\n"
			"  model: one option of\n"
			"    -a, --modelA\n"
			"    -A, --modelAchecker\n"
			"    -b, --modelB\n"
			"  options:\n"
			"    --alternative-builder\n"
			"    -s, --safe-info-in infofile\n"
			"    -v[vvv] Verbosity\n",
			argv[0]);
}
