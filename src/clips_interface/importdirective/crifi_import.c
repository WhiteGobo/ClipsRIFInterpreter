#include "crifi_import.h"

int crifi_add_import_function(crifi_graph *graph,
		CRIFIImportMethod *method,
		void *context,
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


RET_CRIFI_IMPORT crifi_execute_import(crifi_graph *graph, CLIPSValue *import_location, CLIPSValue *entailment_regime, CLIPSValue *values, int number_values){
	RET_CRIFI_IMPORT err = RET_CRIFI_IMPORT_UNHANDLED;
	CRIFIImportData *data = LoadingCRIFIImportData(graph);
	for(CRIFISingleImportData *x = data->first; x != NULL; x = x->next){
		err = x->method(graph, import_location, entailment_regime,
				values, number_values, x->context);
		if (err != RET_CRIFI_IMPORT_UNHANDLED){
			return err;
		}
	}
	return err;
}


int set_model_id_for_import(crifi_graph *graph, CRIFI_IMPORT_MODEL_ID model_id){
	CRIFIImportData *import_data = LoadingCRIFIImportData(graph);
	if (import_data == NULL) return 1;
	switch (model_id){
		case CRIFI_IMPORT_MODEL_SIMPLE:
		case CRIFI_IMPORT_MODEL_RIFGENERATOR:
			import_data->model_id = model_id;
			break;
		default:
			return 2;
	}
	return 0;
}
