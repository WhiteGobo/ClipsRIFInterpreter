#pragma once

#include "ffi_clips_interface.h"

typedef struct bnodelookup BNodeLookup;

BNodeLookup* new_bnodelookup();
int retrieve_blanknode(crifi_graph *graph, const char *bnode_id,
			BNodeLookup *bnode_lookup, CLIPSValue* retval);
void free_bnodelookup(BNodeLookup *bnode_lookup);
