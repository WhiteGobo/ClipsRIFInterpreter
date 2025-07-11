#include "crifi_import.h"
#include "info_query.h"

int crifi_add_import_function(crifi_graph *graph,
		CRIFIImportMethod *method,
		const void *context,
		CRIFIImportDataCleanupFunction *cleanup_function)
{
	CRIFISingleImportData *next;
	CRIFIImportData *data = LoadingCRIFIImportData(graph);
	CRIFISingleImportData **saveposition = &(data->first);
	while(*saveposition != NULL){
		saveposition = &(saveposition[0]->next);
	}
	next = malloc(sizeof(CRIFISingleImportData));
	if (next == NULL){
		return 1;
	}
	next->next = NULL;
	next->method = method;
	next->context = context;
	next->cleanup_function = cleanup_function;

	*saveposition = next;
	return 0;
}

void free_crifi_singleimportdata(CRIFISingleImportData *data){
	CRIFISingleImportData *tmp;
	CRIFISingleImportData *next = data;
	while (next != NULL){
		tmp = next->next;
		if(next->cleanup_function != NULL){
			(*next->cleanup_function)(next->context);
		}
		free(next);
		next = tmp;
	}
}

static char *extract_import_location(crifi_graph *graph, CLIPSValue *import_location){
	char *ret;
	ret = extract_uri(graph, import_location->header);
	if (ret != NULL){
		return ret;
	}
	return extract_lexical(graph, import_location->header);
}

RET_CRIFI_IMPORT crifi_execute_import(crifi_graph *graph,
		CLIPSValue *import_location, CLIPSValue *entailment_regime,
		CLIPSValue *values, int number_values)
{
	int process_err;
	char *import_location_str;

	ImportProcess *process;
	RET_CRIFI_IMPORT err = RET_CRIFI_IMPORT_UNHANDLED;
	CRIFIImportData *data = LoadingCRIFIImportData(graph);

	import_location_str = extract_import_location(graph, import_location);
	if(import_location_str == NULL){
		return RET_CRIFI_IMPORT_UNKNOWN_ERROR;
	}

	process = start_import_process(graph, entailment_regime);
	if (process == NULL){
		free(import_location_str);
		return RET_CRIFI_IMPORT_REJECTED_PROFILE;
	}

	for(CRIFISingleImportData *x = data->first; x != NULL; x = x->next){
		err = x->method(graph, process, import_location_str,
				values, number_values, x->context);
		if (err != RET_CRIFI_IMPORT_UNHANDLED){
			break;
		}
	}
	free(import_location_str);

	process_err = end_import_process(process);
	if (err != RET_CRIFI_IMPORT_NOERROR){
		return err;
	}
	switch (process_err){
		case 0:
			break;
		default:
			return RET_CRIFI_IMPORT_PROCESS_FAILED;
	}
	return RET_CRIFI_IMPORT_NOERROR;
}


int set_model_id_for_import(crifi_graph *graph, CRIFI_IMPORT_MODEL_ID model_id){
	CRIFIImportData *import_data = LoadingCRIFIImportData(graph);
	if (import_data == NULL) return 1;

	switch (model_id){
		case CRIFI_IMPORT_MODEL_SIMPLE:
		case CRIFI_IMPORT_MODEL_RIFGENERATOR:
		case CRIFI_IMPORT_MODEL_RIFGENERATOR_SIMPLE:
			import_data->model_id = model_id;
			break;
		default:
			return 2;
	}
	return 0;
}
