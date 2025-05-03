#include "simple_to_owl_interpretation.h"
#include "direct_interpretation.h"
#include "clipsvalue_interface.h"
#include "triple_list.h"
#include "rdf_list.h"


typedef struct simpleToOwlInfo {
	TripleList *first;
	TripleList *last;
	RDFListInfo *list_info;
} SimpleToOwlInfo;

static SimpleToOwlInfo* generate_simple_to_owl_info(crifi_graph *graph);
static void free_SimpleToOwlInfo(SimpleToOwlInfo *info);
static int transfer_rest_triples(TripleList *first, ImportProcess *sub);
static int try_special_assert(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type);

ImportProcess *start_import_process_simple_to_owl_interpretation(crifi_graph *graph){
	ImportProcess *process = malloc(sizeof(ImportProcess));
	process->graph = graph;
	process->interpreter_id = CRIFI_IMPORT_IP_SIMPLE_TO_OWL;
	process->bnode_lookup = new_bnodelookup();
	process->simple_to_owl_info = generate_simple_to_owl_info(graph);
	if (NULL == process->simple_to_owl_info){
		free(process->bnode_lookup);
		free(process);
		return NULL;
	}
	return process;
}

int end_import_process_simple_to_owl_interpretation(ImportProcess *process){
	int err1, err2=1, err5;
	ImportProcess *subprocess;

	if (process == NULL) return 1;
	subprocess = start_import_process_direct_interpretation(process->graph);
	err1 = add_clipsvalue_retriever(subprocess,
			(clipsvalue_retrieving_function*) retrieve_rdf_list,
			(void*) process->simple_to_owl_info->list_info);
	if (err1 == 0){
		err2 = transfer_rest_triples(
				process->simple_to_owl_info->first,
				subprocess);
	}
	err5 = end_import_process_direct_interpretation(subprocess);

	free_SimpleToOwlInfo(process->simple_to_owl_info);
	free_bnodelookup(process->bnode_lookup);
	free(process);
	if (err1 != 0){
		fprintf(stderr, "error 1\n");
		return err1;
	} else if (err2 != 0){
		fprintf(stderr, "error 2\n");
		return err2;
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
	switch(try_special_assert(process,
				object, object_suffix, object_type,
				slotkey, slotkey_suffix, slotkey_type,
				slotvalue, slotvalue_suffix, slotvalue_type)){
		case 0:
			return CRIFI_IMPORT_ASSERT_NOERROR;
		case 1:
			break;
		default:
			return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	process->simple_to_owl_info->last = crifi_import_append_triple(
			process->simple_to_owl_info->last,
			object, object_suffix, object_type,
			slotkey, slotkey_suffix, slotkey_type,
			slotvalue, slotvalue_suffix, slotvalue_type);
	if (0 == strcmp("http://www.w3.org/2007/rif-builtin-function#numeric-add", slotvalue)){
		fprintf(stderr, "simpletoowl assert (%s, %s, %s)\n", object, slotkey, slotvalue);
	}
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
	info->list_info = new_RDFListInfo();
	return info;
}

static void free_SimpleToOwlInfo(SimpleToOwlInfo *info){
	if (info == NULL) return;
	crifi_import_free_TripleList(info->first);
	free_RDFListInfo(info->list_info);
	free(info);
}


static int transfer_rest_triples(TripleList *first, ImportProcess *sub){
	CRIFI_IMPORT_ASSERT_RET err;
	if (first == NULL) return 0;
	for (TripleList *x = first;
			x != NULL;
			x = x->next)
	{
		err = assert_frame_direct(sub,
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


static int try_special_assert(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	if (0 == strcmp(slotkey, _RDF_first_)){
		if (0 == add_first(process->simple_to_owl_info->list_info,
				object, object_suffix, object_type,
				slotvalue, slotvalue_suffix, slotvalue_type))
		{
			return 0;
		} else {
			return 2;
		}
	} else if (0 == strcmp(slotkey, _RDF_rest_)){
		if (0 == add_rest(process->simple_to_owl_info->list_info,
				object, object_suffix, object_type,
				slotvalue, slotvalue_suffix, slotvalue_type))
		{
			return 0;
		} else {
			return 2;
		}
	}
	return 1;
}

