#include "own_user_defined_functions.h"
#include <crifi_objects.h>
#include "n3parser.h"
#include "info_query.h"

#define RETURNFAIL(failure, ret) \
		Writeln(env, failure);\
		SetErrorValue(env, &(CreateString(env, failure)->header));\
		return ret;


void clipsudf_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	CLIPSValue left_val, right_val;
	UDFValue left, right;
	IEQ_RET check;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &left))return;
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &right))return;
	if (left.header->type == VOID_TYPE || right.header->type == VOID_TYPE){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	left_val.value = left.value;
	right_val.value = right.value;
	check = internal_equal(env, &left_val, &right_val);
	switch (check){
		case IEQ_TRUE:
			out->lexemeValue = CreateBoolean(env, true);
			return;
			break;
		case IEQ_FALSE:
			out->lexemeValue = CreateBoolean(env, false);
			return;
			break;
	}
}


void clipsudf_import(Environment *env, UDFContext *udfc, UDFValue *out){
	char *qq = (char*) udfc->context;
	SetErrorValue(env, &(CreateString(env, "import isnt implemented")->header));
	out->lexemeValue = CreateString(env, "");
}

void clipsudf_new_blanknode(Environment *env, UDFContext *udfc, UDFValue *out){
	int err;
	CLIPSValue target;
	err = new_blanknode(env, &target);
	if (err == 0){
		out->value = target.value;
	} else {
		//RETURNFAIL();
	}
}

void clipsudf_iri_to_clipsconstant(Environment *env, UDFContext *udfc, UDFValue *out){
	int err;
	char *lexical, *result;
	CLIPSValue outclipsval;
	UDFValue input;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &input)) return;

	lexical = extract_lexical(env, input.header);
	if (lexical == NULL) return;

	result = genclipscode_iri(env, lexical);
	if (result == NULL){
		free(lexical);
		return;
	}
	err = value_and_datatype_to_clipsvalue(env,
			result, strlen(result), NULL, 0, &outclipsval);
	free(lexical);
	free(result);
	if (err==0){
		out->value = outclipsval.value;
	}
}

void clipsudf_literal_to_clipsconstant(Environment *env, UDFContext *udfc, UDFValue *out){
	int err;
	char *lexical, *result, *datatype;
	CLIPSValue outclipsval;
	UDFValue input;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &input)) return;

	lexical = extract_lexical(env, input.header);
	if (lexical == NULL) return;
	datatype = extract_datatype(env, input.header);
	if (datatype == NULL){
		free(datatype);
		return;
	}

	result = genclipscode_lexical(env, lexical, datatype);
	if (result == NULL){
		free(lexical);
		free(datatype);
		return;
	}

	err = value_and_datatype_to_clipsvalue(env,
			result, strlen(result), NULL, 0, &outclipsval);
	free(datatype);
	free(lexical);
	free(result);
	if (err==0){
		out->value = outclipsval.value;
	}
}

#undef RETURNFAIL
