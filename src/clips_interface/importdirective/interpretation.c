#include "crifi_import.h"
#include "interpretations.h"
#include "info_query.h"

#include "direct_interpretation.h"
#include "rdf_to_rif_interpretation.h"
#include "simple_to_owl_interpretation.h"


static CRIFI_IMPORT_INTERPRETER_ID get_interpreter_model_rifgenerator_simple(
						const char *entailment);
static CRIFI_IMPORT_INTERPRETER_ID get_interpreter_model_rifgenerator(
						const char *entailment);
static CRIFI_IMPORT_INTERPRETER_ID get_interpreter_model_simple(
						const char *entailment);

static CRIFI_IMPORT_INTERPRETER_ID get_interpreter(crifi_graph *graph, CLIPSValue *input_entailment){
	int err;
	char *entailment;
	CRIFI_IMPORT_MODEL_ID model;
	CRIFI_IMPORT_INTERPRETER_ID ret = CRIFI_IMPORT_IP_UNKNOWN;
	CLIPSValue graph_interpretation_id = {.voidValue = VoidConstant(graph)};
	CLIPSValue tmpval = {.voidValue = VoidConstant(graph)};

	entailment = extract_uri(graph, input_entailment->header);
	if (entailment == NULL) {
		entailment = extract_lexical(graph, input_entailment->header);
		if (entailment == NULL) {
			return CRIFI_IMPORT_IP_UNKNOWN;
		}
	}
	model = LoadingCRIFIImportData(graph)->model_id;
	switch (model){
		case CRIFI_IMPORT_MODEL_RIFGENERATOR:
			ret = get_interpreter_model_rifgenerator(entailment);
			break;
		case CRIFI_IMPORT_MODEL_RIFGENERATOR_SIMPLE:
			ret = get_interpreter_model_rifgenerator_simple(
								entailment);
			break;
		case CRIFI_IMPORT_MODEL_SIMPLE:
			ret = get_interpreter_model_simple(entailment);
			break;
	}
	free(entailment);
	return ret;
}

static CRIFI_IMPORT_INTERPRETER_ID get_interpreter_model_rifgenerator_simple(
						const char *entailment)
{
	if (
			0 == strcmp(entailment, _RIFENTAIL_RDF_)
			|| 0 == strcmp(entailment, _RIFENTAIL_RDFS_)
			|| 0 == strcmp(entailment, _RIFENTAIL_SIMPLE_))
	{
		return CRIFI_IMPORT_IP_SIMPLE_TO_RIF;
	} else if (0 == strcmp(entailment, _RIFENTAIL_RIF_)){
		return CRIFI_IMPORT_IP_DIRECT;
	}
	return CRIFI_IMPORT_IP_UNKNOWN;
}

static CRIFI_IMPORT_INTERPRETER_ID get_interpreter_model_rifgenerator(
						const char *entailment)
{
	if (
			0 == strcmp(entailment, _RIFENTAIL_RDF_)
			|| 0 == strcmp(entailment, _RIFENTAIL_RDFS_)
			|| 0 == strcmp(entailment, _RIFENTAIL_SIMPLE_))
	{
		return CRIFI_IMPORT_IP_SIMPLE_TO_RIF;
	} else if (0 == strcmp(entailment, _RIFENTAIL_RIF_)){
		return CRIFI_IMPORT_IP_SIMPLE_TO_OWL;
		return CRIFI_IMPORT_IP_DIRECT;
	}
	return CRIFI_IMPORT_IP_UNKNOWN;
}

static CRIFI_IMPORT_INTERPRETER_ID get_interpreter_model_simple(
						const char *entailment)
{
	if (
			0 == strcmp(entailment, _RIFENTAIL_RDF_)
			|| 0 == strcmp(entailment, _RIFENTAIL_RDFS_)
			|| 0 == strcmp(entailment, _RIFENTAIL_SIMPLE_))
	{
		return CRIFI_IMPORT_IP_DIRECT;
	}
	return CRIFI_IMPORT_IP_UNKNOWN;
}


ImportProcess *start_import_process(crifi_graph *graph,
				CLIPSValue *input_interpretation)
{
	ImportProcess * ret = NULL;
	SimpleStartImportProcesss *subprocess_starter;
	CRIFI_IMPORT_INTERPRETER_ID interpreter_id;

	interpreter_id = get_interpreter(graph, input_interpretation);
	switch (interpreter_id){
		case CRIFI_IMPORT_IP_DIRECT:
			ret = start_import_process_direct_interpretation(graph);
			break;
		case CRIFI_IMPORT_IP_SIMPLE_TO_OWL:
			subprocess_starter = start_import_process_direct_interpretation;
			ret = start_import_process_simple_to_owl_interpretation(
						graph, subprocess_starter);
			break;
		case CRIFI_IMPORT_IP_SIMPLE_TO_RIF:
			ret = start_import_process_rdf_to_rif_interpretation(
						graph, interpreter_id);
			break;
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
		case CRIFI_IMPORT_IP_SIMPLE_TO_OWL:
			return end_import_process_simple_to_owl_interpretation(process);
		case CRIFI_IMPORT_IP_SIMPLE_TO_RIF:
			return end_import_process_rdf_to_rif_interpretation(process);
		case CRIFI_IMPORT_IP_UNKNOWN:
		default:
			break;
	}
	return 2;
}


CRIFI_IMPORT_ASSERT_RET crifi_import_assert_frame(ImportProcess *process,
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
		case CRIFI_IMPORT_IP_SIMPLE_TO_OWL:
			return assert_frame_simple_to_owl(process,
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

CRIFI_IMPORT_ASSERT_RET crifi_import_assert_member(ImportProcess *process,
		const char *instance, const char *instance_suffix,
		IMPORT_TERM_TYPE instance_type,
		const char *class, const char *class_suffix,
		IMPORT_TERM_TYPE class_type)
{
	switch (process->interpreter_id){
		case CRIFI_IMPORT_IP_DIRECT:
			return assert_member_direct(process,
					instance, instance_suffix, instance_type,
					class, class_suffix, class_type);
	}
	return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
}

CRIFI_IMPORT_ASSERT_RET crifi_import_assert_subclass(ImportProcess *process,
		const char *sub, const char *sub_suffix,
		IMPORT_TERM_TYPE sub_type,
		const char *super, const char *super_suffix,
		IMPORT_TERM_TYPE super_type)
{
	switch (process->interpreter_id){
		case CRIFI_IMPORT_IP_DIRECT:
			return assert_subclass_direct(process,
					sub, sub_suffix, sub_type,
					super, super_suffix, super_type);
	}
	return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
}
