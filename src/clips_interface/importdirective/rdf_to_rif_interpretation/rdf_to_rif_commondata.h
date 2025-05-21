#pragma once

#include "rdf_to_rif_interpretation.h"
#include "clipsvalue_interface.h"
#include "interpretations.h"
#include "triple_list.h"
#include "pair_list.h"
#include "rdf_list.h"

typedef struct rdfToRifInfo {
	BNodeLookup* bnode_lookup;

	TripleList *first_triple;
	TripleList *last_triple;
	PairList *first_member;
	PairList *last_member;
	PairList *first_subclass;
	PairList *last_subclass;
	RDFListInfo *list_info;

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

struct rdfToRifInfo* generate_rdf_rif_info(crifi_graph *graph);
void free_rdf_rif_info(struct rdfToRifInfo *info);
