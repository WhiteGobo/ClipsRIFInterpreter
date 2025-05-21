#pragma once

#include "crifi_import.h"
#include "bnode_lookup.h"

typedef enum {
	CRIFI_IMPORT_IP_DIRECT,
	CRIFI_IMPORT_IP_SIMPLE_TO_RIF,
	CRIFI_IMPORT_IP_SIMPLE_TO_OWL,
	CRIFI_IMPORT_IP_UNKNOWN
} CRIFI_IMPORT_INTERPRETER_ID;

typedef struct rdfToRifInfo {
	BNodeLookup* bnode_lookup;
	CLIPSValue document;
	CLIPSValue group;
	CLIPSValue rule_list;

	CLIPSValue rdf_type;
	CLIPSValue rdf_first;
	CLIPSValue rdf_rest;
	CLIPSValue rdf_nil;

	CLIPSValue rif_Document;
	CLIPSValue rif_Group;
	CLIPSValue rif_payload;
	CLIPSValue rif_sentences;
	CLIPSValue rif_Const;
	CLIPSValue rif_constIRI;
	CLIPSValue rif_value;
	CLIPSValue rif_Var;
	CLIPSValue rif_varname;
	CLIPSValue rif_Frame;
	CLIPSValue rif_slots;
	CLIPSValue rif_Slot;
	CLIPSValue rif_slotkey;
	CLIPSValue rif_slotvalue;
	CLIPSValue rif_object;
} RdfToRifInfo;

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
