#include "rdf_to_rif_interpretation.h"
#include "clipsvalue_interface.h"

#define ASSERT_TRIPLE_OR_FAIL(process, s_cv, p_cv, o_cv) \
	if ( CRIFI_ASSTR_NO_ERROR != assert_triple(process->graph, s_cv, p_cv, o_cv)){ \
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;\
	}

static int generate_rdf_rif_info(crifi_graph *graph, struct rdfToRifInfo *info){
	int err;
	if (0 != new_blanknode(graph, &(info->document))){
		return 1;
	}
	if (0 != new_blanknode(graph, &(info->group))){
		return 1;
	}
	if (0 != new_blanknode(graph, &(info->rule_list))){
		return 1;
	}

	err = uri_to_clipsvalue(graph, _RDF_nil_, strlen(_RDF_nil_),
			&(info->rdf_nil));
	if (err != 0) return 1;
	info->rule_list.value = info->rdf_nil.value;

	err = uri_to_clipsvalue(graph, _RDF_type_, strlen(_RDF_type_),
			&(info->rdf_type));
	if (err != 0) return 1;
	err = uri_to_clipsvalue(graph, _RDF_first_, strlen(_RDF_first_),
			&(info->rdf_first));
	if (err != 0) return 1;
	err = uri_to_clipsvalue(graph, _RDF_rest_, strlen(_RDF_rest_),
			&(info->rdf_rest));
	if (err != 0) return 1;

	err = uri_to_clipsvalue(graph, _RIF_Document_, strlen(_RIF_Document_),
			&(info->rif_Document));
	if (err != 0) return 1;
	err = uri_to_clipsvalue(graph, _RIF_Group_, strlen(_RIF_Group_),
			&(info->rif_Group));
	if (err != 0) return 1;
	err = uri_to_clipsvalue(graph, _RIF_payload_, strlen(_RIF_payload_),
			&(info->rif_payload));
	if (err != 0) return 1;
	err = uri_to_clipsvalue(graph, _RIF_sentences_, strlen(_RIF_sentences_),
			&(info->rif_sentences));
	if (err != 0) return 1;

	err = uri_to_clipsvalue(graph, _RIF_Const_, strlen(_RIF_Const_),
			&(info->rif_Const));
	if (err != 0) return 1;
	err = uri_to_clipsvalue(graph, _RIF_constIRI_, strlen(_RIF_constIRI_),
			&(info->rif_constIRI));
	if (err != 0) return 1;
	err = uri_to_clipsvalue(graph, _RIF_value_, strlen(_RIF_value_),
			&(info->rif_value));
	if (err != 0) return 1;
	err = uri_to_clipsvalue(graph, _RIF_Var_, strlen(_RIF_Var_),
			&(info->rif_Var));
	if (err != 0) return 1;
	err = uri_to_clipsvalue(graph, _RIF_varname_, strlen(_RIF_varname_),
			&(info->rif_varname));
	if (err != 0) return 1;
	err = uri_to_clipsvalue(graph, _RIF_Frame_, strlen(_RIF_Frame_),
			&(info->rif_Frame));
	if (err != 0) return 1;
	err = uri_to_clipsvalue(graph, _RIF_Slot_, strlen(_RIF_Slot_),
			&(info->rif_Slot));
	if (err != 0) return 1;
	err = uri_to_clipsvalue(graph, _RIF_slots_, strlen(_RIF_slots_),
			&(info->rif_slots));
	if (err != 0) return 1;
	err = uri_to_clipsvalue(graph, _RIF_slotkey_, strlen(_RIF_slotkey_),
			&(info->rif_slotkey));
	if (err != 0) return 1;
	err = uri_to_clipsvalue(graph, _RIF_slotvalue_, strlen(_RIF_slotvalue_),
			&(info->rif_slotvalue));
	if (err != 0) return 1;
	err = uri_to_clipsvalue(graph, _RIF_object_, strlen(_RIF_object_),
			&(info->rif_object));
	if (err != 0) return 1;

	return 0;
}

ImportProcess *start_import_process_rdf_to_rif_interpretation(
				crifi_graph *graph,
				CRIFI_IMPORT_INTERPRETER_ID interpreter_id)
{
	CLIPSValue group, document;
	ImportProcess *process = malloc(sizeof(ImportProcess));
	document.value = process->rdf_to_rif_info.document.value;
	group.value = process->rdf_to_rif_info.group.value;
	if(
			0 != new_blanknode(graph, &document)
			|| 0 != new_blanknode(graph, &group))
	{
		free(process);
		return NULL;
	}
	process->graph = graph;
	process->interpreter_id = interpreter_id;
	process->bnode_lookup = new_bnodelookup();

	if (0 != generate_rdf_rif_info(graph, &(process->rdf_to_rif_info))){
		free(process->bnode_lookup);
		free(process);
		return NULL;
	}

	return process;
}

#define ASSERT_TRIPLE_BASE(process, s_cv, p_cv, o_cv) \
	if ( CRIFI_ASSTR_NO_ERROR != assert_triple(process->graph, s_cv, p_cv, o_cv)){ \
		return 1;\
	}
static int assert_base_information(ImportProcess *process){
	CLIPSValue *document = &(process->rdf_to_rif_info.document);
	CLIPSValue *group = &(process->rdf_to_rif_info.group);
	CLIPSValue *rule_list = &(process->rdf_to_rif_info.rule_list);
	CLIPSValue *rif_payload = &(process->rdf_to_rif_info.rif_payload);
	CLIPSValue *rdf_type = &(process->rdf_to_rif_info.rdf_type);
	CLIPSValue *rif_sentences = &(process->rdf_to_rif_info.rif_sentences);
	CLIPSValue *rif_Document = &(process->rdf_to_rif_info.rif_Document);
	CLIPSValue *rif_Group = &(process->rdf_to_rif_info.rif_Group);
	ASSERT_TRIPLE_BASE(process, document, rif_payload, group);
	ASSERT_TRIPLE_BASE(process, document, rdf_type, rif_Document);
	ASSERT_TRIPLE_BASE(process, group, rif_sentences, rule_list);
	ASSERT_TRIPLE_BASE(process, group, rdf_type, rif_Group);
	return 0;
}
#undef ASSERT_TRIPLE_BASE

int end_import_process_rdf_to_rif_interpretation(ImportProcess *process){
	int err = 0;
	if (process == NULL){
		return 1;
	}
	err = assert_base_information(process);
	free_bnodelookup(process->bnode_lookup);
	free(process);
	return err;
}

static CRIFI_IMPORT_ASSERT_RET assert_term(ImportProcess *process,
		const char *value, const char *suffix,
		IMPORT_TERM_TYPE type, CLIPSValue *ret){
	int suffix_length;
	int err;
	CLIPSValue term_cv;
	CLIPSValue value_cv;
	struct rdfToRifInfo *info = &(process->rdf_to_rif_info);
	CLIPSValue rdf_type = {.value = info->rdf_type.value};
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
			ASSERT_TRIPLE_OR_FAIL(process, ret, &rdf_type, &rif_Const);
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
			ASSERT_TRIPLE_OR_FAIL(process, ret, &rdf_type, &rif_Const);
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
			ASSERT_TRIPLE_OR_FAIL(process, ret, &rdf_type, &rif_Const);
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
			ASSERT_TRIPLE_OR_FAIL(process, ret, &rdf_type, &rif_Const);
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
	int err;
	CRIFI_IMPORT_ASSERT_RET ret;
	crifi_graph *graph = process->graph;
	struct rdfToRifInfo *info = &(process->rdf_to_rif_info);
	CLIPSValue rdf_type = {.value = info->rdf_type.value};
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
	ASSERT_TRIPLE_OR_FAIL(process, &frame, &rdf_type, &rif_Frame);
	ASSERT_TRIPLE_OR_FAIL(process, &frame, &rif_object, &object_cv);
	ASSERT_TRIPLE_OR_FAIL(process, &frame, &rif_slots, &slotlist);
	ASSERT_TRIPLE_OR_FAIL(process, &slotlist, rdf_first, &slot);
	ASSERT_TRIPLE_OR_FAIL(process, &slotlist, rdf_rest, &rdf_nil);
	ASSERT_TRIPLE_OR_FAIL(process, &slot, &rdf_type, &rif_Slot);
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
