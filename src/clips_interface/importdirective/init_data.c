#include <clips.h>
#include "crifi_import.h"

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

bool crifi_importdata_register_data(Environment *env){
	if (! AllocateEnvironmentData(env, CRIFI_IMPORT_DATA_INDEX,
						sizeof(CRIFIImportData),
						release_crifi_importdata))
	{
		Writeln(env, "Internal error 0. "
				"Cant load plugin for crifi_import.");
		ExitRouter(env, EXIT_FAILURE);
		return false;
	}
	if(!initialize_crifi_importdata(LoadingCRIFIImportData(env))){
		return false;
	}
	return true;
}

static bool initialize_crifi_importdata(CRIFIImportData *data){
	int err;
	return true;
}

static void free_crifi_importdata(CRIFIImportData *data){
}
