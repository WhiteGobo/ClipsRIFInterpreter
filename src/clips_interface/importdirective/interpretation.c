#include "crifi_import.h"
#include "interpretations.h"


int get_interpretation_id(crifi_graph *graph, CLIPSValue *cv){
	cv->voidValue = VoidConstant(graph);
	return 1;
}


ImportProcess *start_import_process(crifi_graph *graph, CLIPSValue *input_interpretation){
	ImportProcess *process = malloc(sizeof(ImportProcess));
	return process;
}

int end_import_process(ImportProcess *process){
	if (process == NULL){
		return 1;
	}
	free(process);
	return 0;
}
