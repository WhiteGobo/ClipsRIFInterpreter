#include "crifi_import.h"

int crifi_add_import_function(crifi_graph *graph){
	CRIFISingleImportData *next;
	CRIFIImportData *data = LoadingCRIFIImportData(graph);
	CRIFISingleImportData **saveposition = &(data->first);
	while(*saveposition == NULL){
		saveposition = &(saveposition[0]->next);
	}
	next = malloc(sizeof(CRIFISingleImportData));
	if (next == NULL){
		return 1;
	}
	next->next = NULL;

	*saveposition = next;
	return 0;
}

void free_crifi_singleimportdata(CRIFISingleImportData *data){
	CRIFISingleImportData *tmp;
	CRIFISingleImportData *next = data;
	while (next != NULL){
		tmp = next->next;
		free(next);
		next = tmp;
	}
}
