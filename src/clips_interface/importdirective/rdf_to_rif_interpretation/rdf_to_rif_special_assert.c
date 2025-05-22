#include "rdf_to_rif_special_assert.h"
#include "triple_list.h"
#include "pair_list.h"
#include "rdf_list.h"
#include "rdf_to_rif_commondata.h"

typedef int SpecialAssert(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type);

static int my_add_first(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	RdfToRifInfo *info = process->rdf_to_rif_info;
	return add_first(info->list_info,
			object, object_suffix, object_type,
			slotvalue, slotvalue_suffix, slotvalue_type);
}

static int my_add_rest(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	RdfToRifInfo *info = process->rdf_to_rif_info;
	return add_rest(info->list_info,
			object, object_suffix, object_type,
			slotvalue, slotvalue_suffix, slotvalue_type);
}

static int my_add_member(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	PairList *new_last;
	RdfToRifInfo *info = process->rdf_to_rif_info;
	new_last = crifi_import_append_pair(
			info->last_member,
			object, object_suffix, object_type,
			slotvalue, slotvalue_suffix, slotvalue_type);
	if (new_last == NULL){
		return 1;
	}
	info->last_member = new_last;
	if (info->first_member == NULL){
		info->first_member = new_last;
	}
	return 0;
}

static int my_add_subclass(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	PairList *new_last;
	RdfToRifInfo *info = process->rdf_to_rif_info;
	new_last = crifi_import_append_pair(
			info->last_subclass,
			object, object_suffix, object_type,
			slotvalue, slotvalue_suffix, slotvalue_type);
	if (new_last == NULL){
		return 1;
	}
	info->last_subclass = new_last;
	if (info->first_subclass == NULL){
		info->first_subclass = new_last;
	}
	return 0;
}

static SpecialAssert* get_special_assert(const char* pred, const char* obj){
	if (0 == strcmp(pred, _RDF_first_)){
		return my_add_first;
	} else if (0 == strcmp(pred, _RDF_rest_)){
		return my_add_rest;
	} else if (0 == strcmp(pred, _RDFS_subClassOf_)){
		return my_add_subclass;
	} else if (0 == strcmp(pred, _RDF_type_)){
		//on owl direct use subject as ontology id
		if (0 == strcmp(obj, _OWL_Ontology_)){
		}
		return my_add_member;
	}
	return NULL;
}


CRIFI_IMPORT_ASSERT_RET rdf_to_rif_special_assert_triple(
		ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	int err;
	SpecialAssert *my_assert = get_special_assert(slotkey, slotvalue);
	if (my_assert != NULL){
		err = my_assert(process,
				object, object_suffix, object_type,
				slotkey, slotkey_suffix, slotkey_type,
				slotvalue, slotvalue_suffix, slotvalue_type);
		if (err == 0){
			return CRIFI_IMPORT_ASSERT_NOERROR;
		} else {
			return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
		}
	}
	return CRIFI_IMPORT_ASSERT_UNHANDLED_TRIPLE;
}
