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

bool retrieve_items(Environment *env, CLIPSValue arglist, CLIPSValue *items){
	Defclass *atomListClass;
	Instance *superlist;
	switch (arglist.header->type) {
		case INSTANCE_NAME_TYPE:
			//eval(env, "(send %s get-items)", items);
			//return true;
			superlist = FindInstance(env, NULL,
					arglist.lexemeValue->contents, true);
			break;
		case INSTANCE_ADDRESS_TYPE:
			superlist = arglist.instanceValue;
			break;
		default:
			return false;
	}

	atomListClass = FindDefclass(env, "AtomList");
	if (atomListClass == NULL) return false;
	if (InstanceClass(superlist) != atomListClass) return false;
	if (GSE_NO_ERROR != DirectGetSlot(superlist, "items", items)) {
		return false;
	}
	return true;
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

Instance *crifi_list_concatenate(Environment *env, CLIPSValue *listlist, size_t listlist_length){
	CLIPSValue ret;
	size_t newlist_length = 0;
	CLIPSValue items[listlist_length];
	CLIPSValue *newvalues, *tmpptr;
	Instance *newlist;
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
	return crifi_list_new(env, newvalues, newlist_length);
}


Instance *crifi_list_distinct_values(Environment *env, CLIPSValue list){
	IEQ_RET check;
	size_t newlist_length = 0;
	CLIPSValue mf_items, *items;
	CLIPSValue *newitems, *tmpptr;
	Instance *ret;

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
			fprintf(stderr, "something went wrong in getargsize\n");
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
			fprintf(stderr, "something went wrong in getargsize\n");
	}
}

Instance* crifi_list_new(Environment *env, CLIPSValue *values, size_t values_length){
	Instance* ret;
	MakeInstanceError err;
	char *command, *cptr;
	size_t argsize, delta;
	argsize=1;
	for (int i=0; i<values_length; i++){
		argsize += 1 + get_argsize(values[i]);
	}
	command = malloc(sizeof("(of AtomList (items))")+ argsize);
	cptr = command;
 	delta = sprintf(cptr, "(of AtomList (items");
	cptr += delta;
	for (int i=0; i<values_length; i++){
		delta = sprintf_arg(cptr, " %s", values[i]);
		//if(delta == 0) return NULL;
		cptr += delta;
	}
	sprintf(cptr, "))");

	ret = MakeInstance(env, command);
	printf("failed to create list with command: %s\n", command);
	//alternativly use IBMake
	err = GetMakeInstanceError(env);

	switch (err){
		case MIE_NO_ERROR:
			break;
		case MIE_NULL_POINTER_ERROR:
		case MIE_PARSING_ERROR:
		case MIE_COULD_NOT_CREATE_ERROR:
			fprintf(stderr, "failed to create list with command: %s\n", command);
			break;
	}
	free(command);
	return ret;
}


Instance *crifi_list_intersect(Environment *env, CLIPSValue leftlist, CLIPSValue rightlist){
	IEQ_RET check;
	size_t newlist_length = 0;
	size_t left_items_length, right_items_length;
	CLIPSValue right_mf_items, *right_items;
	CLIPSValue left_mf_items, *left_items;

	CLIPSValue *newitems, *tmpptr;
	Instance *ret;

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

Instance *crifi_list_except(Environment *env, CLIPSValue list, CLIPSValue exceptions){
	IEQ_RET check;
	size_t newlist_length = 0;
	size_t left_items_length, right_items_length;
	CLIPSValue right_mf_items, *right_items;
	CLIPSValue left_mf_items, *left_items;

	CLIPSValue *newitems, *tmpptr;
	Instance *ret;

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
