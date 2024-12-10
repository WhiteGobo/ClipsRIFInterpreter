#pragma once

#include <clips.h>
#include "ffi_clips_interface.h"


Environment *initEnvironment();
LoadError load_config_internal(Environment *env, const char *fileName);
bool load_config_internal_mem(Environment *env, const char* string_config, size_t string_length);

bool closeEnvironment(Environment *env);
CLIPSValue getFactsFromEnvironment(Environment *env);

CRI_RET_BUILDTRIPLE build_triple(Environment*, Utf8String subject, Utf8String predicate, Utf8String object, Utf8String context);
