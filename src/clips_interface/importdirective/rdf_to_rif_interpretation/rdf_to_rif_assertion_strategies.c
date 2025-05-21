#include "rdf_to_rif_assertion_strategies.h"
#include "rdf_to_rif_interpretation.h"
#include "clipsvalue_interface.h"
#include "rdf_to_rif_commondata.h"
#include "rdf_list_internal.h"


#define ASSERT_TRIPLE_OR_FAIL(process, s_cv, p_cv, o_cv) \
	switch(assert_triple(process->graph, s_cv, p_cv, o_cv)){\
		case CRIFI_ASSTR_NO_ERROR:\
			break;\
		default:\
			return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;\
	}
#define ASSERT_MEMBER_OR_FAIL(process, s_cv, o_cv) \
	switch(assert_member(process->graph, s_cv, o_cv)){\
		case CRIFI_ASSTR_NO_ERROR:\
			break;\
		default:\
			return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;\
	}

static CRIFI_IMPORT_ASSERT_RET assert_term(ImportProcess *process,
		const char *value, const char *suffix,
		IMPORT_TERM_TYPE type, CLIPSValue *ret){
	int suffix_length;
	int err;
	CLIPSValue term_cv;
	CLIPSValue value_cv;
	struct rdfToRifInfo *info = process->rdf_to_rif_info;
	CLIPSValue rif_Const = {.value = info->rif_Const.value};
	CLIPSValue rif_constIRI = {.value = info->rif_constIRI.value};
	CLIPSValue rif_value = {.value = info->rif_value.value};
	//CLIPSValue rif_Var;
	//CLIPSValue rif_varname;
	if (0 != new_blanknode(process->graph, ret)){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	if (suffix != NULL){
		suffix_length = strlen(suffix);
	} else {
		suffix_length = 0;
	}
	switch(type){
		case CRIFI_IMPORT_TERM_URI:
			err = value_and_datatype_to_clipsvalue(process->graph,
					value, strlen(value),
					_XS_anyURI_, strlen(_XS_anyURI_),
					&value_cv);
			if (err != 0){
				return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
			}
			ASSERT_MEMBER_OR_FAIL(process, ret, &rif_Const);
			ASSERT_TRIPLE_OR_FAIL(process, ret, &rif_constIRI, &value_cv);
			break;
		case CRIFI_IMPORT_TERM_TYPEDLITERAL:
			err = value_and_datatype_to_clipsvalue(process->graph,
						value, strlen(value),
						suffix, suffix_length,
						&value_cv);
			if (err != 0){
				return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
			}
			ASSERT_MEMBER_OR_FAIL(process, ret, &rif_Const);
			ASSERT_TRIPLE_OR_FAIL(process, ret, &rif_value, &value_cv);
			break;
		case CRIFI_IMPORT_TERM_LANGLITERAL:
			err = value_and_lang_to_clipsvalue(process->graph,
						value, strlen(value),
						suffix, suffix_length,
						&value_cv);
			if (err != 0){
				return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
			}
			ASSERT_MEMBER_OR_FAIL(process, ret, &rif_Const);
			ASSERT_TRIPLE_OR_FAIL(process, ret, &rif_value, &value_cv);
			break;
		case CRIFI_IMPORT_TERM_BNODE:
			err = value_and_datatype_to_clipsvalue(process->graph,
						value, strlen(value),
						_RIF_local_, strlen(_RIF_local_),
						&value_cv);
			if (err != 0){
				return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
			}
			ASSERT_MEMBER_OR_FAIL(process, ret, &rif_Const);
			ASSERT_TRIPLE_OR_FAIL(process, ret, &rif_value, &value_cv);
			break;
		case CRIFI_IMPORT_TERM_UNKNOWN:
		default:
			return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	return CRIFI_IMPORT_ASSERT_NOERROR;
}


CRIFI_IMPORT_ASSERT_RET assert_frame_rdf_to_rif(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	RdfToRifInfo *info = process->rdf_to_rif_info;
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

CRIFI_IMPORT_ASSERT_RET assert_triple_rdf_to_rif(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	int err;
	CRIFI_IMPORT_ASSERT_RET ret;
	crifi_graph *graph = process->graph;
	struct rdfToRifInfo *info = process->rdf_to_rif_info;
	CLIPSValue *rdf_first = &(info->rdf_first);
	CLIPSValue *rdf_rest = &(info->rdf_rest);
	CLIPSValue rdf_nil = {.value = info->rdf_nil.value};
	CLIPSValue rif_Frame = {.value = info->rif_Frame.value};
	CLIPSValue rif_Slot = {.value = info->rif_Slot.value};
	CLIPSValue rif_slots = {.value = info->rif_slots.value};
	CLIPSValue rif_slotkey = {.value = info->rif_slotkey.value};
	CLIPSValue rif_slotvalue = {.value = info->rif_slotvalue.value};
	CLIPSValue rif_object = {.value = info->rif_object.value};

	CLIPSValue object_cv = {.voidValue = VoidConstant(process->graph)};
	CLIPSValue slotkey_cv = {.voidValue = VoidConstant(process->graph)};
	CLIPSValue slotvalue_cv = {.voidValue = VoidConstant(process->graph)};
	CLIPSValue slotlist = {.voidValue = VoidConstant(process->graph)};
	CLIPSValue slot = {.voidValue = VoidConstant(process->graph)};
	CLIPSValue frame = {.voidValue = VoidConstant(process->graph)};
	CLIPSValue new_rule_list = {.voidValue = VoidConstant(process->graph)};


	ret = assert_term(process, object, object_suffix,
				object_type, &object_cv);
	if (ret != CRIFI_IMPORT_ASSERT_NOERROR){
		return ret;
	}
	ret = assert_term(process, slotkey, slotkey_suffix,
				slotkey_type, &slotkey_cv);
	if (ret != CRIFI_IMPORT_ASSERT_NOERROR){
		return ret;
	}
	ret = assert_term(process, slotvalue, slotvalue_suffix,
				slotvalue_type, &slotvalue_cv);
	if (ret != CRIFI_IMPORT_ASSERT_NOERROR){
		return ret;
	}
	if (0 != new_blanknode(graph, &frame)){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	if (0 != new_blanknode(graph, &slot)){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	if (0 != new_blanknode(graph, &slotlist)){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	ASSERT_MEMBER_OR_FAIL(process, &frame, &rif_Frame);
	ASSERT_TRIPLE_OR_FAIL(process, &frame, &rif_object, &object_cv);
	ASSERT_TRIPLE_OR_FAIL(process, &frame, &rif_slots, &slotlist);
	ASSERT_TRIPLE_OR_FAIL(process, &slotlist, rdf_first, &slot);
	ASSERT_TRIPLE_OR_FAIL(process, &slotlist, rdf_rest, &rdf_nil);
	ASSERT_MEMBER_OR_FAIL(process, &slot, &rif_Slot);
	ASSERT_TRIPLE_OR_FAIL(process, &slot, &rif_slotkey, &slotkey_cv);
	ASSERT_TRIPLE_OR_FAIL(process, &slot, &rif_slotvalue, &slotvalue_cv);
	if (0 != new_blanknode(graph, &new_rule_list)){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	ASSERT_TRIPLE_OR_FAIL(process, &new_rule_list, rdf_rest, &(info->rule_list));
	ASSERT_TRIPLE_OR_FAIL(process, &new_rule_list, rdf_first, &frame);
	info->rule_list.value = new_rule_list.value;
	return CRIFI_IMPORT_ASSERT_NOERROR;
}



CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_RET get_rif_list(
		ImportProcess *process,
		ClipsvalueRetriever* node_retriever,
		const char *id, const char *suffix, IMPORT_TERM_TYPE type,
		void* context, //RDFListInfo* context,
		CLIPSValue* retval)
{
	return CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_NOTFOUND;
	CRIFI_IMPORT_GENERATE_RDFLIST err;
	/*
	err = get_list_as_clipsvalue(
			process, node_retriever,
			(RDFListInfo*) context,
			id, suffix, type, retval);
			*/
	switch(err){
		case CRIFI_IMPORT_GENERATE_RDFLIST_NOERROR:
			return CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_SUCCESS;
		case CRIFI_IMPORT_GENERATE_RDFLIST_NOTFOUND:
			return CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_NOTFOUND;
		case CRIFI_IMPORT_GENERATE_RDFLIST_UNKNOWN_ERROR:
		default:
			return CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_UNHANDLED_ERROR;
	}
}

