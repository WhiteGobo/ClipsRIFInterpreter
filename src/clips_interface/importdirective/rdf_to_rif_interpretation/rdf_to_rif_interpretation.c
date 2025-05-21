#include "rdf_to_rif_interpretation.h"
#include "clipsvalue_interface.h"
#include "rdf_to_rif_commondata.h"
#include "rdf_to_rif_assertion_strategies.h"

static int assert_base_information(ImportProcess *process);
static int transfer_rest_triples(TripleList *first, ImportProcess *process);


ImportProcess *start_import_process_rdf_to_rif_interpretation(
				crifi_graph *graph,
				CRIFI_IMPORT_INTERPRETER_ID interpreter_id)
{
	ImportProcess *process = malloc(sizeof(ImportProcess));
	process->graph = graph;
	process->interpreter_id = interpreter_id;
	process->rdf_to_rif_info = generate_rdf_rif_info(graph);
	if (process->rdf_to_rif_info == NULL){
		free(process);
		return NULL;
	}

	return process;
}


int end_import_process_rdf_to_rif_interpretation(ImportProcess *process){
	int err = 0, err2;
	RdfToRifInfo *info = process->rdf_to_rif_info;
	if (process == NULL){
		return 1;
	}
	err2 = transfer_rest_triples(info->first_triple, process);

	err = assert_base_information(process);
	free_rdf_rif_info(process->rdf_to_rif_info);
	free(process);
	switch(err2){
		case 0:
			break;
		default:
			return 1;
	}
	return err;
}



#define ASSERT_TRIPLE_BASE(process, s_cv, p_cv, o_cv) \
	if ( CRIFI_ASSTR_NO_ERROR != assert_triple(process->graph, s_cv, p_cv, o_cv)){ \
		return 1;\
	}
#define ASSERT_MEMBER_BASE(process, s_cv, o_cv) \
	if ( CRIFI_ASSTR_NO_ERROR != assert_member(process->graph, s_cv, o_cv)){ \
		return 1;\
	}
static int assert_base_information(ImportProcess *process){
	CLIPSValue *document = &(process->rdf_to_rif_info->document);
	CLIPSValue *group = &(process->rdf_to_rif_info->group);
	CLIPSValue *rule_list = &(process->rdf_to_rif_info->rule_list);
	CLIPSValue *rif_payload = &(process->rdf_to_rif_info->rif_payload);
	CLIPSValue *rif_sentences = &(process->rdf_to_rif_info->rif_sentences);
	CLIPSValue *rif_Document = &(process->rdf_to_rif_info->rif_Document);
	CLIPSValue *rif_Group = &(process->rdf_to_rif_info->rif_Group);
	ASSERT_TRIPLE_BASE(process, document, rif_payload, group);
	ASSERT_MEMBER_BASE(process, document, rif_Document);
	ASSERT_TRIPLE_BASE(process, group, rif_sentences, rule_list);
	ASSERT_MEMBER_BASE(process, group, rif_Group);
	return 0;
}
#undef ASSERT_TRIPLE_BASE
#undef ASSERT_MEMBER_BASE


static int transfer_rest_triples(TripleList *first, ImportProcess *process){
	CRIFI_IMPORT_ASSERT_RET err;
	if (first == NULL) return 0;
	for (TripleList *x = first;
			x != NULL;
			x = x->next)
	{
		err = assert_triple_rdf_to_rif(process,
				x->object, x->object_suffix, x->object_type,
				x->slotkey, x->slotkey_suffix, x->slotkey_type,
				x->slotvalue, x->slotvalue_suffix,
				x->slotvalue_type);
		switch(err){
			case CRIFI_IMPORT_ASSERT_NOERROR:
				break;
			case CRIFI_IMPORT_ASSERT_INVALID_TERM:
				fprintf(stderr, "invalid term\n");
				return 1;
			case CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR:
			default:
				fprintf(stderr, "unknown assert error\n");
				return 1;
		}
	}
	return 0;
}
