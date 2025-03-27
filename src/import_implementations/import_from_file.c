#include "crifi_import.h"

RET_CRIFI_IMPORT import_data_from_file(crifi_graph *graph, FILE *inputfile){
	int err = 0;
	ImportProcess *process;
	CLIPSValue inputinterpretation = {.voidValue = VoidConstant(graph)};

	process = start_import_process(graph, &inputinterpretation);
	if (process == NULL){
		return RET_CRIFI_IMPORT_REJECTED_PROFILE;
	}
	err = end_import_process(process);
	if (err != 0){
		return RET_CRIFI_IMPORT_PROCESS_FAILED;
	}
	return RET_CRIFI_IMPORT_NOERROR;
}
