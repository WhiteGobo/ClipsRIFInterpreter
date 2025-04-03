#pragma once

#include "bnode_lookup.h"

typedef enum {
	CRIFI_IMPORT_IP_DIRECT,
	CRIFI_IMPORT_IP_SIMPLE_TO_RIF,
	CRIFI_IMPORT_IP_UNKNOWN
} CRIFI_IMPORT_INTERPRETER_ID;

struct rdfToRifInfo {
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
};

typedef struct importProcess {
	crifi_graph *graph;
	CRIFI_IMPORT_INTERPRETER_ID interpreter_id;
	BNodeLookup *bnode_lookup;
	union {
		struct rdfToRifInfo rdf_to_rif_info;
	};
} ImportProcess;
