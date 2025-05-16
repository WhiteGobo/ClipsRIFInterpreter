#pragma once

#include "crifi_import.h"

/**
 * assert only special triples and returns CRIFI_IMPORT_ASSERT_UNHANDLED_TRIPLE
 * on unsupported triple.
 */
CRIFI_IMPORT_ASSERT_RET simpletoowl_special_assert_triple(
		ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type);
