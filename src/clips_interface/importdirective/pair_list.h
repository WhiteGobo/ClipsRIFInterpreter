#pragma once
#include "crifi_import.h"

typedef struct pairList {
	char *left;
	char *left_suffix;
	IMPORT_TERM_TYPE left_type;
	char *second;
	char *second_suffix;
	IMPORT_TERM_TYPE second_type;
	struct pairList *next;
} PairList;


/**
 * returns appended pair. Is first pair if first == NULL.
 */
PairList* crifi_import_append_pair(PairList* first,
		const char *left, const char *left_suffix,
		IMPORT_TERM_TYPE left_type,
		const char *second, const char *second_suffix,
		IMPORT_TERM_TYPE second_type);

void crifi_import_free_PairList(PairList* first);
