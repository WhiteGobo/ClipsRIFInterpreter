#pragma once

#include <ffi_clips_interface.h>

#ifndef CRIFI_IMPORT_DATA_INDEX
#define CRIFI_IMPORT_DATA_INDEX USER_ENVIRONMENT_DATA + 3
#endif


typedef enum {
	RET_CRIFI_IMPORT_UNHANDLED = -1,
	RET_CRIFI_IMPORT_NOERROR = 0,
} RET_CRIFI_IMPORT;

typedef void CRIFIImportDataCleanupFunction(void *context);
typedef RET_CRIFI_IMPORT CRIFIImportMethod(crifi_graph *graph,
		CLIPSValue *import_location, CLIPSValue *entailment_regime,
		CLIPSValue *values, int number_values, void *context);

typedef struct crifiSingleImportData {
	CRIFIImportMethod *method;
	void *context;
	CRIFIImportDataCleanupFunction *cleanup_function;
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

int crifi_add_import_function(crifi_graph *graph,
		CRIFIImportMethod *method,
		void *context,
		CRIFIImportDataCleanupFunction *cleanup_function);

void free_crifi_singleimportdata(CRIFISingleImportData *data);

RET_CRIFI_IMPORT crifi_execute_import(crifi_graph *graph, CLIPSValue *import_location, CLIPSValue *entailment_regime, CLIPSValue *values, int number_values);

#ifdef __cplusplus
}
#endif
