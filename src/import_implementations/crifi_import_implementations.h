#pragma once

#include <ffi_clips_interface.h>
#include "crifi_raptor.h"

typedef struct filepath_importid_pair {
	char *id;
	char *filepath;
} FilepathImportidPair;

typedef FILE* GetFileMethod(void *context);
typedef void CleanupGetFileMethodContext(void *context);

typedef struct getfile_importid_pair {
	char *id;
	GetFileMethod *method;
	void *context;
	CleanupGetFileMethodContext *cleanup;
} GetfileImportidPair;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Loads methods and locations so that new resources can be imported via the
 * given id.
 * All given ids can be loaded via crifi:import and within the default rif
 * entailment regimes. Loading is done via raptor.
 *
 * importlocations and importmethods can be NULL or a list terminated
 * with an element, which id is NULL.
 */
bool add_importlocations(crifi_graph *graph, FilepathImportidPair *importlocations, GetfileImportidPair *importmethods);

#ifdef __cplusplus
} //extern "C"
#endif
