#pragma once

#include "rdf_list.h"

CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_RET get_rif_list(
		ImportProcess *process,
		ClipsvalueRetriever* node_retriever,
		const char *id, const char *suffix, IMPORT_TERM_TYPE type,
		void* context, //RDFListInfo* context,
		CLIPSValue* retval);

CRIFI_IMPORT_ASSERT_RET assert_triple_rdf_to_rif(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type);
