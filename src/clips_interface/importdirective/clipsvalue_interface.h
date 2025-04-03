#pragma once

#include "crifi_import.h"

int value_suffix_to_clipsvalue(ImportProcess *process,
		const char *value, const char *suffix, IMPORT_TERM_TYPE type,
		CLIPSValue *retval);
