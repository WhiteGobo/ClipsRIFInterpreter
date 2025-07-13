#include "simple_to_owl_interpretation.h"
#include "direct_interpretation.h"
#include "clipsvalue_interface.h"
#include "triple_list.h"
#include "pair_list.h"
#include "rdf_list.h"

#include "simple_to_owl_info.h"

#include "simpletoowl_special_assert.h"

static SimpleToOwlInfo* generate_simple_to_owl_info(crifi_graph *graph);
static void free_SimpleToOwlInfo(SimpleToOwlInfo *info);
static int transfer_rest_triples(TripleList *first, ImportProcess *sub);
static int transfer_members(PairList *first, ImportProcess *sub);

ImportProcess *start_import_process_simple_to_owl_interpretation(
		crifi_graph *graph,
		SimpleStartImportProcesss start_subprocess_function)
{
	ImportProcess *process = malloc(sizeof(ImportProcess));
	process->graph = graph;
	process->interpreter_id = CRIFI_IMPORT_IP_SIMPLE_TO_OWL;
	//process->bnode_lookup = new_bnodelookup();
	process->simple_to_owl_info = generate_simple_to_owl_info(graph);
	if (NULL == process->simple_to_owl_info){
		//free(process->bnode_lookup);
		free(process);
		return NULL;
	}
	return process;
}

int end_import_process_simple_to_owl_interpretation(ImportProcess *process,
		ClipsvalueRetrieveFunction *list_retrieve){
	int err1, err2=1, err3=1, err5;
	ImportProcess *subprocess;

	if (process == NULL) return 1;
	subprocess = start_import_process_direct_interpretation(process->graph);
	if (list_retrieve == NULL){
		list_retrieve = retrieve_rdf_list;
	}
	err1 = add_clipsvalue_retriever(subprocess,
			list_retrieve,
			process->simple_to_owl_info->list_info, NULL);
	if (err1 == 0){
		err2 = transfer_rest_triples(
				process->simple_to_owl_info->first,
				subprocess);
	}
	if (err2 == 0){
		err3 = transfer_members(
				process->simple_to_owl_info->first_member,
				subprocess);
	}
	err5 = end_import_process(subprocess);

	free_SimpleToOwlInfo(process->simple_to_owl_info);
	//free_bnodelookup(process->bnode_lookup);
	free(process);
	if (err1 != 0){
		fprintf(stderr, "error 1\n");
		return err1;
	} else if (err2 != 0){
		fprintf(stderr, "error 2\n");
		return err2;
	} else if (err3 != 0){
		fprintf(stderr, "error 3\n");
		return err3;
	} else if (err5 != 0){
		fprintf(stderr, "error 5\n");
		return err5;
	}
	return 0;
}


CRIFI_IMPORT_ASSERT_RET assert_frame_simple_to_owl(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	CRIFI_IMPORT_ASSERT_RET err;
	if (process == NULL){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	} else if (process->simple_to_owl_info == NULL){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	switch(slotkey_type){ //only uris or bnode in owl accepted
		case CRIFI_IMPORT_TERM_URI:
		case CRIFI_IMPORT_TERM_BNODE:
			break;
		default:
			return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	err = simpletoowl_special_assert_triple(process,
				object, object_suffix, object_type,
				slotkey, slotkey_suffix, slotkey_type,
				slotvalue, slotvalue_suffix, slotvalue_type);
	switch(err){
		case CRIFI_IMPORT_ASSERT_NOERROR:
			return CRIFI_IMPORT_ASSERT_NOERROR;
		case CRIFI_IMPORT_ASSERT_UNHANDLED_TRIPLE:
			break;
		default:
			return err;
	}
	process->simple_to_owl_info->last = crifi_import_append_triple(
			process->simple_to_owl_info->last,
			object, object_suffix, object_type,
			slotkey, slotkey_suffix, slotkey_type,
			slotvalue, slotvalue_suffix, slotvalue_type);
	if (process->simple_to_owl_info->last == NULL){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	if (process->simple_to_owl_info->first == NULL){
		process->simple_to_owl_info->first
			= process->simple_to_owl_info->last;
	}
	return CRIFI_IMPORT_ASSERT_NOERROR;
}



static SimpleToOwlInfo* generate_simple_to_owl_info(crifi_graph *graph){
	struct simpleToOwlInfo *info = malloc(sizeof(struct simpleToOwlInfo));
	info->first = NULL;
	info->last = NULL;
	info->first_member = NULL;
	info->last_member = NULL;
	info->first_subclass = NULL;
	info->last_subclass = NULL;
	info->list_info = new_RDFListInfo();
	return info;
}

static void free_SimpleToOwlInfo(SimpleToOwlInfo *info){
	if (info == NULL) return;
	crifi_import_free_TripleList(info->first);
	free_RDFListInfo(info->list_info);

	crifi_import_free_PairList(info->first_member);
	crifi_import_free_PairList(info->first_subclass);
	free(info);
}

static int transfer_members(PairList *first, ImportProcess *sub){
	CRIFI_IMPORT_ASSERT_RET err;
	if (first == NULL) return 0;
	for (PairList *x = first;
			x != NULL;
			x = x->next)
	{
		err = crifi_import_assert_member(sub,
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

static int transfer_rest_triples(TripleList *first, ImportProcess *sub){
	CRIFI_IMPORT_ASSERT_RET err;
	if (first == NULL) return 0;
	for (TripleList *x = first;
			x != NULL;
			x = x->next)
	{
		err = crifi_import_assert_frame(sub,
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
