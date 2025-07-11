#include "direct_interpretation.h"
#include "clipsvalue_interface.h"
#include "debug.h"
#include "node_retriever.h"


typedef struct directInterpretationInfo {
	//BNodeLookup* bnode_lookup;
	ClipsvalueRetriever* node_retriever;
} DirectInterpretationInfo;

static DirectInterpretationInfo* generate_direct_interpretation_info(
				ImportProcess *process,
				crifi_graph *graph);
static void free_direct_interpretation_info(DirectInterpretationInfo *info);
static bool gen_val(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type, CLIPSValue *cv);
static CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_RET get_special_clipsvalue(
		ImportProcess *process,
		const char *id, const char *suffix,
		IMPORT_TERM_TYPE type, CLIPSValue* retval);
static void free_clipsvalue_retriever(ClipsvalueRetriever*);

ImportProcess *start_import_process_direct_interpretation(crifi_graph *graph){
	int err1;
	ImportProcess *process = malloc(sizeof(ImportProcess));
	BNodeLookup *bnode_lookup;
	process->graph = graph;
	process->interpreter_id = CRIFI_IMPORT_IP_DIRECT;
	process->direct_info = generate_direct_interpretation_info(process, graph);
	if(process->direct_info == NULL) {
		free(process);
		return NULL;
	}
	bnode_lookup = new_bnodelookup();
	if (bnode_lookup == NULL){
		free(process);
		return NULL;
	}
	err1 = add_clipsvalue_retriever(process, retrieve_blanknode,
			bnode_lookup,
			(CRIFIImportDataCleanupFunction*) free_bnodelookup);
	if (err1 != 0){
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
	free(process);
	return 0;
}

static bool gen_val(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type, CLIPSValue *cv)
{
	int err;
	/*
	CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_RET err2;
	err2 = get_special_clipsvalue(process, object, object_suffix,
					object_type, cv);
	switch (err2){
		case CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_SUCCESS:
			return true;
		case CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_NOTFOUND:
			break;
		case CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_UNHANDLED_ERROR:
		default:
			return false;
	}
	*/
	err = value_suffix_to_clipsvalue(process,
			process->direct_info->node_retriever,
			object, object_suffix,
			object_type, cv);
	if (err != 0){
		return false;
	}
	return true;
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
	if (!gen_val(process, object, object_suffix, object_type, &object_cv)){
		return CRIFI_IMPORT_ASSERT_INVALID_TERM;
	}
	if (!gen_val(process, slotkey, slotkey_suffix, slotkey_type, &slotkey_cv)){
		return CRIFI_IMPORT_ASSERT_INVALID_TERM;
	}
	if (!gen_val(process, slotvalue, slotvalue_suffix, slotvalue_type, &slotvalue_cv)){
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
	return CRIFI_IMPORT_ASSERT_NOERROR;
}


static DirectInterpretationInfo* generate_direct_interpretation_info(
				ImportProcess *process,
				crifi_graph *graph){
	DirectInterpretationInfo *info
		= malloc(sizeof(DirectInterpretationInfo));
	if (info == NULL){
		return NULL;
	}
	info->node_retriever = NULL;
	//info->bnode_lookup = new_bnodelookup();
	//if(info->bnode_lookup == NULL){
	//	free(info);
	//	return NULL;
	//}
	return info;
}


static void free_direct_interpretation_info(DirectInterpretationInfo *info){
	if (info == NULL) return;
	free_clipsvalue_retriever(info->node_retriever);
	free(info);
}


int add_clipsvalue_retriever(ImportProcess *process,
		ClipsvalueRetrieveFunction* retriever, void* context,
		CRIFIImportDataCleanupFunction *cleanup_function)
{
	switch (process->interpreter_id){
		case CRIFI_IMPORT_IP_DIRECT:
			break;
		default:
			return 1;
	}
	ClipsvalueRetriever *tmp, *new;
	if (retriever == NULL){
		return 0;
	}
	new = malloc(sizeof(ClipsvalueRetriever));
	if (new == NULL) return 1;
	new->function = retriever;
	new->context = context;
	new->next = process->direct_info->node_retriever;
	new->cleanup_function = cleanup_function;
	process->direct_info->node_retriever = new;
	return 0;
}

static void free_clipsvalue_retriever(ClipsvalueRetriever *target){
	if (target->next != NULL){
		free_clipsvalue_retriever(target->next);
	}
	if (target->context != NULL && target->cleanup_function != NULL){
		target->cleanup_function(target->context);
	}
	free(target);
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
		err = retriever->function(process, first, id, suffix, type,
						retriever->context, retval);
		if (err != CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_NOTFOUND){
			return err;
		}
	}
	return CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_NOTFOUND;
}

CRIFI_IMPORT_ASSERT_RET assert_member_direct(ImportProcess *process,
		const char *instance, const char *instance_suffix,
		IMPORT_TERM_TYPE instance_type,
		const char *class, const char *class_suffix,
		IMPORT_TERM_TYPE class_type)
{
	int err;
	CrifiAssertTripleError err3;
	CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_RET err2;
	CLIPSValue instance_cv = {.voidValue = VoidConstant(process->graph)};
	CLIPSValue class_cv = {.voidValue = VoidConstant(process->graph)};
	if (!gen_val(process, instance, instance_suffix, instance_type, &instance_cv)){
		return CRIFI_IMPORT_ASSERT_INVALID_TERM;
	}
	if (!gen_val(process, class, class_suffix, class_type, &class_cv)){
		return CRIFI_IMPORT_ASSERT_INVALID_TERM;
	}
	err3 = assert_member(process->graph, &instance_cv, &class_cv);
	switch (err3){
		case CRIFI_ASSTR_NO_ERROR:
			break;
		case CRIFI_ASSTR_SUBJECT:
		case CRIFI_ASSTR_OBJECT:
			return CRIFI_IMPORT_ASSERT_INVALID_TERM;
		case CRIFI_ASSTR_PREDICATE:
		case CRIFI_ASSTR_UNKNOWN:
		default:
			return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	return CRIFI_IMPORT_ASSERT_NOERROR;
}

CRIFI_IMPORT_ASSERT_RET assert_subclass_direct(ImportProcess *process,
		const char *sub, const char *sub_suffix,
		IMPORT_TERM_TYPE sub_type,
		const char *super, const char *super_suffix,
		IMPORT_TERM_TYPE super_type)
{
	int err;
	CrifiAssertTripleError err3;
	CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_RET err2;
	CLIPSValue sub_cv = {.voidValue = VoidConstant(process->graph)};
	CLIPSValue super_cv = {.voidValue = VoidConstant(process->graph)};
	if (!gen_val(process, sub, sub_suffix, sub_type, &sub_cv)){
		return CRIFI_IMPORT_ASSERT_INVALID_TERM;
	}
	if (!gen_val(process, super, super_suffix, super_type, &super_cv)){
		return CRIFI_IMPORT_ASSERT_INVALID_TERM;
	}
	err3 = assert_subclass(process->graph, &sub_cv, &super_cv);
	switch (err3){
		case CRIFI_ASSTR_NO_ERROR:
			break;
		case CRIFI_ASSTR_SUBJECT:
		case CRIFI_ASSTR_OBJECT:
			return CRIFI_IMPORT_ASSERT_INVALID_TERM;
		case CRIFI_ASSTR_PREDICATE:
		case CRIFI_ASSTR_UNKNOWN:
		default:
			return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	return CRIFI_IMPORT_ASSERT_NOERROR;
}
