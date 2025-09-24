#include "crifi_graph_models.h"
#include "crifi_import.h"

void crifi_graph_debug_set_random_strategy(crifi_graph* graph, int seed){
	char seedcmd[50];
	sprintf(seedcmd, "(seed %d)", seed);
	eval(graph, seedcmd);
	eval(graph, "(set-strategy random)");
}
