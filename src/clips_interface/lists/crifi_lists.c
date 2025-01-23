#include "crifi_lists.h"

#include <crifi_objects.h>

/**
 * returns success
 */
static bool normalize_index(size_t length, long long *index){
	//compare size_t with long long only safe if positive
	//see `https://stackoverflow.com/questions/3642010/can-i-compare-int-with-size-t-directly-in-c`_
	if (*index>0 && *index >= length) return false;
	if (*index<0){
		*index += length;
		if (*index<0) return false;
	}
	return true;
}

/**
 *
 * TODO: consider to use Multifield for items instead
 */
bool retrieve_items_udf(Environment *env, UDFValue arglist, CLIPSValue *items){
	CLIPSValue cpy_arglist;
	cpy_arglist.value = arglist.value;
	return retrieve_items(env, cpy_arglist, items);
}

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

bool retrieve_items(Environment *env, CLIPSValue arglist, CLIPSValue *items){
	Deftemplate *factClass;
	Fact *superlist;
	switch (arglist.header->type) {
		case FACT_ADDRESS_TYPE:
			superlist = arglist.factValue;
			break;
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


CLIPSValue crifi_list_get(Environment *env, CLIPSValue list, long long index){
	size_t length;
	long long i = index;
	CLIPSValue ret, items;
	if (!retrieve_items(env, list, &items)){
		ret.value = NULL;
		return ret;
	}
	length = items.multifieldValue->length;
	if (!normalize_index(length, &i)){ret.value =NULL; return ret;}
	ret.value = items.multifieldValue->contents[i].value;
	return ret;
}

Fact *crifi_list_concatenate(Environment *env, CLIPSValue *listlist, size_t listlist_length){
	Fact *ret;
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
	ret = crifi_list_new(env, newvalues, newlist_length);
	free(newvalues);
	return ret;
}


Fact *crifi_list_distinct_values(Environment *env, CLIPSValue list){
	IEQ_RET check;
	size_t newlist_length = 0;
	CLIPSValue mf_items, *items;
	CLIPSValue *newitems, *tmpptr;
	Fact *ret;

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
	ret = crifi_list_new(env, newitems, newlist_length);
	free(newitems);
	return ret;
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

Fact* crifi_list_new(Environment *env, CLIPSValue *values, size_t values_length){
	Fact* ret;

	//printf("asdf %d\n", values[0].header->type);
	Multifield *items;
	MultifieldBuilder *mb;
	mb = CreateMultifieldBuilder(env, values_length);
	for (int i=0; i<values_length; i++){
		MBAppend(mb, values + i);
	}
	items = MBCreate(mb);
	MBDispose(mb);

	FactBuilder *fb;
	FactBuilderError err;
	fb = CreateFactBuilder(env, "AtomList");
	switch(FBPutSlotMultifield(fb, "items", items)){
		case PSE_NO_ERROR:
			break;
		default:
			FBDispose(fb); return NULL;
	}
	ret = FBAssert(fb);
	switch (FBError(env)){
		case FBE_NO_ERROR:
			break;
		default:
			FBDispose(fb); return NULL;
	}
	FBDispose(fb);
	return ret;
}


Fact *crifi_list_intersect(Environment *env, CLIPSValue leftlist, CLIPSValue rightlist){
	IEQ_RET check;
	size_t newlist_length = 0;
	size_t left_items_length, right_items_length;
	CLIPSValue right_mf_items, *right_items;
	CLIPSValue left_mf_items, *left_items;

	CLIPSValue *newitems, *tmpptr;
	Fact *ret;

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
	ret = crifi_list_new(env, newitems, newlist_length);
	free(newitems);
	return ret;
}

Fact *crifi_list_except(Environment *env, CLIPSValue list, CLIPSValue exceptions){
	IEQ_RET check;
	size_t newlist_length = 0;
	size_t left_items_length, right_items_length;
	CLIPSValue right_mf_items, *right_items;
	CLIPSValue left_mf_items, *left_items;

	CLIPSValue *newitems, *tmpptr;
	Fact *ret;

	if (!retrieve_items(env, list, &left_mf_items)) return NULL;
	if (!retrieve_items(env, exceptions, &right_mf_items)) return NULL;

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
			return NULL;
		}
	}
	ret = crifi_list_new(env, newitems, newlist_length);
	free(newitems);
	return ret;
}
