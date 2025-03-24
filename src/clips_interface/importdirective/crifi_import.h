#pragma once

#include <ffi_clips_interface.h>

#ifndef CRIFI_IMPORT_DATA_INDEX
#define CRIFI_IMPORT_DATA_INDEX USER_ENVIRONMENT_DATA + 3
#endif

typedef struct crifiSingleImportData {
	struct crifiSingleImportData *next;
} CRIFISingleImportData;

typedef struct crifiImportData{
	CRIFISingleImportData *first;
} CRIFIImportData;


/** LoadingCRIFIImportData
 */
#define LoadingCRIFIImportData(theEnv) \
	((struct crifiImportData *) GetEnvironmentData(theEnv, CRIFI_IMPORT_DATA_INDEX))


#ifdef __cplusplus
extern "C" {
#endif

bool crifi_importdata_register_data(crifi_graph *graph);

int crifi_add_import_function(crifi_graph *graph);
void free_crifi_singleimportdata(CRIFISingleImportData *data);

#ifdef __cplusplus
}
#endif
