#include "crifi_import_implementations.h"
#include "crifi_import.h"
#include "info_query.h"

struct data {
	FilepathImportidPair *importlocations;
	int number_importlocations;
	GetfileImportidPair *importmethods;
	int number_importmethods;
};

static RET_CRIFI_IMPORT myimportfunction(crifi_graph *graph,
		CLIPSValue *import_location, CLIPSValue *entailment_regime,
		CLIPSValue *values, int number_values, void *context){
	if (context == NULL) return RET_CRIFI_IMPORT_INVALIDCONTEXT;
	char *id = extract_uri(graph, import_location->header);
	char *entailment = extract_uri(graph, entailment_regime->header);
	if (entailment == NULL || id == NULL){
		free(entailment);
		free(id);
		return RET_CRIFI_BROKEN_ALGORITHM;
	}
	struct data *mydata = (struct data*) context;
	if (mydata->importlocations != NULL){
		for (int i = 0; i<mydata->number_importlocations; i++){
			if (0==strcmp(id, mydata->importlocations[i].id)){
				free(id);
				return RET_CRIFI_IMPORT_NOERROR;
			}
		}
	}
	if (mydata->importmethods != NULL){
		for (int i = 0; i<mydata->number_importmethods; i++){
			if (0==strcmp(id, mydata->importmethods[i].id)){
				free(id);
				return RET_CRIFI_IMPORT_NOERROR;
			}
		}
	}
	free(id);
	free(entailment);
	return RET_CRIFI_IMPORT_UNHANDLED;
}

static void cleanup_importlocation(FilepathImportidPair *data){
	free(data->id);
	free(data->filepath);
}

static void cleanup_importmethod(GetfileImportidPair *data){
	free(data->id);
}

static void mycleanupfunction(void *context){
	struct data *mydata = (struct data*) context;
	if (mydata->importlocations != NULL){
		for (int i = 0; i<mydata->number_importlocations; i++){
			cleanup_importlocation(mydata->importlocations + i);
		}
		free(mydata->importlocations);
	}
	if (mydata->importmethods != NULL){
		for (int i = 0; i<mydata->number_importmethods; i++){
			cleanup_importmethod(mydata->importmethods + i);
		}
		free(mydata->importmethods);
	}
	free(mydata);
}

bool add_importlocations(crifi_graph *graph, FilepathImportidPair *importlocations, GetfileImportidPair *importmethods){
	int err;
	int number_importlocations = 0;
	int number_importmethods = 0;
	FilepathImportidPair *importlocations_cpy = NULL;
	GetfileImportidPair *importmethods_cpy = NULL;
	if (importlocations != NULL){
		for(FilepathImportidPair *x = importlocations; x->id != NULL || x->filepath != NULL; x++){
			number_importlocations++;
		}
		importlocations_cpy = calloc(1 + number_importlocations,
						sizeof(FilepathImportidPair));
		for(int i=0; i<number_importlocations; i++){
			importlocations_cpy[i].id = calloc(strlen(importlocations[i].id) + 1, sizeof(char));
			strcpy(importlocations_cpy[i].id, importlocations[i].id);
			importlocations_cpy[i].filepath = calloc(strlen(importlocations[i].filepath) +1, sizeof(char));
			strcpy(importlocations_cpy[i].filepath, importlocations[i].filepath);
		}
	}
	if (importmethods != NULL){
		for(GetfileImportidPair *x = importmethods; x->id != NULL || x->method != NULL; x++){
			number_importmethods++;
		}
		importmethods_cpy = calloc(1 + number_importmethods,
						sizeof(GetfileImportidPair));
		for(int i=0; i<number_importmethods; i++){
			importmethods_cpy[i].id = calloc(strlen(importmethods[i].id) + 1, sizeof(char));
			strcpy(importmethods_cpy[i].id, importmethods[i].id);
			importmethods_cpy[i].method = importmethods[i].method;
			importmethods_cpy[i].context = importmethods[i].context;
			importmethods_cpy[i].cleanup = importmethods[i].cleanup;
		}
	}
	struct data* mydata = malloc(sizeof(struct data));
	mydata->importlocations = importlocations_cpy;
	mydata->number_importlocations = number_importlocations;
	mydata->importmethods = importmethods_cpy;
	mydata->number_importmethods = number_importmethods;

	err = crifi_add_import_function(graph, myimportfunction, mydata, mycleanupfunction);
	return err == 0;
}
