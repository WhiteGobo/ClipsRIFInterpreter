#pragma once

#include "ffi_clips_interface.h"
#include "crifi_import.h"

typedef struct bnodelookup BNodeLookup;

BNodeLookup* new_bnodelookup();
//int retrieve_blanknode(crifi_graph *graph, const char *bnode_id,
//			BNodeLookup *bnode_lookup, CLIPSValue* retval);
CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_RET retrieve_blanknode(
		ImportProcess *process,
		ClipsvalueRetriever* node_retriever,
		const char *id, const char *suffix, IMPORT_TERM_TYPE type,
		void* context, //BNodeLookup* context,
		CLIPSValue* retval);

void free_bnodelookup(BNodeLookup *bnode_lookup);
