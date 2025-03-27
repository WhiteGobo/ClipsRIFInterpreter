#pragma once

#include <ffi_clips_interface.h>

#ifndef CRIFI_IMPORT_DATA_INDEX
#define CRIFI_IMPORT_DATA_INDEX USER_ENVIRONMENT_DATA + 3
#endif


typedef enum {
	RET_CRIFI_IMPORT_UNHANDLED = -1,
	RET_CRIFI_IMPORT_NOERROR = 0,
	RET_CRIFI_IMPORT_INVALIDCONTEXT,
	///if a CRIFIImportMethod was called with broken inputs.
	RET_CRIFI_BROKEN_ALGORITHM,
	///If inputdata cant imported because of its interpretation
	RET_CRIFI_IMPORT_REJECTED_PROFILE,
	RET_CRIFI_IMPORT_COULDNT_LOCATE_SOURCE,
	RET_CRIFI_IMPORT_PROCESS_FAILED
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
	CLIPSValue *interpretation;
} CRIFIImportData;

typedef struct importProcess ImportProcess;


/** LoadingCRIFIImportData
 */
#define LoadingCRIFIImportData(theEnv) \
	((struct crifiImportData *) GetEnvironmentData(theEnv, CRIFI_IMPORT_DATA_INDEX))


#ifdef __cplusplus
extern "C" {
#endif

bool crifi_importdata_register_data(crifi_graph *graph);

/**
 * The returned uri in cv identifies which interpretation is used in graph.
 * This is needed to determine, how to import from other RIF documents
 * or non-RIF documents, like eg RDF graphs or OWL onthologies.
 */
int get_interpretation_id(crifi_graph *graph, CLIPSValue *cv);

int crifi_add_import_function(crifi_graph *graph,
		CRIFIImportMethod *method,
		void *context,
		CRIFIImportDataCleanupFunction *cleanup_function);

void free_crifi_singleimportdata(CRIFISingleImportData *data);

ImportProcess *start_import_process(crifi_graph *graph, CLIPSValue *input_interpretation);
int end_import_process(ImportProcess *process);

RET_CRIFI_IMPORT crifi_execute_import(crifi_graph *graph, CLIPSValue *import_location, CLIPSValue *entailment_regime, CLIPSValue *values, int number_values);

#ifdef __cplusplus
}
#endif
