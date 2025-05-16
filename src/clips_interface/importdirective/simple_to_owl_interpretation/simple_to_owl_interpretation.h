#pragma once

#include "crifi_import.h"
#include "interpretations.h"
#include "info_query.h"

ImportProcess *start_import_process_simple_to_owl_interpretation(crifi_graph *graph);
int end_import_process_simple_to_owl_interpretation(ImportProcess *process);

CRIFI_IMPORT_ASSERT_RET assert_frame_simple_to_owl(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type);
