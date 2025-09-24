#pragma once

#include "ffi_clips_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

crifi_graph *init_graph_stable_model();

crifi_graph *init_graph_modelA();

crifi_graph *init_graph_modelcheckA();

crifi_graph *init_graph_model_first();

void crifi_graph_debug_set_random_strategy(crifi_graph * graph, int seed);

#ifdef __cplusplus
} //extern "C"
#endif
