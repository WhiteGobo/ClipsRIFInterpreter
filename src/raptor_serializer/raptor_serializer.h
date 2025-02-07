#pragma once

#include <ffi_clips_interface.h>
#include <raptor.h>

typedef enum {
	//No error
	CRIFI_SERIALIZE_NOERROR = 0,
	//Format cant be NULL
	CRIFI_SERIALIZE_MISSING_FORMAT,
	//Base cant be NULL
	CRIFI_SERIALIZE_MISSING_BASE,
	//Couldnt transform all terms
	CRIFI_SERIALIZE_TERM
} CRIFI_SERIALIZE_RET;

#ifdef __cplusplus
extern "C" {
#endif

CRIFI_SERIALIZE_RET crifi_serialize_all_triples(crifi_graph* graph,
					FILE *filehandle,
					const char* format, const char* base);

#ifdef __cplusplus
} //extern "C"
#endif
