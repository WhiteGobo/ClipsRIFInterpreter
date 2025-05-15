#include "crifi_lists.h"

#include <crifi_objects.h>
#include "n3parser.h"
#include "dataspace_constants.h"
#include "ffi_constants.h"

/**
 * returns success
 */
static bool normalize_index(size_t length, long long *index){
	//compare size_t with long long only safe if positive
	//see `https://stackoverflow.com/questions/3642010/can-i-compare-int-with-size-t-directly-in-c`_
	if (length == 0){
		return false;
	}
	if (*index>0 && *index >= length){
		return false;
	}
	if (*index<0){
		*index += length;
		if (*index<0) return false;
	}
	return true;
}


/*
Fact *clipsvalue_to_list(CLIPSValue val){
	Deftemplate *factClass;
	Fact *list;
	if(val.header->type != FACT_ADDRESS_TYPE) return NULL;
	factClass = FactDeftemplate(list);
	if(0 != strcmp("AtomList", DeftemplateName(factClass))){
		return NULL;
	}
	return list;
}
*/


CRIFI_LIST_GET_RET crifi_list_get(Environment *env, CLIPSValue list, long long index, CLIPSValue *ret){
	size_t length;
	long long i = index;
	CLIPSValue itemscontainer;
	CLIPSValue *items;
	if (!retrieve_items(env, list, &itemscontainer)){
		return CRIFI_LIST_GET_NOLIST;
	}
	items = itemscontainer.multifieldValue->contents;
	length = crifi_list_count(env, &list);
	if (!normalize_index(length, &i)){
		return CRIFI_LIST_GET_INDEX;
	}
	ret->value = items[i].value;
	return CRIFI_LIST_GET_NOERROR;
}

CRIFI_LIST_REMOVE_RET crifi_list_remove(Environment *env, CLIPSValue list, long long index, CLIPSValue *ret){
	size_t length, newlength;
	long long i, ii;
	int err;
	CLIPSValue itemscontainer;
	CLIPSValue tmp;
	CLIPSValue *items;
	CLIPSValue *newitems;
	if (ret == NULL || env == NULL){
		return CRIFI_LIST_REMOVE_USAGE;
	}
	if (!retrieve_items(env, list, &itemscontainer)){
		return CRIFI_LIST_REMOVE_NOLIST;
	}
	items = itemscontainer.multifieldValue->contents;
	length = crifi_list_count(env, &list);
	if (length <= 0){
		return CRIFI_LIST_REMOVE_EMPTY_LIST;
	}
	if (!normalize_index(length, &index)){
		return CRIFI_LIST_REMOVE_INDEX;
	}
	if (index < 0 || index >= length){
		return CRIFI_LIST_REMOVE_INDEX;
	}
	newlength = length - 1;
	newitems = malloc(length * sizeof(CLIPSValue));
	if (newitems == NULL){
		return CRIFI_LIST_REMOVE_MALLOC;
	}
	ii = 0;
	for (int i = 0; i < newlength; i++){
		if (i == index){
			ii++;
		}
		newitems[i].value = items[ii].value;
		ii++;
	}
	err = crifi_list_new(env, newitems, length - 1, ret);
	if (err){
		return CRIFI_LIST_REMOVE_CREATE_LIST;
	}
	return CRIFI_LIST_REMOVE_NOERROR;
}

Fact *crifi_list_concatenate(Environment *env, CLIPSValue *listlist, size_t listlist_length){
	CLIPSValue ret = {.voidValue=VoidConstant(env)};
	size_t newlist_length = 0;
	CLIPSValue items[listlist_length];
	CLIPSValue *newvalues, *tmpptr;
	Fact *newlist;
	Multifield *tmp_mf;
	for (int i=0; i<listlist_length; i++){
		if (!retrieve_items(env, listlist[i], items+i)){
			return NULL;
		}
		newlist_length += items[i].multifieldValue->length;
	}
	newvalues = calloc(newlist_length, sizeof(CLIPSValue));
	tmpptr = newvalues;
	for (int i=0; i<listlist_length; i++){
		tmp_mf = items[i].multifieldValue;
		for (int j=0; j < tmp_mf->length; j++){
			tmpptr->value = tmp_mf->contents[j].value;
			tmpptr++;
		}
	}
	int err = crifi_list_new(env, newvalues, newlist_length, &ret);
	free(newvalues);
	if (err == 0){
		return ret.factValue;
	} else {
		return NULL;
	}
}


Fact *crifi_list_distinct_values(Environment *env, CLIPSValue list){
	int err;
	IEQ_RET check;
	size_t newlist_length = 0;
	CLIPSValue mf_items, *items;
	CLIPSValue *newitems, *tmpptr;
	CLIPSValue ret = {.voidValue=VoidConstant(env)};

	if (!retrieve_items(env, list, &mf_items)){
		return NULL;
	}
	items = mf_items.multifieldValue->contents;
	newitems = calloc(mf_items.multifieldValue->length, sizeof(CLIPSValue));
	tmpptr = newitems;
	for (int i=0; i < mf_items.multifieldValue->length; i++){
		check = IEQ_FALSE;
		for (int j=0; j<i; j++){
			check = internal_equal(env, items + i, items + j);
			if (check != IEQ_FALSE) break;
		}
		if (check == IEQ_FALSE){
			tmpptr->value = items[i].value;
			newlist_length++;
			tmpptr++;
		} else if (check == IEQ_ERROR){
			free(newitems);
			return NULL;
		}
	}
	err = crifi_list_new(env, newitems, newlist_length, &ret);
	free(newitems);
	if (err == 0){
		return ret.factValue;
	} else {
		return NULL;
	}
}


/*
 * print single argument for new instance command in crifi_list_new
 */
static size_t sprintf_arg(char *cptr, const char* format, CLIPSValue val){
	switch (val.header->type){
		case STRING_TYPE:
			return sprintf(cptr, " \"%s\"", val.lexemeValue->contents);
			break;
		case SYMBOL_TYPE:
			return sprintf(cptr, " %s", val.lexemeValue->contents);
			break;
		case INSTANCE_NAME_TYPE:
			return sprintf(cptr, " [%s]",val.lexemeValue->contents);
			break;
		case INSTANCE_ADDRESS_TYPE:
			return sprintf(cptr, " [%s]", InstanceName(val.instanceValue));
			break;
		default:
			//fprintf(stderr, "something went wrong in getargsize\n");
			return 0;
	}
}

/** 
 * used for crifi_list_new
 */
static size_t get_argsize(CLIPSValue val){
	switch (val.header->type){
		case SYMBOL_TYPE:
			return 1+strlen(val.lexemeValue->contents);
			break;
		case STRING_TYPE:
		case INSTANCE_NAME_TYPE:
			return 3+strlen(val.lexemeValue->contents);
			break;
		case INSTANCE_ADDRESS_TYPE:
			return 3+strlen(InstanceName(val.instanceValue));
			break;
		default:
			//fprintf(stderr, "something went wrong in getargsize\n");
	}
}

int crifi_list_new(Environment *env, CLIPSValue *values, size_t values_length, CLIPSValue *ret){
	int errret = 0;
	CLIPSValue errval = {.voidValue = VoidConstant(env)};
	Multifield *items;
	MultifieldBuilder *mb;
	if (values_length == -1){ //?why does only == -1 work?
		return 2;
	}
	if (values == NULL && values_length > 0){
		return 4;
	}
	mb = CreateMultifieldBuilder(env, values_length);
	if (mb == NULL){
		return 3;
	}

	for (int i=0; i<values_length; i++){
		MBAppend(mb, values + i);
	}
	items = MBCreate(mb);
	MBDispose(mb);
	if (items == NULL){
		return 4;
	}

	FactBuilder *fb;
	FactBuilderError err;
	fb = CreateFactBuilder(env, "AtomList");
	switch(FBPutSlotMultifield(fb, "items", items)){
		case PSE_NO_ERROR:
			break;
		default:
			FBDispose(fb); return 1;
	}
	errret = 0;
	Fact *retfact = FBAssert(fb);
	switch (FBError(env)){
		case FBE_NO_ERROR:
			if (retfact != NULL){
				ret->factValue = retfact;
			} else {
				errret = 1;
			}
			break;
		case FBE_COULD_NOT_ASSERT_ERROR:
			//TODO: Cant assert during pattern-matching
			ret->multifieldValue = items;
			break;
		default:
			errret = 2;
			ret->voidValue = VoidConstant(env);
			//errval.lexemeValue = CreateString(env, "make-list "
			//		"failed due to unknown reasons.");
			//SetErrorValue(env, errval.header);
			break;
	}
	FBDispose(fb);
	return errret;
}


Fact *crifi_list_intersect(Environment *env, CLIPSValue leftlist, CLIPSValue rightlist){
	int err;
	IEQ_RET check;
	size_t newlist_length = 0;
	size_t left_items_length, right_items_length;
	CLIPSValue right_mf_items, *right_items;
	CLIPSValue left_mf_items, *left_items;

	CLIPSValue *newitems, *tmpptr;
	CLIPSValue ret = {.voidValue = VoidConstant(env)};

	if (!retrieve_items(env, leftlist, &left_mf_items)) return NULL;
	if (!retrieve_items(env, rightlist, &right_mf_items)) return NULL;

	left_items = left_mf_items.multifieldValue->contents;
	right_items = right_mf_items.multifieldValue->contents;
	left_items_length = left_mf_items.multifieldValue->length;
	right_items_length = right_mf_items.multifieldValue->length;

	newitems = calloc(left_items_length, sizeof(CLIPSValue));
	tmpptr = newitems;
	for (int i=0; i < left_items_length; i++){
		check = IEQ_FALSE;
		for (int j=0; j<right_items_length; j++){
			check = internal_equal(env, left_items + i, right_items + j);
			if (check != IEQ_FALSE) break;
		}
		if (check == IEQ_TRUE){
			tmpptr->value = left_items[i].value;
			newlist_length++;
			tmpptr++;
		} else if (check == IEQ_ERROR){
			free(newitems);
			return NULL;
		}
	}
	err = crifi_list_new(env, newitems, newlist_length, &ret);
	free(newitems);
	if (err == 0){
		return ret.factValue;
	} else {
		return NULL;
	}
}

int crifi_list_except(Environment *env, CLIPSValue list, CLIPSValue exceptions, CLIPSValue *ret){
	IEQ_RET check;
	int err;
	size_t newlist_length = 0;
	size_t left_items_length, right_items_length;
	CLIPSValue right_mf_items, *right_items;
	CLIPSValue left_mf_items, *left_items;

	CLIPSValue *newitems, *tmpptr;

	if (!retrieve_items(env, list, &left_mf_items)) return 1;
	if (!retrieve_items(env, exceptions, &right_mf_items)) return 1;

	left_items = left_mf_items.multifieldValue->contents;
	right_items = right_mf_items.multifieldValue->contents;
	left_items_length = left_mf_items.multifieldValue->length;
	right_items_length = right_mf_items.multifieldValue->length;

	newitems = calloc(left_items_length, sizeof(CLIPSValue));
	tmpptr = newitems;
	for (int i=0; i < left_items_length; i++){
		check = IEQ_FALSE;
		for (int j=0; j<right_items_length; j++){
			check = internal_equal(env, left_items + i, right_items + j);
			if (check != IEQ_FALSE) break;
		}
		if (check == IEQ_FALSE){
			tmpptr->value = left_items[i].value;
			newlist_length++;
			tmpptr++;
		} else if (check == IEQ_ERROR){
			free(newitems);
			return 1;
		}
	}
	err = crifi_list_new(env, newitems, newlist_length, ret);
	free(newitems);
	return err;
}

bool crifi_is_list(Environment *env, CLIPSValue *arglist){
	Deftemplate *listtempl, *facttempl;
	if (arglist == NULL) return false;
	if (arglist->header->type != FACT_ADDRESS_TYPE){
		return false;
	}
	listtempl = FindDeftemplate(env, ATOMLISTTEMPLATE);
	facttempl = FactDeftemplate(arglist->factValue);
	if (facttempl == listtempl){
		return true;
	}
	return false;
}

int crifi_list_count(Environment *env, CLIPSValue *list){
	size_t length;
	CLIPSValue items;
	if (!retrieve_items(env, *list, &items)){
		return -1;
	}
	length = items.multifieldValue->length;
	return length;
}

bool crifi_list_as_identifier(Environment *env, CLIPSValue *val, int index, CLIPSValue *target){
	Fact *f;
	char* ret;
	long long factindex;
	int length, err;
	if (val->header->type != FACT_ADDRESS_TYPE) return false;
	length = crifi_list_count(env, val);
	if (index >= length){
		err = uri_to_clipsvalue(env, _RDF_nil_, strlen(_RDF_nil_), target);
		return err == 0;

	}
       	f = val->factValue;
	factindex = FactIndex(f);
	ret = malloc(24 + 12 + sizeof("factlistp") + 1);
	if (ret == NULL) return NULL;
	sprintf(ret, "factlist%ldp%d", factindex, index);

	err = blanknode_from_idstring(env, ret, target);
	return err == 0;
}



bool retrieve_items(Environment *env, CLIPSValue arglist, CLIPSValue *items){
	Deftemplate *factClass;
	Fact *superlist;
	switch (arglist.header->type) {
		case FACT_ADDRESS_TYPE:
			superlist = arglist.factValue;
			break;
		case MULTIFIELD_TYPE:
			items->value = arglist.value;
			return true;
		case SYMBOL_TYPE:
			if (0 == strcmp(_RDF_nil_,
					arglist.lexemeValue->contents))
			{
				return 0 == crifi_list_new(env, NULL, 0, items);
			}
			return false;
		default:
			return false;
	}

	factClass = FactDeftemplate(superlist);
	if(0 != strcmp("AtomList", DeftemplateName(factClass))){
		return false;
	}
	switch (GetFactSlot(superlist, "items", items)) {
		case GSE_NO_ERROR:
			return true; break;
		default:
			return false;
	}
}
