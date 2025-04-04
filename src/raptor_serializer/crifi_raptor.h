/*
 * Public interface of crifi_raptor
 */
#pragma once

#include <ffi_clips_interface.h>
#include <raptor.h>
#include "clips_script_serializer.h"

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

typedef enum {
	CRIFI_PARSE_NOERROR = 0,
	CRIFI_PARSE_INITERROR,
	CRIFI_PARSE_BASEERROR,
	CRIFI_PARSE_TERM_CONVERT,
	CRIFI_PARSE_SYNTAX_ERROR,
	///Throw when parser in progress returns error
	CRIFI_PARSE_PARSING_ERROR,
	CRIFI_PARSE_UNKNOWN
} CRIFI_PARSE_RET;

typedef enum {
	//No error
	CRIFI_SERIALIZE_SCRIPT_NOERROR = 0,
	CRIFI_SERIALIZE_MALLOC_ERROR,
	CRIFI_SERIALIZE_BROKEN_GRAPH,
	CRIFI_SERIALIZE_SCRIPT_CANT_CREATE_NODE,
	CRIFI_SERIALIZE_SCRIPT_CANT_CREATE_STRUCTS,
	CRIFI_SERIALIZE_SCRIPT_UNHANDLED_PREDICATE,
	CRIFI_SERIALIZE_SCRIPT_SUBJECT,
	CRIFI_SERIALIZE_SCRIPT_PREDICATE,
	CRIFI_SERIALIZE_SCRIPT_FAILED_ADDING_NEW_NODE,
	CRIFI_SERIALIZE_SCRIPT_OBJECT,
	//Input has void pointer
	CRIFI_SERIALIZE_SCRIPT_INPUT,
	CRIFI_SERIALIZE_SCRIPT_UNKNOWN
} CRIFI_SERIALIZE_SCRIPT_RET;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Serialize all triples in crifi_graph to RDF. 
 * Supports only default formats from raptor.
 */
CRIFI_SERIALIZE_RET crifi_serialize_all_triples(crifi_graph* graph,
					FILE *filehandle,
					const char* format, const char* base);

/**
 * Parse rdf graph and assert triples in crifi_graph.
 * Supports only default formats from raptor.
 */
CRIFI_PARSE_RET crifi_parse_to_triples(crifi_graph* graph,
					FILE *filehandle,
					const char* format, const char* base);

/**
 * For valid syntax_uri see `https://www.w3.org/ns/formats/`_
 */
CRIFI_PARSE_RET crifi_parse(raptor_statement_handler assert_triple_handler,
					void *assert_triple_context,
					FILE *filehandle, const char *filepath,
					const char* syntax_uri, const char* base);

CRIFI_SERIALIZE_SCRIPT_RET serialize_information_as_clips_script(FILE* stream, crifi_graph* graph);

CRIFI_SERIALIZE_SCRIPT_RET serialize_information_as_clips_function(FILE* stream, crifi_graph* graph);

#ifdef __cplusplus
} //extern "C"
#endif
