#pragma once

#include "crifi_import.h"
#include "bnode_lookup.h"

typedef enum {
	CRIFI_IMPORT_IP_DIRECT,
	CRIFI_IMPORT_IP_SIMPLE_TO_RIF,
	CRIFI_IMPORT_IP_SIMPLE_TO_OWL,
	CRIFI_IMPORT_IP_UNKNOWN
} CRIFI_IMPORT_INTERPRETER_ID;

typedef struct rdfToRifInfo RdfToRifInfo;

typedef struct simpleToOwlInfo SimpleToOwlInfo;
typedef struct directInterpretationInfo DirectInterpretationInfo;

typedef struct importProcess {
	crifi_graph *graph;
	CRIFI_IMPORT_INTERPRETER_ID interpreter_id;
	union {
		DirectInterpretationInfo* direct_info;
		RdfToRifInfo *rdf_to_rif_info;
		SimpleToOwlInfo *simple_to_owl_info;
	};
} ImportProcess;

/**
 * Simplest form of a function, that starts an ImportProcess.
 *
 * Some Import processes use other types of import processes for the interaction
 * to the graph. At the end of those combined import processes the subprocess
 * is created with a function of this type.
 */
typedef ImportProcess* SimpleStartImportProcesss(crifi_graph *graph);
