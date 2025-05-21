#pragma once

#include "rdf_list.h"
#include <raptor.h>
#include "clipsvalue_interface.h"
#include "crifi_lists.h"
#include "ffi_constants.h"

typedef struct rdflistinfo {
	raptor_avltree* avltree;
} RDFListInfo;

typedef struct {
	char *this_id;
	char* first;
	char* first_suffix;
	IMPORT_TERM_TYPE first_type;
	const char *next_id;
} ListEntry;

ListEntry* find_list_entry(RDFListInfo* info, const char* list_id);
