#pragma once

#include "rdf_to_rif_interpretation.h"
#include "clipsvalue_interface.h"
#include "interpretations.h"

struct rdfToRifInfo* generate_rdf_rif_info(crifi_graph *graph);
void free_rdf_rif_info(struct rdfToRifInfo *info);
