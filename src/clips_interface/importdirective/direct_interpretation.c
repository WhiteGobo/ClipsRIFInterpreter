#include "direct_interpretation.h"
#include "clipsvalue_interface.h"


ImportProcess *start_import_process_direct_interpretation(crifi_graph *graph){
	ImportProcess *process = malloc(sizeof(ImportProcess));
	process->graph = graph;
	process->interpreter_id = CRIFI_IMPORT_IP_DIRECT;
	process->bnode_lookup = new_bnodelookup();
	return process;
}

int end_import_process_direct_interpretation(ImportProcess *process){
	if (process == NULL){
		return 1;
	}
	free_bnodelookup(process->bnode_lookup);
	free(process);
	return 0;
}


CRIFI_IMPORT_ASSERT_RET assert_frame_direct(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	int err;
	fprintf(stderr, "assert %s[%s -> %s]\n", object, slotkey, slotvalue);
	CLIPSValue object_cv = {.voidValue = VoidConstant(process->graph)};
	CLIPSValue slotkey_cv = {.voidValue = VoidConstant(process->graph)};
	CLIPSValue slotvalue_cv = {.voidValue = VoidConstant(process->graph)};
	err = value_suffix_to_clipsvalue(process, object, object_suffix, object_type, &object_cv);
	if (err != 0){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	err = value_suffix_to_clipsvalue(process, slotkey, slotkey_suffix, slotkey_type, &slotkey_cv);
	if (err != 0){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	err = value_suffix_to_clipsvalue(process, slotvalue, slotvalue_suffix, slotvalue_type, &slotvalue_cv);
	if (err != 0){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	err = assert_triple(process->graph, &object_cv, &slotkey_cv, &slotvalue_cv);
	switch (err){
		case CRIFI_ASSTR_NO_ERROR:
			break;
		case CRIFI_ASSTR_SUBJECT:
		case CRIFI_ASSTR_PREDICATE:
		case CRIFI_ASSTR_OBJECT:
		case CRIFI_ASSTR_UNKNOWN:
		default:
			return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	return CRIFI_IMPORT_ASSERT_NOERROR;
}
