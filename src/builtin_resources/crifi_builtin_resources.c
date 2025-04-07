#include "crifi_builtin_resources.h"

//implements modelA_add_importlocations
#include "modeldata_as_header_modelA.h"

bool add_builtin_resources(crifi_graph *graph){
	return modelA_add_importlocations(graph);
}
