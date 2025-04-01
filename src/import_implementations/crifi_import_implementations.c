#include "crifi_import_implementations.h"
#include "crifi_import.h"
#include "info_query.h"
#include "import_from_file.h"

struct data {
	FilepathImportidPair *importlocations;
	int number_importlocations;
	GetfileImportidPair *importmethods;
	int number_importmethods;
};

static RET_CRIFI_IMPORT myimportfunction(crifi_graph *graph,
		ImportProcess *process, const char *import_location,
		CLIPSValue *values, int number_values, void *context){
	const char *filepath;
	GetfileImportidPair *tmpmethod;
	RET_CRIFI_IMPORT import_err;
	char *id = import_location;
	struct data *mydata = (struct data*) context;
	FILE *f = NULL;
	if (context == NULL) return RET_CRIFI_IMPORT_INVALIDCONTEXT;
	if (mydata->importlocations != NULL){
		for (int i = 0; i<mydata->number_importlocations; i++){
			if (0==strcmp(id, mydata->importlocations[i].id)){
				filepath = mydata->importlocations[i].filepath;
				char *syntax_uri = mydata->importlocations[i].syntax;
				f = fopen(filepath, "r");
				if (f != NULL){

					import_err = import_data_from_file(
							graph, f, filepath,
							process,
							syntax_uri);
					fclose(f);
				} else {
					import_err = RET_CRIFI_IMPORT_COULDNT_LOCATE_SOURCE;
				}
				free(id);
				return import_err;
			}
		}
	}
	if (mydata->importmethods != NULL){
		for (int i = 0; i<mydata->number_importmethods; i++){

			tmpmethod = mydata->importmethods + i;
			if (0==strcmp(id, tmpmethod->id)){
				f = tmpmethod->method(tmpmethod->context);
				if (f != NULL){

					import_err = import_data_from_file(
							graph, f,
							tmpmethod->id,
							process,
							tmpmethod->syntax);
					fclose(f);
				} else {
					import_err = RET_CRIFI_IMPORT_COULDNT_LOCATE_SOURCE;
				}
				free(id);
				return import_err;
			}
		}
	}
	free(id);
	return RET_CRIFI_IMPORT_UNHANDLED;
}

static void cleanup_importlocation(FilepathImportidPair *data){
	free(data->id);
	free(data->filepath);
	free(data->syntax);
}

static void cleanup_importmethod(GetfileImportidPair *data){
	free(data->id);
	free(data->syntax);
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

bool add_importlocations(crifi_graph *graph,
		FilepathImportidPair *importlocations,
		GetfileImportidPair *importmethods){
	int err;
	int number_importlocations = 0;
	int number_importmethods = 0;
	FilepathImportidPair *importlocations_cpy = NULL;
	GetfileImportidPair *importmethods_cpy = NULL;
	if (importlocations != NULL){
		for(FilepathImportidPair *x = importlocations;
				x->id != NULL || x->filepath != NULL;
				x++)
		{
			number_importlocations++;
		}
		importlocations_cpy = calloc(1 + number_importlocations,
						sizeof(FilepathImportidPair));
		for(int i=0; i<number_importlocations; i++){
			importlocations_cpy[i].id = calloc(strlen(importlocations[i].id) + 1, sizeof(char));
			strcpy(importlocations_cpy[i].id, importlocations[i].id);
			importlocations_cpy[i].filepath = calloc(strlen(importlocations[i].filepath) +1, sizeof(char));
			strcpy(importlocations_cpy[i].filepath, importlocations[i].filepath);
			importlocations_cpy[i].syntax = calloc(strlen(importlocations[i].syntax) +1, sizeof(char));
			strcpy(importlocations_cpy[i].syntax, importlocations[i].syntax);
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
			importmethods_cpy[i].syntax = calloc(strlen(importmethods[i].syntax) +1, sizeof(char));
			strcpy(importmethods_cpy[i].syntax, importmethods[i].syntax);
		}
	}
	struct data* mydata = malloc(sizeof(struct data));
	mydata->importlocations = importlocations_cpy;
	mydata->number_importlocations = number_importlocations;
	mydata->importmethods = importmethods_cpy;
	mydata->number_importmethods = number_importmethods;

	err = crifi_add_import_function(graph, myimportfunction, mydata,
					mycleanupfunction);
	return err == 0;
}
