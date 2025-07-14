#include "rdf_to_rif_commondata.h"

static bool init_clipsvalues(crifi_graph *graph, RdfToRifInfo *info);

RdfToRifInfo* generate_rdf_rif_info(crifi_graph *graph){
	int err;
	RdfToRifInfo *info = malloc(sizeof(RdfToRifInfo));
	if (info == NULL){
		return NULL;
	}

	info->first_triple = NULL;
	info->last_triple = NULL;
	info->first_member = NULL;
	info->last_member = NULL;
	info->first_subclass = NULL;
	info->last_subclass = NULL;

	info->rule_list = NULL;

	if(!init_clipsvalues(graph, info)){
		free(info);
		return NULL;
	}
	info->list_info = new_RDFListInfo();
	if (info->list_info == NULL){
		free(info);
		return NULL;
	}

	info->bnode_lookup = new_bnodelookup();
	return info;
}

static bool init_clipsvalues(crifi_graph *graph, RdfToRifInfo *info){
	int err;
	if (0 != new_blanknode(graph, &(info->document))){
		return false;
	}
	if (0 != new_blanknode(graph, &(info->group))){
		return false;
	}
	//if (0 != new_blanknode(graph, &(info->rule_list))){
	//	return false;
	//}

	//err = uri_to_clipsvalue(graph, _RDF_nil_, strlen(_RDF_nil_),
	//		&(info->rdf_nil));
	//if (err != 0){
	//	return false;
	//}
	//info->rule_list.value = info->rdf_nil.value;

	err = uri_to_clipsvalue(graph, _RDF_type_, strlen(_RDF_type_),
			&(info->rdf_type));
	if (err != 0){
		return false;
	}
	/*err = uri_to_clipsvalue(graph, _RDF_first_, strlen(_RDF_first_),
			&(info->rdf_first));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RDF_rest_, strlen(_RDF_rest_),
			&(info->rdf_rest));
	if (err != 0){
		return false;
	}*/

	err = uri_to_clipsvalue(graph, _RIF_Document_, strlen(_RIF_Document_),
			&(info->rif_Document));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_Group_, strlen(_RIF_Group_),
			&(info->rif_Group));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_payload_, strlen(_RIF_payload_),
			&(info->rif_payload));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_sentences_, strlen(_RIF_sentences_),
			&(info->rif_sentences));
	if (err != 0){
		return false;
	}

	err = uri_to_clipsvalue(graph, _RIF_Const_, strlen(_RIF_Const_),
			&(info->rif_Const));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_constIRI_, strlen(_RIF_constIRI_),
			&(info->rif_constIRI));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_value_, strlen(_RIF_value_),
			&(info->rif_value));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_Var_, strlen(_RIF_Var_),
			&(info->rif_Var));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_varname_, strlen(_RIF_varname_),
			&(info->rif_varname));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_Frame_, strlen(_RIF_Frame_),
			&(info->rif_Frame));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_Slot_, strlen(_RIF_Slot_),
			&(info->rif_Slot));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_slots_, strlen(_RIF_slots_),
			&(info->rif_slots));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_slotkey_, strlen(_RIF_slotkey_),
			&(info->rif_slotkey));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_slotvalue_, strlen(_RIF_slotvalue_),
			&(info->rif_slotvalue));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_object_, strlen(_RIF_object_),
			&(info->rif_object));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_Member_, strlen(_RIF_Member_),
			&(info->rif_Member));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_instance_, strlen(_RIF_instance_),
			&(info->rif_instance));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_class_, strlen(_RIF_class_),
			&(info->rif_class));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_Subclass_, strlen(_RIF_Subclass_),
			&(info->rif_Subclass));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_super_, strlen(_RIF_super_),
			&(info->rif_super));
	if (err != 0){
		return false;
	}
	err = uri_to_clipsvalue(graph, _RIF_sub_, strlen(_RIF_sub_),
			&(info->rif_sub));
	if (err != 0){
		return false;
	}

	return true;
}

void free_rdf_rif_info(struct rdfToRifInfo *info){
	free_bnodelookup(info->bnode_lookup);
	free_RDFListInfo(info->list_info);
	free_cvsnake(info->rule_list);
	crifi_import_free_PairList(info->first_member);
	crifi_import_free_PairList(info->first_subclass);
	crifi_import_free_TripleList(info->first_triple);
	free(info);
}
