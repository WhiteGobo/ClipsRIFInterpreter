#pragma once
#include "interpretations.h"
#include "crifi_import.h"
#include "direct_interpretation.h"

typedef struct rdflistinfo RDFListInfo;

typedef enum {
	CRIFI_IMPORT_GENERATE_RDFLIST_NOERROR = 0,
	CRIFI_IMPORT_GENERATE_RDFLIST_NOTFOUND,
	CRIFI_IMPORT_GENERATE_RDFLIST_UNKNOWN_ERROR
} CRIFI_IMPORT_GENERATE_RDFLIST;


RDFListInfo *new_RDFListInfo();

int add_first(RDFListInfo* info,
		const char* source, const char* source_suffix,
		IMPORT_TERM_TYPE source_type,
		const char* target, const char* target_suffix,
		IMPORT_TERM_TYPE target_type);

int add_rest(RDFListInfo* info,
		const char* source, const char* source_suffix,
		IMPORT_TERM_TYPE source_type,
		const char* target, const char* target_suffix,
		IMPORT_TERM_TYPE target_type);

CRIFI_IMPORT_GENERATE_RDFLIST get_list_as_clipsvalue(
			ImportProcess *process, RDFListInfo *info,
			const char *listid, const char *listid_suffix,
			IMPORT_TERM_TYPE listid_type,
			CLIPSValue *target);

void free_RDFListInfo(RDFListInfo* info);

CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_RET retrieve_rdf_list(
		ImportProcess *process,
		const char *id, const char *suffix, IMPORT_TERM_TYPE type,
		RDFListInfo* context,
		CLIPSValue* retval);
