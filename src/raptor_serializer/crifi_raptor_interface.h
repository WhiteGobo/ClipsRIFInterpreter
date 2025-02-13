#pragma once

#include <ffi_clips_interface.h>
#include <raptor.h>

#ifdef __cplusplus
extern "C" {
#endif

raptor_term* clipsvalue_to_raptorterm(raptor_world *world, crifi_graph* graph, CLIPSValue val);

#ifdef __cplusplus
} //extern "C"
#endif
