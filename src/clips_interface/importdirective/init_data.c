#include <clips.h>
#include "crifi_import.h"
#include "ffi_constants.h"

static void release_crifi_importdata(Environment *env);
static void free_crifi_importdata(CRIFIImportData *data);
static bool initialize_crifi_importdata(CRIFIImportData *data);

/**
 * method given at registration for tidying up import data after Environment is
 * freed
 */
static void release_crifi_importdata(Environment *env){
	free_crifi_importdata(LoadingCRIFIImportData(env));
}

bool crifi_importdata_register_data(crifi_graph *graph){
	if (! AllocateEnvironmentData(graph, CRIFI_IMPORT_DATA_INDEX,
						sizeof(CRIFIImportData),
						release_crifi_importdata))
	{
		Writeln(graph, "Internal error 0. "
				"Cant load plugin for crifi_import.");
		ExitRouter(graph, EXIT_FAILURE);
		return false;
	}
	if(!initialize_crifi_importdata(LoadingCRIFIImportData(graph))){
		return false;
	}
	return true;
}

static bool initialize_crifi_importdata(CRIFIImportData *data){
	int err;
	data->first = NULL;
	data->model_id = CRIFI_IMPORT_MODEL_SIMPLE;
	return true;
}

static void free_crifi_importdata(CRIFIImportData *data){
	if (data->first != NULL){
		free_crifi_singleimportdata(data->first);
	}
}
