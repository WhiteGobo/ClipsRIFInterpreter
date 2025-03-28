#include "crifi_import.h"
#include "interpretations.h"
#include "info_query.h"

#include "direct_interpretation.h"
#include "rdf_to_rif_interpretation.h"


int get_interpretation_id(crifi_graph *graph, CLIPSValue *cv){
	const char* value = _CRIFI_MODEL_SIMPLE_;
	int err = uri_to_clipsvalue(graph,
			value, strlen(value),
			cv);
	return err;
}

static CRIFI_IMPORT_INTERPRETER_ID get_interpreter(crifi_graph *graph, CLIPSValue *input_entailment){
	int err;
	CRIFI_IMPORT_INTERPRETER_ID ret = CRIFI_IMPORT_IP_UNKNOWN;
	char *entailment = extract_uri(graph, input_entailment->header);
	if (entailment == NULL) return CRIFI_IMPORT_IP_UNKNOWN;
	CLIPSValue graph_interpretation_id = {.voidValue = VoidConstant(graph)};
	CLIPSValue tmpval = {.voidValue = VoidConstant(graph)};

	err = get_interpretation_id(graph, &graph_interpretation_id);
	char *model = extract_uri(graph, graph_interpretation_id.header);
	if (model == NULL){
		free(entailment);
		return CRIFI_IMPORT_IP_UNKNOWN;
	}
	if (0 == strcmp(entailment, _RIFENTAIL_SIMPLE_)){
		if (0 == strcmp(model, _CRIFI_MODEL_SIMPLE_)){
			ret = CRIFI_IMPORT_IP_DIRECT;
		} else if (0 == strcmp(model, _CRIFI_MODEL_RIFGENERATOR_)){
			ret = CRIFI_IMPORT_IP_SIMPLE_TO_RIF;
		}
	} else if (0 == strcmp(entailment, _RIFENTAIL_RIF_)){
		if (0 == strcmp(model, _CRIFI_MODEL_SIMPLE_)){
			ret = CRIFI_IMPORT_IP_UNKNOWN;
		} else if (0 == strcmp(model, _CRIFI_MODEL_RIFGENERATOR_)){
			ret = CRIFI_IMPORT_IP_DIRECT;
		}
	}
	free(entailment);
	free(model);
	return ret;
}

ImportProcess *start_import_process(crifi_graph *graph, CLIPSValue *input_interpretation){
	ImportProcess * ret = NULL;
	CRIFI_IMPORT_INTERPRETER_ID interpreter_id = get_interpreter(graph,
							input_interpretation);
	switch (interpreter_id){
		case CRIFI_IMPORT_IP_DIRECT:
			ret = start_import_process_direct_interpretation(graph);
			break;
		case CRIFI_IMPORT_IP_SIMPLE_TO_RIF:
		case CRIFI_IMPORT_IP_UNKNOWN:
		default:
			return NULL;
	}
	if (ret != NULL){
		ret->interpreter_id = interpreter_id;
	}
	return ret;
}

int end_import_process(ImportProcess *process){
	if (process == NULL){
		return 1;
	}
	switch (process->interpreter_id){
		case CRIFI_IMPORT_IP_DIRECT:
			return end_import_process_direct_interpretation(process);
		case CRIFI_IMPORT_IP_SIMPLE_TO_RIF:
		case CRIFI_IMPORT_IP_UNKNOWN:
		default:
			break;
	}
	return 2;
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
		case CRIFI_IMPORT_IP_SIMPLE_TO_RIF:
			return assert_frame_rdf_to_rif(process,
					object, object_suffix, object_type,
					slotkey, slotkey_suffix, slotkey_type,
					slotvalue, slotvalue_suffix,
					slotvalue_type);
	}
	return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
}
