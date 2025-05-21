#pragma once
#include "crifi_import.h"

typedef struct tripleList {
	char *object;
	char *object_suffix;
	IMPORT_TERM_TYPE object_type;
	char *slotkey;
	char *slotkey_suffix;
	IMPORT_TERM_TYPE slotkey_type;
	char *slotvalue;
	char *slotvalue_suffix;
	IMPORT_TERM_TYPE slotvalue_type;
	struct tripleList *next;
} TripleList;


/**
 * returns appended triple. Is first triple if first == NULL.
 */
TripleList* crifi_import_append_triple(TripleList* first,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type);

void crifi_import_free_TripleList(TripleList* first);
