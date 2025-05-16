#include "simpletoowl_special_assert.h"
#include "triple_list.h"
#include "rdf_list.h"
#include "simple_to_owl_info.h"

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
	return add_first(process->simple_to_owl_info->list_info,
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
	return add_rest(process->simple_to_owl_info->list_info,
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
	/*
	return add_member(process->simple_to_owl_info->list_info,
			object, object_suffix, object_type,
			slotvalue, slotvalue_suffix, slotvalue_type);
	*/
}

static int my_add_subclass(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	/*
	return add_subclass(process->simple_to_owl_info->list_info,
			object, object_suffix, object_type,
			slotvalue, slotvalue_suffix, slotvalue_type);
	*/
}

static SpecialAssert* get_special_assert(const char* id){
	if (0 == strcmp(id, _RDF_first_)){
		return my_add_first;
	} else if (0 == strcmp(id, _RDF_rest_)){
		return my_add_rest;
	} else if (0 == strcmp(id, _RDF_subClassOf_)){
		//return my_add_subclass;
	} else if (0 == strcmp(id, _RDF_type_)){
		//return my_add_member;
	}
	return NULL;
}


CRIFI_IMPORT_ASSERT_RET simpletoowl_special_assert_triple(
		ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	int err;
	SpecialAssert *my_assert = get_special_assert(slotkey);
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
