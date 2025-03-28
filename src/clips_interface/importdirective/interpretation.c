#include "crifi_import.h"
#include "interpretations.h"
#include "info_query.h"


int get_interpretation_id(crifi_graph *graph, CLIPSValue *cv){
	cv->voidValue = VoidConstant(graph);
	return 1;
}

static CRIFI_IMPORT_INTERPRETER_ID get_interpreter(crifi_graph *graph, CLIPSValue *input_interpretation){
	if (true){ //input_interpretation == interpretation of graph
		return CRIFI_IMPORT_IP_DIRECT;
	}
	return CRIFI_IMPORT_IP_UNKNOWN;
}

ImportProcess *start_import_process(crifi_graph *graph, CLIPSValue *input_interpretation){
	CRIFI_IMPORT_INTERPRETER_ID interpreter_id = get_interpreter(graph,
							input_interpretation);
	if (interpreter_id == CRIFI_IMPORT_IP_UNKNOWN){
		return NULL;
	}
	ImportProcess *process = malloc(sizeof(ImportProcess));
	process->graph = graph;
	process->interpreter_id = interpreter_id;
	return process;
}

int end_import_process(ImportProcess *process){
	if (process == NULL){
		return 1;
	}
	free(process);
	return 0;
}


static int brubru(
		crifi_graph *graph,
		const char *value, const char *suffix, IMPORT_TERM_TYPE type,
		CLIPSValue *retval)
{
	int err = 0;
	size_t suffix_length;
	if (value == NULL) return 1;
	if (suffix != NULL){
		suffix_length = strlen(suffix);
	} else {
		suffix_length = 0;
	}
	switch(type){
		case CRIFI_IMPORT_TERM_URI:
			err = uri_to_clipsvalue(graph,
						value, strlen(value),
						retval);
			return err;
		case CRIFI_IMPORT_TERM_BNODE:
			err = new_blanknode(graph, retval);
			return err;
		case CRIFI_IMPORT_TERM_LANGLITERAL:
			err = value_and_lang_to_clipsvalue(graph,
						value, strlen(value),
						suffix, suffix_length,
						retval);
			return err;
		case CRIFI_IMPORT_TERM_TYPEDLITERAL:
			err = value_and_datatype_to_clipsvalue(graph,
						value, strlen(value),
						suffix, suffix_length,
						retval);
			return err;
		case CRIFI_IMPORT_TERM_UNKOWN:
		default:
			break;
	}
	return 1;
}

static CRIFI_IMPORT_ASSERT_RET assert_frame_direct(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	int err;
	CLIPSValue object_cv = {.voidValue = VoidConstant(process->graph)};
	CLIPSValue slotkey_cv = {.voidValue = VoidConstant(process->graph)};
	CLIPSValue slotvalue_cv = {.voidValue = VoidConstant(process->graph)};
	err = brubru(process->graph, object, object_suffix, object_type, &object_cv);
	if (err != 0){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	brubru(process->graph, slotkey, slotkey_suffix, slotkey_type, &slotkey_cv);
	if (err != 0){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	brubru(process->graph, slotvalue, slotvalue_suffix, slotvalue_type, &slotvalue_cv);
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

CRIFI_IMPORT_ASSERT_RET assert_frame(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	switch (process->interpreter_id){
		case CRIFI_IMPORT_IP_DIRECT:
			return assert_frame_direct(process,
					object, object_suffix, object_type,
					slotkey, slotkey_suffix, slotkey_type,
					slotvalue, slotvalue_suffix,
					slotvalue_type);
	}
	return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
}
