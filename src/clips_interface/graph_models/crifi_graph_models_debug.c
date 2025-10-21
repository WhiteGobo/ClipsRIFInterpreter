#include "crifi_graph_models.h"
#include "crifi_import.h"

void crifi_graph_debug_set_random_strategy(crifi_graph* graph, int seed){
	struct DynamicValue retval;
	char seedcmd[50];
	sprintf(seedcmd, "(seed %d)", seed);
	retval = eval(graph, seedcmd);
	free_dynamic_value(retval);
	retval = eval(graph, "(set-strategy random)");
	free_dynamic_value(retval);
}
