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

CRIFI_IMPORT_ASSERT_RET rdf_to_rif_internal_assert_member(
		ImportProcess *process,
		const char *instance, const char *instance_suffix,
		IMPORT_TERM_TYPE instance_type,
		const char *cls, const char *cls_suffix,
		IMPORT_TERM_TYPE cls_type);

CRIFI_IMPORT_ASSERT_RET rdf_to_rif_internal_assert_subclass(
		ImportProcess *process,
		const char *sub, const char *sub_suffix,
		IMPORT_TERM_TYPE sub_type,
		const char *super, const char *super_suffix,
		IMPORT_TERM_TYPE super_type);
