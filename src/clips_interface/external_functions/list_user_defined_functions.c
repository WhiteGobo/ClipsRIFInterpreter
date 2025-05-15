#include "external_functions.h"

#include "list_user_defined_functions.h"
#include "own_user_defined_functions.h"
#include <crifi_lists.h>
#include <crifi_objects.h>
#include "crifi_numeric.h"

#include "info_query.h"
#include "errormanagment.h"

#define RETURNFAIL(failure) \
		crifi_udf_error(env, failure, out);\
		return;

#define RETURNONVOID(env, udfval)\
		if(udfval.voidValue == VoidConstant(env)){return;}


void pred_is_list(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue myval;
	CLIPSValue val;
	out->lexemeValue = FalseSymbol(env); //default output
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &myval)){
		return;
		//RETURNFAIL("pred_is_list");
	}
	RETURNONVOID(env, myval);
	val.header = myval.header;
	out->lexemeValue = CreateBoolean(env, crifi_is_list(env, &val));
}

void pred_list_contains(Environment *env, UDFContext *udfc, UDFValue *out){
	IEQ_RET check;
	UDFValue arglist, entry;
	CLIPSValue c_arglist = {.voidValue=VoidConstant(env)};
	CLIPSValue entry_dupl = {.voidValue=VoidConstant(env)};
	CLIPSValue items = {.voidValue=VoidConstant(env)};
	out->lexemeValue = FalseSymbol(env); //default output
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &arglist)){
		RETURNFAIL("list_contains");
	}
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &entry)){
		RETURNFAIL("list_contains");
	}
	c_arglist.value = arglist.value;
	if (!retrieve_items(env, c_arglist, &items)){
		RETURNFAIL("Cant handle given list.");
	}
	entry_dupl.header = entry.header;
	for(int i = 0; i < items.multifieldValue->length; i++){
		check = internal_equal(env, &entry_dupl,
				items.multifieldValue->contents + i);
		if (check == IEQ_TRUE){
			out->lexemeValue = CreateBoolean(env, true);
			break;
		} else if (check == IEQ_ERROR){
			RETURNFAIL("pred_list_contains");
		}
	}
}

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



void func_make_list(Environment *env, UDFContext *udfc, UDFValue *out){
	Fact* ret;
	CLIPSValue tmpout = {.voidValue = VoidConstant(env)};
	unsigned int l = UDFArgumentCount(udfc);
	UDFValue tmpval;
	CLIPSValue myval[l+1];
	if (l > 0){
		if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpval)){
			RETURNFAIL("func_make_list");
		}
		myval[0].value = tmpval.value;
		for (int i=1; i<l; i++){
			if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpval)){
				RETURNFAIL("func_make_list");
			}
			myval[i].value = tmpval.value;
		}
	}
	if (0 == crifi_list_new(env, myval, l, &tmpout)){
		out->value = tmpout.value;
	} else {
		RETURNFAIL("Failed to create new crifi_list.");
	}
}


void func_count(Environment *env, UDFContext *udfc, UDFValue *out){
	size_t length;
	GetSlotError err;
	CLIPSValue items;
	UDFValue list_udfvalue;
	CLIPSValue list_clipsvalue;
	Defclass *argclass, *atomListClass;

	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &list_udfvalue)){
		RETURNFAIL("func_count requires instance of type AtomList");
	}
	list_clipsvalue.value = list_udfvalue.value;
	length = crifi_list_count(env, &list_clipsvalue);
	if (length < 0){
		RETURNFAIL("Argument error. func_count requires AtomList");
	}

	TEMPORARYINTERNALREPRESENTATION(tmpi, length, 11, "%d", _XS_integer_);
	out->lexemeValue = CreateString(env, tmpi);
}

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

void func_get(Environment *env, UDFContext *udfc, UDFValue *out){
	long long i;
	int err2;
	CRIFI_LIST_GET_RET err;
	UDFValue arglist, udf_index;
	CLIPSValue val_arglist, clips_index, tmpout;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &arglist)){
		RETURNFAIL("list_contains");
	}
	RETURNONVOID(env, arglist);
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &udf_index)){
		RETURNFAIL("list_contains");
	}
	RETURNONVOID(env, udf_index);
	val_arglist.value = arglist.value;

	clips_index.value = udf_index.value;
	if(!clipsvalue_as_integer(env, clips_index, &i)){
		RETURNFAIL("func:get expects an integer as second argument.");
	}
	err = crifi_list_get(env, val_arglist, i, &tmpout);

	switch (err){
		case CRIFI_LIST_GET_NOERROR:
			break;
		case CRIFI_LIST_GET_INDEX:
			tmpout.voidValue = VoidConstant(env);
			//err2 = crifi_list_new(env, NULL, 0, &tmpout);
			//if (err2 != 0){
			//	RETURNFAIL("func:get internal error.");
			//}
			break;
		case CRIFI_LIST_GET_NOLIST:
			RETURNFAIL("func:get expects list as first argument.");
		default:
			RETURNFAIL("func:get produced unhandled error.");
	}
	out->value = tmpout.value;
}

void func_sublist(Environment *env, UDFContext *udfc, UDFValue *out){
	CLIPSValue tmpout = {.voidValue = VoidConstant(env)};
	long long start, end;
	size_t length;
	Fact *ret;
	IEQ_RET check;
	UDFValue udf_arglist, start_val, end_val;
	CLIPSValue clips_arglist;
	CLIPSValue entry_dupl, items;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udf_arglist)){
		RETURNFAIL("func_sublist");
	}
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &start_val)){
		RETURNFAIL("func_sublist");
	}
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &end_val)){
		RETURNFAIL("func_sublist");
	}
	if (true){//if number args == 3
		clips_arglist.value = udf_arglist.value;
		if (!retrieve_items(env, clips_arglist, &items)){
			RETURNFAIL("Cant handle given list.");
		}
	} else {
		end_val.value = NULL;
	}
	length = items.multifieldValue->length;
	if (!udfvalue_as_integer(start_val, &start)) return;
	if (end_val.value != NULL){
		if (!udfvalue_as_integer(end_val, &end)) return;
	} else {
		end = length;
	}
	if (!normalize_index(length, &start)) return;
	if (end != length && !normalize_index(length, &end)) return;
	if (start >= end) return;
	crifi_list_new(env,
			items.multifieldValue->contents + start,
			end - start, &tmpout);
	out->header = tmpout.header;
}

void func_append(Environment *env, UDFContext *udfc, UDFValue *out){
	size_t listlength;
	unsigned arglength;
	UDFValue udf_list, tmparg;
	CLIPSValue list, clips_list;
	CLIPSValue *newvalues, *tmpptr;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udf_list)){
		RETURNFAIL("func_append");
	}
	clips_list.value = udf_list.value;
	if (!retrieve_items(env, clips_list, &list)){
		RETURNFAIL("Cant handle given list.");
	}
	arglength = UDFArgumentCount(udfc);
	listlength = list.multifieldValue->length;
	newvalues = calloc(listlength + arglength -1, sizeof(CLIPSValue));
	tmpptr = newvalues;
	for (int i=0; i<listlength; i++){
		tmpptr->value = list.multifieldValue->contents[i].value;
		tmpptr++;
	}
	for (int i=1; i<arglength; i++){
		if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmparg)){
			free(newvalues);
			RETURNFAIL("func_append");
		}
		tmpptr->value = tmparg.value;
		tmpptr++;
	}
	CLIPSValue tmpout = {.voidValue = VoidConstant(env)};
	crifi_list_new(env, newvalues, listlength+arglength -1, &tmpout);
	out->header = tmpout.header;
	free(newvalues);
}

void func_concatenate(Environment *env, UDFContext *udfc, UDFValue *out){
	long long start, end;
	unsigned argcount = UDFArgumentCount(udfc);
	IEQ_RET check;
	Fact *newlist;
	UDFValue tmparg;
	CLIPSValue firstlist, secondlist;
	CLIPSValue listlist[argcount];
	CLIPSValue ret;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmparg)){
		RETURNFAIL("func_sublist");
	}
	listlist[0].value = tmparg.value;
	for (int i=1; i<argcount; i++){
		if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmparg)){
			RETURNFAIL("func_sublist");
		}
		listlist[i].value = tmparg.value;
	}
	newlist = crifi_list_concatenate(env, listlist, argcount);
	if (newlist != NULL){
		out->factValue = newlist;
	} else {
		out->voidValue = VoidConstant(env);
	}
}


void func_insert_before(Environment *env, UDFContext *udfc, UDFValue *out){
	long long position;
	size_t listlength;
	unsigned arglength;
	CLIPSValue tmpout = {.voidValue = VoidConstant(env)};
	UDFValue udf_list, positionarg, newvalarg;
	CLIPSValue list, clips_list;
	CLIPSValue *newvalues, *tmpptr;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udf_list)){
		RETURNFAIL("func_insert_before");
	}
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &positionarg)){
		RETURNFAIL("func_insert_before");
	}
	if (!udfvalue_as_integer(positionarg, &position)) return;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &newvalarg)){
		RETURNFAIL("func_insert_before");
	}
	clips_list.value = udf_list.value;
	if (!retrieve_items(env, clips_list, &list)){
		RETURNFAIL("Cant handle given list.");
	}
	listlength = list.multifieldValue->length;
	if (!normalize_index(listlength, &position)){
		RETURNFAIL("cant insert at given position");
	}
	newvalues = calloc(listlength + 1, sizeof(CLIPSValue));
	tmpptr = newvalues;
	for (int i=0; i<position; i++) {
		tmpptr->value = list.multifieldValue->contents[i].value;
		tmpptr++;
	}
	tmpptr->value = newvalarg.value;
	tmpptr++;
	for (int i=position; i<listlength; i++) {
		tmpptr->value = list.multifieldValue->contents[i].value;
		tmpptr++;
	}
	crifi_list_new(env, newvalues, listlength+1, &tmpout);
	out->header = tmpout.header;
	free(newvalues);
}

void func_remove(Environment *env, UDFContext *udfc, UDFValue *out){
	long long position;
	size_t listlength;
	unsigned arglength;
	UDFValue firstarg, positionarg, newvalarg;
	CLIPSValue list, newlist = {.voidValue = VoidConstant(env)};
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &firstarg)){
		RETURNFAIL("Argument error for func:remove.");
	}
	RETURNONVOID(env, firstarg);
	list.value = firstarg.value;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &positionarg)){
		RETURNFAIL("Argument error for func:remove.");
	}
	RETURNONVOID(env, positionarg);
	if (!udfvalue_as_integer(positionarg, &position)) return;

	CRIFI_LIST_REMOVE_RET err;
	err = crifi_list_remove(env, list, position, &newlist);
	switch (err){
		case CRIFI_LIST_REMOVE_NOERROR:
			break;
		case CRIFI_LIST_REMOVE_EMPTY_LIST:
			RETURNFAIL("func:remove cant use an empty list.");
		case CRIFI_LIST_REMOVE_NOLIST:
			RETURNFAIL("func:remove expects a list as "
					"first argument");
		case CRIFI_LIST_REMOVE_INDEX:
			RETURNFAIL("func:remove got an index which isnt "
					"in given list");
		case CRIFI_LIST_REMOVE_USAGE:
		case CRIFI_LIST_REMOVE_CREATE_LIST:
		case CRIFI_LIST_REMOVE_MALLOC:
		default:
			RETURNFAIL("func:remove failed with unknown error");
	}
	out->value = newlist.value;
}

void func_reverse(Environment *env, UDFContext *udfc, UDFValue *out){
	size_t listlength;
	unsigned arglength;
	UDFValue udf_list;
	CLIPSValue list, clips_list;
	CLIPSValue *newvalues, *tmpptr;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udf_list)){
		RETURNFAIL("func_insert_before");
	}
	clips_list.value = udf_list.value;
	if (!retrieve_items(env, clips_list, &list)){
		RETURNFAIL("Cant handle given list.");
	}
	listlength = list.multifieldValue->length;
	newvalues = calloc(listlength, sizeof(CLIPSValue));
	tmpptr = newvalues;
	for (int i=listlength-1; i>=0; i--){
		tmpptr->value = list.multifieldValue->contents[i].value;
		tmpptr++;
	}
	CLIPSValue tmpout = {.voidValue = VoidConstant(env)};
	crifi_list_new(env, newvalues, listlength, &tmpout);
	out->header = tmpout.header;
	free(newvalues);
}

void func_index_of(Environment *env, UDFContext *udfc, UDFValue *out){
	size_t listlength;
	IEQ_RET check;
	unsigned long long newvalues_length = 0;
	unsigned arglength;
	UDFValue udf_list, cmparg;
	CLIPSValue list, clips_list;
	CLIPSValue *newvalues, *tmpptr;
	CLIPSValue tmpval, cmpval;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udf_list)){
		RETURNFAIL("func_insert_before");
	}
	clips_list.value = udf_list.value;
	if (!retrieve_items(env, clips_list, &list)){
		RETURNFAIL("Cant handle given list.");
	}
	listlength = list.multifieldValue->length;

	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &cmparg)){
		RETURNFAIL("func_insert_before");
	}
	cmpval.value = cmparg.value;

	newvalues = calloc(listlength, sizeof(CLIPSValue));
	tmpptr = newvalues;
	for (int i=0; i<listlength; i++){
		tmpval.value = list.multifieldValue->contents[i].value;
		check = internal_equal(env, &tmpval, &cmpval);
		if(IEQ_TRUE ==check) {
			newvalues_length++;
			TEMPORARYINTERNALREPRESENTATION(tmpi, i, 11,\
					"%d", _XS_integer_);
			tmpptr->lexemeValue = CreateString(env, tmpi);
			tmpptr++;
		} else if (IEQ_ERROR == check){
			free(newvalues);
			return;
		}
	}
	CLIPSValue tmpout = {.voidValue = VoidConstant(env)};
	crifi_list_new(env, newvalues, newvalues_length, &tmpout);
	out->header = tmpout.header;
	free(newvalues);
}


void func_union(Environment *env, UDFContext *udfc, UDFValue *out){
	long long start, end;
	unsigned argcount = UDFArgumentCount(udfc);
	IEQ_RET check;
	Fact *newlist;
	UDFValue tmparg;
	CLIPSValue tmpval;
	CLIPSValue firstlist, secondlist;
	CLIPSValue listlist[argcount];
	CLIPSValue ret;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmparg)){
		RETURNFAIL("func_sublist");
	}
	listlist[0].value = tmparg.value;
	for (int i=1; i<argcount; i++){
		if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmparg)){
			RETURNFAIL("func_sublist");
		}
		listlist[i].value = tmparg.value;
	}
	newlist = crifi_list_concatenate(env, listlist, argcount);
	if (newlist == NULL) return;
	tmpval.factValue = newlist;
	newlist = crifi_list_distinct_values(env, tmpval);
	if (newlist != NULL) {
		out->factValue = newlist;
	} else {
		out->voidValue = VoidConstant(env);
	}
}

void func_distinct_values(Environment *env, UDFContext *udfc, UDFValue *out){
	size_t listlength;
	IEQ_RET check;
	Fact *newlist;
	UDFValue firstarg, secondarg;
	CLIPSValue firstval;
	CLIPSValue firstlist, secondlist;
	CLIPSValue entry_dupl, items;
	CLIPSValue *newvalues, *tmpptr, *values;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &firstarg)){
		RETURNFAIL("func_distinct_values");
	}
	firstval.value = firstarg.value;
	newlist = crifi_list_distinct_values(env, firstval);
	if (newlist != NULL) {
		out->factValue = newlist;
	} else {
		out->voidValue = VoidConstant(env);
	}
}

void func_intersect(Environment *env, UDFContext *udfc, UDFValue *out){
	Fact *newlist;
	UDFValue leftarg, rightarg;
	CLIPSValue leftlist, rightlist;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &leftarg)){
		RETURNFAIL("func_sublist");
	}
	leftlist.value = leftarg.value;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &rightarg)){
		RETURNFAIL("func_sublist");
	}
	rightlist.value = rightarg.value;

	newlist = crifi_list_intersect(env, leftlist, rightlist);
	if (newlist != NULL) {
		out->factValue = newlist;
	} else {
		out->voidValue = VoidConstant(env);
	}
}

void func_except(Environment *env, UDFContext *udfc, UDFValue *out){
	CLIPSValue tmpout = {.voidValue = VoidConstant(env)};
	Fact *newlist;
	UDFValue leftarg, rightarg;
	CLIPSValue leftlist, rightlist;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &leftarg)){
		RETURNFAIL("func_sublist");
	}
	leftlist.value = leftarg.value;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &rightarg)){
		RETURNFAIL("func_sublist");
	}
	rightlist.value = rightarg.value;

	crifi_list_except(env, leftlist, rightlist, &tmpout);
	out->header = tmpout.header;
}


#undef RETURNFAIL
