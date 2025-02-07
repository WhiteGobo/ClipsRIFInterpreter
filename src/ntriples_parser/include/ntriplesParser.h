/** \file ntriplesParser.h
 * For more information see `https://www.w3.org/TR/n-triples/`_
 */

#pragma once
#ifndef _NTRIPLESPARSER_H_
#define _NTRIPLESPARSER_H_

#include <stdio.h>
#include <ffi_clips_interface.h>

#ifndef __cplusplus
#ifndef public
#define public
#endif //public
#define NTRIPLESPARSER_INTERFACE public
#else
#define NTRIPLESPARSER_INTERFACE
#endif //__cplusplus

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	NTP_NO_ERROR = 0,
	NTP_PARSE_ERROR = 1,
	NTP_INTERNAL_ERROR = 2,
	NTP_INPUT_ERROR = 3,
} RET_NTRIPLESPARSE;

/**
 * parse ntriples from string and directly assert facts.
 * Use free_linked_list after usage.
 */
NTRIPLESPARSER_INTERFACE RET_NTRIPLESPARSE ntriples_parse(
		crifi_graph* graph,
		const char *input, size_t length, int debug);

/**
 * parse ntriples from file and directly assert facts.
 */
NTRIPLESPARSER_INTERFACE RET_NTRIPLESPARSE ntriples_parse_f(
		crifi_graph* graph,
		FILE *input, int debug);

/**
 * parse ntriples from string and returns them as factlist
 */
//NTRIPLESPARSER_INTERFACE RET_NTRIPLESPARSE ntriples_parse_triples(
//		struct TriplesLinkedList** triplepointer,
//		const char *input, size_t length);

/**
 * parse ntriples from file and returns them as factlist
 */
NTRIPLESPARSER_INTERFACE struct TriplesLinkedList* ntriples_parse_triples_f(
		FILE *input, int debug);

#ifdef __cplusplus
}
#endif

#endif // _NTRIPLESPARSER_H_
