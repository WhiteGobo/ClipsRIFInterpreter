#pragma once

#include "bnode_lookup.h"

typedef enum {
	CRIFI_IMPORT_IP_DIRECT,
	CRIFI_IMPORT_IP_SIMPLE_TO_RIF,
	CRIFI_IMPORT_IP_UNKNOWN
} CRIFI_IMPORT_INTERPRETER_ID;

typedef struct importProcess {
	crifi_graph *graph;
	CRIFI_IMPORT_INTERPRETER_ID interpreter_id;
	BNodeLookup *bnode_lookup;
} ImportProcess;
