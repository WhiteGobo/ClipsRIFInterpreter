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
	RET_CRIFI_IMPORT_PROCESS_FAILED,
	//Return this if assert_frame failed unexpectedly.
	RET_CRIFI_IMPORT_ASSERT_FRAME_FAILED,
	///Return on unhandled problem
	RET_CRIFI_IMPORT_UNKNOWN_ERROR
	
} RET_CRIFI_IMPORT;

typedef enum {
	CRIFI_IMPORT_TERM_URI,
	CRIFI_IMPORT_TERM_BNODE,
	CRIFI_IMPORT_TERM_TYPEDLITERAL,
	CRIFI_IMPORT_TERM_LANGLITERAL,
	CRIFI_IMPORT_TERM_UNKNOWN
} IMPORT_TERM_TYPE;

typedef enum {
	CRIFI_IMPORT_ASSERT_NOERROR = 0,
	CRIFI_IMPORT_ASSERT_INVALID_TERM,
	CRIFI_IMPORT_ASSERT_UNHANDLED_TRIPLE,
	CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR
} CRIFI_IMPORT_ASSERT_RET;

typedef enum {
	CRIFI_IMPORT_MODEL_UNDEFINED = -1,
	///type of _CRIFI_MODEL_SIMPLE_
	CRIFI_IMPORT_MODEL_SIMPLE=0,
	///type of _CRIFI_MODEL_RIFGENERATOR_ Is subtype to owl
	CRIFI_IMPORT_MODEL_RIFGENERATOR=1,
	CRIFI_IMPORT_MODEL_RIFGENERATOR_SIMPLE=2
} CRIFI_IMPORT_MODEL_ID;

typedef struct importProcess ImportProcess;

typedef void CRIFIImportDataCleanupFunction(void *context);
typedef RET_CRIFI_IMPORT CRIFIImportMethod(crifi_graph *graph,
		ImportProcess *process, const char *import_location,
		CLIPSValue *values, int number_values, void *context);

typedef struct crifiSingleImportData {
	CRIFIImportMethod *method;
	void *context;
	CRIFIImportDataCleanupFunction *cleanup_function;
	struct crifiSingleImportData *next;
} CRIFISingleImportData;

typedef struct crifiImportData{
	CRIFISingleImportData *first;
	CRIFI_IMPORT_MODEL_ID model_id;
} CRIFIImportData;



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
		const void *context,
		CRIFIImportDataCleanupFunction *cleanup_function);

void free_crifi_singleimportdata(CRIFISingleImportData *data);

int set_model_id_for_import(crifi_graph *graph, CRIFI_IMPORT_MODEL_ID model_id);

/**
 * TODO: rename input_interpretation to input_entailment
 */
ImportProcess *start_import_process(crifi_graph *graph, CLIPSValue *input_interpretation);

int end_import_process(ImportProcess *process);
CRIFI_IMPORT_ASSERT_RET crifi_import_assert_frame(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type
		);
CRIFI_IMPORT_ASSERT_RET crifi_import_assert_member(ImportProcess *process,
		const char *instance, const char *instance_suffix,
		IMPORT_TERM_TYPE instance_type,
		const char *cls, const char *cls_suffix,
		IMPORT_TERM_TYPE cls_type);

CRIFI_IMPORT_ASSERT_RET crifi_import_assert_subclass(ImportProcess *process,
		const char *sub, const char *sub_suffix,
		IMPORT_TERM_TYPE sub_type,
		const char *super, const char *super_suffix,
		IMPORT_TERM_TYPE super_type);


RET_CRIFI_IMPORT crifi_execute_import(crifi_graph *graph, CLIPSValue *import_location, CLIPSValue *entailment_regime, CLIPSValue *values, int number_values);

#ifdef __cplusplus
}
#endif
