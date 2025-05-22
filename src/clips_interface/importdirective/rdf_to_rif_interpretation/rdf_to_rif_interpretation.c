#include "rdf_to_rif_interpretation.h"
#include "clipsvalue_interface.h"
#include "rdf_to_rif_commondata.h"
#include "rdf_to_rif_assertion_strategies.h"
#include "rdf_to_rif_special_assert.h"
#include "crifi_lists.h"

static int assert_base_information(ImportProcess *process);
static int transfer_rest_triples(TripleList *first, ImportProcess *process);
static int transfer_members(PairList *first, ImportProcess *process);
static int transfer_subclass(PairList *first, ImportProcess *process);


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
	int err = 0;
	RdfToRifInfo *info = process->rdf_to_rif_info;
	if (process == NULL){
		return 1;
	}
	switch(transfer_rest_triples(info->first_triple, process)){
		case 0:
			break;
		default:
			free_rdf_rif_info(process->rdf_to_rif_info);
			free(process);
			return 1;
	}
	switch(transfer_members(info->first_member, process)){
		case 0:
			break;
		default:
			free_rdf_rif_info(process->rdf_to_rif_info);
			free(process);
			return 1;
	}
	switch(transfer_subclass(info->first_subclass, process)){
		case 0:
			break;
		default:
			free_rdf_rif_info(process->rdf_to_rif_info);
			free(process);
			return 1;
	}

	err = assert_base_information(process);
	free_rdf_rif_info(process->rdf_to_rif_info);
	free(process);
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
	RdfToRifInfo* info = process->rdf_to_rif_info;
	CLIPSValue *document = &(info->document);
	CLIPSValue *group = &(process->rdf_to_rif_info->group);
	CLIPSValue rule_list;
	CLIPSValue* rules;
	int number_rules;
	CLIPSValue *rif_payload = &(process->rdf_to_rif_info->rif_payload);
	CLIPSValue *rif_sentences = &(process->rdf_to_rif_info->rif_sentences);
	CLIPSValue *rif_Document = &(process->rdf_to_rif_info->rif_Document);
	CLIPSValue *rif_Group = &(process->rdf_to_rif_info->rif_Group);

	rules = cv_snake_to_list(info->rule_list, &number_rules);
	if(0 != crifi_list_new(process->graph, rules, number_rules, &rule_list))
	{
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}

	ASSERT_TRIPLE_BASE(process, document, rif_payload, group);
	ASSERT_MEMBER_BASE(process, document, rif_Document);
	ASSERT_TRIPLE_BASE(process, group, rif_sentences, &rule_list);
	ASSERT_MEMBER_BASE(process, group, rif_Group);
	return 0;
}
#undef ASSERT_TRIPLE_BASE
#undef ASSERT_MEMBER_BASE


CRIFI_IMPORT_ASSERT_RET assert_frame_rdf_to_rif(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	CRIFI_IMPORT_ASSERT_RET special_err;
	RdfToRifInfo *info = process->rdf_to_rif_info;

	special_err = rdf_to_rif_special_assert_triple(process,
				object, object_suffix, object_type,
				slotkey, slotkey_suffix, slotkey_type,
				slotvalue, slotvalue_suffix, slotvalue_type);
	switch(special_err){
		case CRIFI_IMPORT_ASSERT_NOERROR:
			return CRIFI_IMPORT_ASSERT_NOERROR;
		case CRIFI_IMPORT_ASSERT_UNHANDLED_TRIPLE:
			break;
		default:
			return special_err;
	}

	info->last_triple = crifi_import_append_triple(
			info->last_triple,
			object, object_suffix, object_type,
			slotkey, slotkey_suffix, slotkey_type,
			slotvalue, slotvalue_suffix, slotvalue_type);
	if (info->last_triple == NULL){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	if (info->first_triple == NULL){
		info->first_triple = info->last_triple;
	}
	return CRIFI_IMPORT_ASSERT_NOERROR;
}

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


static int transfer_members(PairList *first, ImportProcess *process){
	CRIFI_IMPORT_ASSERT_RET err;
	if (first == NULL) return 0;
	for (PairList *x = first;
			x != NULL;
			x = x->next)
	{
		err = rdf_to_rif_internal_assert_member(process,
				x->left, x->left_suffix, x->left_type,
				x->second, x->second_suffix, x->second_type);
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
}


static int transfer_subclass(PairList *first, ImportProcess *process){
	CRIFI_IMPORT_ASSERT_RET err;
	if (first == NULL) return 0;
	for (PairList *x = first;
			x != NULL;
			x = x->next)
	{
		err = rdf_to_rif_internal_assert_subclass(process,
				x->left, x->left_suffix, x->left_type,
				x->second, x->second_suffix, x->second_type);
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
}
