#pragma once

#include <ffi_clips_interface.h>

#ifdef __cplusplus
extern "C" {
#endif

void fprint_activities_per_rule(FILE* out, crifi_graph* graph);

#ifdef __cplusplus
} //extern "C"
#endif
