#include "rdf_to_rif_interpretation.h"

ImportProcess *start_import_process_rdf_to_rif_interpretation(
				crifi_graph *graph,
				CRIFI_IMPORT_INTERPRETER_ID interpreter_id)
{
	ImportProcess *process = malloc(sizeof(ImportProcess));
	process->graph = graph;
	process->interpreter_id = interpreter_id;
	process->bnode_lookup = new_bnodelookup();
	return process;
}

int end_import_process_rdf_to_rif_interpretation(ImportProcess *process){
	if (process == NULL){
		return 1;
	}
	free_bnodelookup(process->bnode_lookup);
	free(process);
	return 0;
}

CRIFI_IMPORT_ASSERT_RET assert_frame_rdf_to_rif(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	printf("failing to assert frame qwertz\n");
	return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
}
