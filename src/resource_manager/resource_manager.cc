#include "resource_manager.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ffi_clips_interface.h>
#include <exception>
#include <format>

#include <cmrc/cmrc.hpp>

#include "additional_user_functions.h"

#define OWLLOGIC "resources/OwlLogic.clp"
#define OWLDIRECT "resources/OwlDirect.clp"
#define RIFLOGIC "resources/RifLogic.clp"
#define RDFENTAILMENT "resources/RDFEntailment.clp"
#define RDFSENTAILMENT "resources/RDFSEntailment.clp"

CMRC_DECLARE(clipsrifinterpreter);

static struct clips_graph_container create_logic_helpergraph(
		const char* logicpath,
		LoadingFunction *loading_functions,
		const void **loading_function_context,
		unsigned int loading_functions_length
		){
	auto fs = cmrc::clipsrifinterpreter::get_filesystem();
	cmrc::file asfile = fs.open(logicpath);
	std::string owllogic_data = std::string(asfile.begin(), asfile.end());
	struct clips_graph_container helper_graph = init_graph();
	if (!add_needed_user_functions(helper_graph, loading_functions, loading_function_context, loading_functions_length)){
		throw std::runtime_error("failed adding needed to clips "
				"environment functions.");
	}
	
	RET_LOADCONFIG err = load_config_mem(helper_graph,
			owllogic_data.c_str(), owllogic_data.length());

	if (err == CTC_LC_PARSING_ERROR){
		throw std::runtime_error("failed parsing.");
		//helper_graph.inErrorState = -1;
		//return helper_graph;
	}
	return helper_graph;
}

static std::string *create_clipsrifinterpreter_program(
		const char* create_clips_symbol,
		struct clips_graph_container helper_graph
		){
	std::string *retString;
	struct DynamicValue tmpval;
	char command[sizeof(create_clips_symbol)
			+ sizeof("(%s \"description\")") + 1 + 30];
	sprintf(command, "(%s \"description\")", create_clips_symbol);
	tmpval = eval(helper_graph, command);
	if (tmpval.type != CTC_DYNAMIC_STRING){
		printf("something went wrong during clips script creation.");
		return nullptr;
	}
	if (0 == strcmp(tmpval.val.string, "")) {
		printf("failed to create clips script");
		return nullptr;
	}
	retString = new std::string(tmpval.val.string);
	free_dynamic_value(tmpval);
	//free tmpval
	return retString;
}

static std::string *generate_logic(
		struct TriplesLinkedList* factlist,
		const char* logicpath,
		const char* create_clips_symbol,
		LoadingFunction *loading_functions,
		const void **loading_function_context,
		unsigned int loading_functions_length,
		int debuglevel
		){
	int err;
	std::string *retString;
	struct clips_graph_container helper_graph = create_logic_helpergraph(logicpath, loading_functions, loading_function_context, loading_functions_length);
	if (helper_graph.inErrorState != 0){
		fprintf(stderr, "Couldnt load logic\n");
		close_graph(helper_graph);
		return nullptr;
	}

	FOREACH_TRIPLE(factlist, tmpTriple){
		err = assert_fact(helper_graph, tmpTriple->subject,
				tmpTriple->predicate, tmpTriple->object, "");
		if (err != 0){
			fprintf(stderr, "Failed to assert %s, %s, %s, with %d\n",
					tmpTriple->subject,
					tmpTriple->predicate,
					tmpTriple->object, err);
			throw std::runtime_error("During generate_logic, "
					"couldnt assert triples in factlist");
		}
	}
	//eval(helper_graph, "(set-strategy simplicity)");
	if (debuglevel > 0) {
	//	if (debuglevel > 1) eval(helper_graph, "(facts)");
		free_dynamic_value(eval(helper_graph, "(watch activations)"));
		//eval(helper_graph, "(watch facts RIFRepresentation)");
	}
	auto qq = run_rules(helper_graph, -1);
	//eval(helper_graph, "(matches RIFprocess_Atom)");
	//eval(helper_graph, "(facts)");
	fprintf(stderr, "rules run: %d\n", qq);
	//tmpval = eval(helper_graph, "(matches RIFprocess_Group)");
	if (graph_in_errorstate(helper_graph)){
		throw std::runtime_error("Rulecreation ended in errorstate. "
				"Happend during run.");
	}
	retString = create_clipsrifinterpreter_program(
			create_clips_symbol, helper_graph);

	if (graph_in_errorstate(helper_graph)){
		throw std::runtime_error("Rulecreation ended in errorstate. "
				"Happend during retrieval of clips program.");
	}

	close_graph(helper_graph);
	return retString;
}


std::string *generate_rdf_entailment(struct TriplesLinkedList* rdf_triples){
	int debuglevel = 0;
	return generate_logic(rdf_triples, RDFENTAILMENT,
			"create-clips-script",
			NULL, NULL, 0,
			debuglevel);
}


std::string *generate_rdfs_entailment(struct TriplesLinkedList* rdf_triples){
	int debuglevel = 0;
	return generate_logic(rdf_triples, RDFSENTAILMENT,
			"create-clips-script",
			NULL, NULL, 0,
			debuglevel);
}


std::string *generate_owl_logic(
		struct TriplesLinkedList* OWLLogicFactlist
		){
	int debuglevel = 0;
	return generate_logic(OWLLogicFactlist, OWLLOGIC,
			"create-clips-script",
			NULL, NULL, 0,
			debuglevel);
}

std::string *generate_rif_logic(
		struct TriplesLinkedList* RIFLogicFactlist,
		LoadingFunction loading_function,
		const void *loading_function_context
		){
	int debuglevel = 0;
	LoadingFunction wrapper_lf[] = {loading_function, NULL};
	const void *wrapper_lfc[] = {loading_function_context, NULL};
	return generate_logic(RIFLogicFactlist, RIFLOGIC,
			"create-script-rif-logic",
			wrapper_lf, wrapper_lfc, 1,
			debuglevel);
}

std::string *generate_rif_statement(
		struct TriplesLinkedList* RIFLogicFactlist
		){
	int debuglevel = 0;
	return generate_logic(RIFLogicFactlist, RIFLOGIC,
			"create-script-rif-statement",
			NULL, NULL, 0,
			debuglevel);
}


std::string *generate_owldirect_entailment(
		struct TriplesLinkedList* owl_triples){
	int debuglevel = 0;
	return generate_logic(owl_triples, OWLDIRECT,
			"create-clips-script",
			NULL, NULL, 0,
			debuglevel);
}

bool check_statements(struct clips_graph_container graph){
	struct DynamicValue ret = eval(graph, CHECKFUNCTION);
	//struct DynamicValue ret = eval(graph, "TRUE");
	//if (ret != 0) throw std::runtime_error("No function loaded to "
	//					"check statements");
	switch (ret.type) {
		case CTC_DYNAMIC_BOOL:
			return ret.val.boolean;
			break;
		case CTC_DYNAMIC_ERROR:
			switch (ret.val.error){
				case CTC_CTD_CANTTRANSLATE:
					throw std::runtime_error(
						"Return value unsupported");
					break;
				case CTC_CTD_PARSING_ERROR:
					throw std::runtime_error(
						"Internal error (parsing)");
					break;
				case CTC_CTD_PROCESSING_ERROR:
					throw std::runtime_error(
						"Internal error (processing)");
					break;
				default:
					throw std::runtime_error(
							"unknown error");
					break;
			}
			break;
		default:
			throw std::runtime_error(
					"Clips function 'check-statements' "
					"didnt return bool");
	}
}
