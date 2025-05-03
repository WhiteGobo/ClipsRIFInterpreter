#include "direct_interpretation.h"
#include "clipsvalue_interface.h"
#include "debug.h"

static CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_RET get_special_clipsvalue(
		ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type, CLIPSValue* target);

typedef struct clipsvalueRetriever {
	clipsvalue_retrieving_function* function;
	void *context;
	struct clipsvalueRetriever* next;
} ClipsvalueRetriever;

typedef struct directInterpretationInfo {
	BNodeLookup* bnode_lookup;
	ClipsvalueRetriever* node_retriever;
} DirectInterpretationInfo;

static DirectInterpretationInfo* generate_direct_interpretation_info(
				crifi_graph *graph);
static void free_direct_interpretation_info(DirectInterpretationInfo *info);

ImportProcess *start_import_process_direct_interpretation(crifi_graph *graph){
	ImportProcess *process = malloc(sizeof(ImportProcess));
	process->graph = graph;
	process->interpreter_id = CRIFI_IMPORT_IP_DIRECT;
	process->bnode_lookup = new_bnodelookup();
	process->direct_info = generate_direct_interpretation_info(graph);
	if(process->direct_info == NULL) {
		free(process);
		return NULL;
	}
	return process;
}

int end_import_process_direct_interpretation(ImportProcess *process){
	if (process == NULL){
		return 1;
	}
	free_direct_interpretation_info(process->direct_info);
	free_bnodelookup(process->bnode_lookup);
	free(process);
	return 0;
}

CRIFI_IMPORT_ASSERT_RET assert_frame_direct(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	int err;
	CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_RET err2;
	CLIPSValue object_cv = {.voidValue = VoidConstant(process->graph)};
	CLIPSValue slotkey_cv = {.voidValue = VoidConstant(process->graph)};
	CLIPSValue slotvalue_cv = {.voidValue = VoidConstant(process->graph)};
	err2 = get_special_clipsvalue(process, object, object_suffix,
					object_type, &object_cv);
	if (err2 == CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_NOTFOUND){
		err = value_suffix_to_clipsvalue(process, object, object_suffix,
					object_type, &object_cv);
		if (err != 0){
			return CRIFI_IMPORT_ASSERT_INVALID_TERM;
		}
	} else if (err2 == CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_UNHANDLED_ERROR){
		return CRIFI_IMPORT_ASSERT_INVALID_TERM;
	}

	err2 = get_special_clipsvalue(process, slotkey, slotkey_suffix,
					slotkey_type, &slotkey_cv);
	if (err2 == CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_NOTFOUND){
		err = value_suffix_to_clipsvalue(process, slotkey,
					slotkey_suffix, slotkey_type,
					&slotkey_cv);
		if (err != 0){
			return CRIFI_IMPORT_ASSERT_INVALID_TERM;
		}
	} else if (err2 == CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_UNHANDLED_ERROR){
		return CRIFI_IMPORT_ASSERT_INVALID_TERM;
	}

	err2 = get_special_clipsvalue(process, slotvalue, slotvalue_suffix,
					slotvalue_type, &slotvalue_cv);
	if (err2 == CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_NOTFOUND){
		err = value_suffix_to_clipsvalue(process, slotvalue,
					slotvalue_suffix, slotvalue_type,
					&slotvalue_cv);
		if (err != 0){
			return CRIFI_IMPORT_ASSERT_INVALID_TERM;
		}
	} else if (err2 == CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_UNHANDLED_ERROR){
		return CRIFI_IMPORT_ASSERT_INVALID_TERM;
	}

	err = assert_triple(process->graph, &object_cv, &slotkey_cv,
					&slotvalue_cv);
	switch (err){
		case CRIFI_ASSTR_NO_ERROR:
			break;
		case CRIFI_ASSTR_SUBJECT:
		case CRIFI_ASSTR_PREDICATE:
		case CRIFI_ASSTR_OBJECT:
			return CRIFI_IMPORT_ASSERT_INVALID_TERM;
		case CRIFI_ASSTR_UNKNOWN:
		default:
			return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	if (0 == strcmp("http://www.w3.org/2007/rif-builtin-function#numeric-add", slotvalue)){
		fprintf(stderr, "used object %s\n", object);
		fprintf(stderr, "qwertz found:\n");
		fprintf(stderr, "assert (");
		debugprint(stderr, &object_cv);
		fprintf(stderr, ", ");
		debugprint(stderr, &slotkey_cv);
		fprintf(stderr, ", ");
		debugprint(stderr, &slotvalue_cv);
		fprintf(stderr, ")\n");
	}
	return CRIFI_IMPORT_ASSERT_NOERROR;
}


static DirectInterpretationInfo* generate_direct_interpretation_info(
				crifi_graph *graph){
	DirectInterpretationInfo *info
		= malloc(sizeof(DirectInterpretationInfo));
	if (info == NULL){
		return NULL;
	}
	info->node_retriever = NULL;
	info->bnode_lookup = new_bnodelookup();
	if(info->bnode_lookup == NULL){
		free(info);
		return NULL;
	}
	return info;
}


static void free_direct_interpretation_info(DirectInterpretationInfo *info){
	if (info == NULL) return;
	free_bnodelookup(info->bnode_lookup);
	free(info);
}


int add_clipsvalue_retriever(ImportProcess *process,
		clipsvalue_retrieving_function* retriever, void* context)
{
	ClipsvalueRetriever *tmp, *new;
	if (retriever == NULL){
		return 0;
	}
	new = malloc(sizeof(ClipsvalueRetriever));
	if (new == NULL) return 1;
	new->function = retriever;
	new->context = context;
	new->next = NULL;
	if(process->direct_info->node_retriever == NULL){
		process->direct_info->node_retriever = new;
		return 0;
	}
	tmp = process->direct_info->node_retriever;
	while(tmp->next != NULL){
		tmp = tmp->next;
	}
	tmp->next = new;
	return 0;
}

static CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_RET get_special_clipsvalue(
		ImportProcess *process,
		const char *id, const char *suffix,
		IMPORT_TERM_TYPE type, CLIPSValue* retval)
{
	CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_RET err;
	ClipsvalueRetriever* first = process->direct_info->node_retriever;
	for (ClipsvalueRetriever* retriever = first;
			retriever != NULL;
			retriever = retriever->next)
	{
		err = retriever->function(process, id, suffix, type,
						retriever->context, retval);
		if (err != CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_NOTFOUND){
			return err;
		}
	}
	return CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_NOTFOUND;
}
