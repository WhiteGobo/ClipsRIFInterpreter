#include "external_functions.h"

#include "list_user_defined_functions.h"
#include "own_user_defined_functions.h"
#include <crifi_lists.h>
#include <crifi_objects.h>

#include <n3parser.h>

#define RETURNARGERROR(fooname) \
		SetErrorValue(env, &(CreateString(env, "Argument Error for "fooname)->header));\
		return;

#define RETURNFAIL(failure) \
		SetErrorValue(env, &(CreateString(env, failure)->header));\
		return;


void pred_is_list(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue myval;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &myval)){
		return;
		//RETURNARGERROR("pred_is_list");
	}
	if (myval.header->type != INSTANCE_NAME_TYPE)
		out->lexemeValue = CreateBoolean(env, false);

	out->lexemeValue = CreateBoolean(env, true);
}


void pred_list_contains(Environment *env, UDFContext *udfc, UDFValue *out){
	IEQ_RET check;
	UDFValue arglist, entry;
	CLIPSValue entry_dupl, items;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &arglist)){
		RETURNARGERROR("list_contains");
	}
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &entry)){
		RETURNARGERROR("list_contains");
	}
	if (!retrieve_items_udf(env, arglist, &items)){
		RETURNARGERROR("Cant handle given list.");
	}
	entry_dupl.header = entry.header;
	for(int i = 0; i < items.multifieldValue->length; i++){
		check = internal_equal(env, &entry_dupl,
				items.multifieldValue->contents + i);
		if (check == IEQ_TRUE){
			out->lexemeValue = CreateBoolean(env, true);
			return;
		} else if (check == IEQ_ERROR){
			RETURNARGERROR("brubru");
		}
	}
	out->lexemeValue = CreateBoolean(env, false);
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
			fprintf(stderr, "something went wrong in getargsize\n");
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
			fprintf(stderr, "something went wrong in getargsize\n");
			return 0;
	}
}


static Instance* intern_make_list(Environment *env, CLIPSValue *values, size_t values_length){
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

void func_make_list(Environment *env, UDFContext *udfc, UDFValue *out){
	Instance* retinstance;
	unsigned int l = UDFArgumentCount(udfc);
	UDFValue tmpval;
	CLIPSValue myval[l+1];
	if (!UDFFirstArgument(udfc, STRING_BIT, &tmpval)){
		RETURNARGERROR("func_make_list");
	}
	myval[0].value = tmpval.value;
	for (int i=1; i<l; i++){
		if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpval)){
			RETURNARGERROR("func_make_list");
		}
		myval[i].value = tmpval.value;
	}
	retinstance = intern_make_list(env, myval, l);
	if (retinstance != NULL){
		out->instanceValue = retinstance;
	}
	//out->lexemeValue = CreateInstanceName(env, InstanceName(retinstance));
}


void func_count(Environment *env, UDFContext *udfc, UDFValue *out){
	const char *list_name;
	size_t length;
	GetSlotError err;
	CLIPSValue items;
	UDFValue list;
	Instance *list_inst;
	Defclass *argclass, *atomListClass;

	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &list)){
		RETURNFAIL("func_count requires instance of type AtomList");
	}
	if (list.header->type == VOID_TYPE) {
		return;
	} else if (list.header->type == INSTANCE_NAME_TYPE) {
		list_name = list.lexemeValue->contents;
		list_inst = FindInstance(env, NULL, list_name, true);
	} else if (list.header->type == INSTANCE_ADDRESS_TYPE) {
		list_inst = list.instanceValue;
	} else {RETURNFAIL("AtomList not defined");}
	atomListClass = FindDefclass(env, "AtomList");
	if (atomListClass == NULL){RETURNFAIL("AtomList not defined");}
	argclass = InstanceClass(list_inst);
	if (argclass != atomListClass){
		RETURNFAIL("Argument error. func_count requires AtomList");
	}
	err = DirectGetSlot(list_inst, "items", &items);
	if (err != GSE_NO_ERROR || items.header->type != MULTIFIELD_TYPE) {
		RETURNFAIL("compare_lists: couldnt get items of left");
	}
	length = items.multifieldValue->length;
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
	UDFValue arglist, entry;
	CLIPSValue val_arglist;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &arglist)){
		RETURNARGERROR("list_contains");
	}
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &entry)){
		RETURNARGERROR("list_contains");
	}
	val_arglist.value = arglist.value;
	if (!udfvalue_as_integer(entry, &i)) return;
	out->value = crifi_list_get(env, val_arglist, i).value;
}

void func_sublist(Environment *env, UDFContext *udfc, UDFValue *out){
	long long start, end;
	size_t length;
	IEQ_RET check;
	UDFValue arglist, start_val, end_val;
	CLIPSValue entry_dupl, items;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &arglist)){
		RETURNARGERROR("func_sublist");
	}
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &start_val)){
		RETURNARGERROR("func_sublist");
	}
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &end_val)){
		RETURNARGERROR("func_sublist");
	}
	if (true){//if number args == 3
		if (!retrieve_items_udf(env, arglist, &items)){
			RETURNARGERROR("Cant handle given list.");
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
	out->instanceValue = intern_make_list(env,
			items.multifieldValue->contents + start,
			end - start);
}

void func_append(Environment *env, UDFContext *udfc, UDFValue *out){
	size_t listlength;
	unsigned arglength;
	UDFValue firstarg, tmparg;
	CLIPSValue list;
	CLIPSValue *newvalues, *tmpptr;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &firstarg)){
		RETURNARGERROR("func_append");
	}
	if (!retrieve_items_udf(env, firstarg, &list)){
		RETURNARGERROR("Cant handle given list.");
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
			RETURNARGERROR("func_append");
		}
		tmpptr->value = tmparg.value;
		tmpptr++;
	}
	out->instanceValue = intern_make_list(env, newvalues,
						listlength+arglength -1);
	free(newvalues);
}

void func_concatenate(Environment *env, UDFContext *udfc, UDFValue *out){
	long long start, end;
	unsigned argcount = UDFArgumentCount(udfc);
	IEQ_RET check;
	Instance *newlist;
	UDFValue tmparg;
	CLIPSValue firstlist, secondlist;
	CLIPSValue listlist[argcount];
	CLIPSValue ret;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmparg)){
		RETURNARGERROR("func_sublist");
	}
	listlist[0].value = tmparg.value;
	for (int i=1; i<argcount; i++){
		if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmparg)){
			RETURNARGERROR("func_sublist");
		}
		listlist[i].value = tmparg.value;
	}
	newlist = crifi_list_concatenate(env, listlist, argcount);
	if (newlist != NULL) out->instanceValue = newlist;
}


void func_insert_before(Environment *env, UDFContext *udfc, UDFValue *out){
	long long position;
	size_t listlength;
	unsigned arglength;
	UDFValue firstarg, positionarg, newvalarg;
	CLIPSValue list;
	CLIPSValue *newvalues, *tmpptr;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &firstarg)){
		RETURNARGERROR("func_insert_before");
	}
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &positionarg)){
		RETURNARGERROR("func_insert_before");
	}
	if (!udfvalue_as_integer(positionarg, &position)) return;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &newvalarg)){
		RETURNARGERROR("func_insert_before");
	}
	if (!retrieve_items_udf(env, firstarg, &list)){
		RETURNFAIL("Cant handle given list.");
	}
	listlength = list.multifieldValue->length;
	if (!normalize_index(listlength, &position)){
		RETURNFAIL("cant insert at given position");
	}
	newvalues = calloc(listlength + 1, sizeof(CLIPSValue));
	tmpptr = newvalues;
	for (int i=0; i<position; i++){
		tmpptr->value = list.multifieldValue->contents[i].value;
		tmpptr++;
	}
	tmpptr->value = newvalarg.value;
	tmpptr++;
	for (int i=position; i<listlength; i++){
		tmpptr->value = list.multifieldValue->contents[i].value;
		tmpptr++;
	}
	out->instanceValue = intern_make_list(env, newvalues,
						listlength+1);
	free(newvalues);
}

void func_remove(Environment *env, UDFContext *udfc, UDFValue *out){
	long long position;
	size_t listlength;
	unsigned arglength;
	UDFValue firstarg, positionarg, newvalarg;
	CLIPSValue list;
	CLIPSValue *newvalues, *tmpptr;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &firstarg)){
		RETURNARGERROR("func_insert_before");
	}
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &positionarg)){
		RETURNARGERROR("func_insert_before");
	}
	if (!udfvalue_as_integer(positionarg, &position)) return;
	if (!retrieve_items_udf(env, firstarg, &list)){
		RETURNFAIL("Cant handle given list.");
	}
	listlength = list.multifieldValue->length;
	if (!normalize_index(listlength, &position)){
		RETURNFAIL("cant insert at given position");
	}
	newvalues = calloc(listlength - 1, sizeof(CLIPSValue));
	tmpptr = newvalues;
	for (int i=0; i<position; i++){
		tmpptr->value = list.multifieldValue->contents[i].value;
		tmpptr++;
	}
	for (int i=position+1; i<listlength; i++){
		tmpptr->value = list.multifieldValue->contents[i].value;
		tmpptr++;
	}
	out->instanceValue = intern_make_list(env, newvalues, listlength-1);
	free(newvalues);
}

void func_reverse(Environment *env, UDFContext *udfc, UDFValue *out){
	size_t listlength;
	unsigned arglength;
	UDFValue firstarg;
	CLIPSValue list;
	CLIPSValue *newvalues, *tmpptr;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &firstarg)){
		RETURNARGERROR("func_insert_before");
	}
	if (!retrieve_items_udf(env, firstarg, &list)){
		RETURNFAIL("Cant handle given list.");
	}
	listlength = list.multifieldValue->length;
	newvalues = calloc(listlength, sizeof(CLIPSValue));
	tmpptr = newvalues;
	for (int i=listlength-1; i>=0; i--){
		tmpptr->value = list.multifieldValue->contents[i].value;
		tmpptr++;
	}
	out->instanceValue = intern_make_list(env, newvalues, listlength);
	free(newvalues);
}

void func_index_of(Environment *env, UDFContext *udfc, UDFValue *out){
	size_t listlength;
	IEQ_RET check;
	unsigned long long newvalues_length = 0;
	unsigned arglength;
	UDFValue firstarg, cmparg;
	CLIPSValue list;
	CLIPSValue *newvalues, *tmpptr;
	CLIPSValue tmpval, cmpval;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &firstarg)){
		RETURNARGERROR("func_insert_before");
	}
	if (!retrieve_items_udf(env, firstarg, &list)){
		RETURNFAIL("Cant handle given list.");
	}
	listlength = list.multifieldValue->length;

	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &cmparg)){
		RETURNARGERROR("func_insert_before");
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
	out->instanceValue = intern_make_list(env, newvalues, newvalues_length);
	free(newvalues);
}


void func_union(Environment *env, UDFContext *udfc, UDFValue *out){
	long long start, end;
	unsigned argcount = UDFArgumentCount(udfc);
	IEQ_RET check;
	Instance *newlist;
	UDFValue tmparg;
	CLIPSValue tmpval;
	CLIPSValue firstlist, secondlist;
	CLIPSValue listlist[argcount];
	CLIPSValue ret;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmparg)){
		RETURNARGERROR("func_sublist");
	}
	listlist[0].value = tmparg.value;
	for (int i=1; i<argcount; i++){
		if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmparg)){
			RETURNARGERROR("func_sublist");
		}
		listlist[i].value = tmparg.value;
	}
	newlist = crifi_list_concatenate(env, listlist, argcount);
	if (newlist == NULL) return;
	tmpval.instanceValue = newlist;
	newlist = crifi_list_distinct_values(env, tmpval);
	if (newlist != NULL) out->instanceValue = newlist;
}

void func_distinct_values(Environment *env, UDFContext *udfc, UDFValue *out){
	size_t listlength;
	IEQ_RET check;
	Instance *newlist;
	UDFValue firstarg, secondarg;
	CLIPSValue firstval;
	CLIPSValue firstlist, secondlist;
	CLIPSValue entry_dupl, items;
	CLIPSValue *newvalues, *tmpptr, *values;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &firstarg)){
		RETURNARGERROR("func_distinct_values");
	}
	firstval.value = firstarg.value;
	newlist = crifi_list_distinct_values(env, firstval);
	if (newlist != NULL) out->instanceValue = newlist;
}

void func_intersect(Environment *env, UDFContext *udfc, UDFValue *out){
	Instance *newlist;
	UDFValue leftarg, rightarg;
	CLIPSValue leftlist, rightlist;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &leftarg)){
		RETURNARGERROR("func_sublist");
	}
	leftlist.value = leftarg.value;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &rightarg)){
		RETURNARGERROR("func_sublist");
	}
	rightlist.value = rightarg.value;

	newlist = crifi_list_intersect(env, leftlist, rightlist);
	if (newlist != NULL) out->instanceValue = newlist;
}

void func_except(Environment *env, UDFContext *udfc, UDFValue *out){
	Instance *newlist;
	UDFValue leftarg, rightarg;
	CLIPSValue leftlist, rightlist;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &leftarg)){
		RETURNARGERROR("func_sublist");
	}
	leftlist.value = leftarg.value;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &rightarg)){
		RETURNARGERROR("func_sublist");
	}
	rightlist.value = rightarg.value;

	newlist = crifi_list_except(env, leftlist, rightlist);
	if (newlist != NULL) out->instanceValue = newlist;
}


#undef RETURNARGERROR
#undef RETURNFAIL
