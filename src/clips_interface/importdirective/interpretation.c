#include "crifi_import.h"
#include "interpretations.h"
#include "info_query.h"

#include "direct_interpretation.h"


int get_interpretation_id(crifi_graph *graph, CLIPSValue *cv){
	cv->voidValue = VoidConstant(graph);
	return 1;
}

static CRIFI_IMPORT_INTERPRETER_ID get_interpreter(crifi_graph *graph, CLIPSValue *input_interpretation){
	int err;
	CLIPSValue graph_interpretation_id = {.voidValue = VoidConstant(graph)};

	err = get_interpretation_id(graph, &graph_interpretation_id);
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
	process->bnode_lookup = new_bnodelookup();
	return process;
}

int end_import_process(ImportProcess *process){
	if (process == NULL){
		return 1;
	}
	free_bnodelookup(process->bnode_lookup);
	free(process);
	return 0;
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
