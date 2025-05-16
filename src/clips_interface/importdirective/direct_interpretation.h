#pragma once

#include "crifi_import.h"
#include "interpretations.h"
#include "info_query.h"

typedef enum {
	CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_SUCCESS = 0,
	CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_NOTFOUND,
	CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_UNHANDLED_ERROR
} CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_RET;

typedef CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_RET clipsvalue_retrieving_function(
		ImportProcess *process,
		const char *id, const char *suffix, IMPORT_TERM_TYPE type,
		void* context,
		CLIPSValue* retval);


ImportProcess *start_import_process_direct_interpretation(crifi_graph *graph);
int end_import_process_direct_interpretation(ImportProcess *process);

CRIFI_IMPORT_ASSERT_RET assert_frame_direct(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type);

CRIFI_IMPORT_ASSERT_RET assert_member_direct(ImportProcess *process,
		const char *instance, const char *instance_suffix,
		IMPORT_TERM_TYPE instance_type,
		const char *class, const char *class_suffix,
		IMPORT_TERM_TYPE class_type);

CRIFI_IMPORT_ASSERT_RET assert_subclass_direct(ImportProcess *process,
		const char *sub, const char *sub_suffix,
		IMPORT_TERM_TYPE sub_type,
		const char *super, const char *super_suffix,
		IMPORT_TERM_TYPE super_type);

int add_clipsvalue_retriever(ImportProcess *process, clipsvalue_retrieving_function* retriever, void* context);
