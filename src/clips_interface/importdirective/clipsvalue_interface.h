#pragma once

#include "crifi_import.h"
#include "bnode_lookup.h"

int value_suffix_to_clipsvalue(
		ImportProcess *process, ClipsvalueRetriever *node_lookup,
		const char *value, const char *suffix, IMPORT_TERM_TYPE type,
		CLIPSValue *retval);
