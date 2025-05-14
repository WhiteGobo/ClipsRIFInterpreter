#include <clips.h>
#include "pred_user_defined_functions.h"
#include "info_query.h"

#include "errormanagment.h"

#define RETURNFAIL(failure) \
		crifi_udf_error(env, failure, out);\
		return;

#define RETURNONVOID(env, udfval)\
		if(udfval.voidValue == VoidConstant(env)){return;}

/**
 * Compares two literal strings on equality.
 * No checks for correct arguments.
 */
void pred_literal_not_identical(Environment *env, UDFContext *udfc, UDFValue *out){
	unsigned long l;
	UDFValue val1, val2;
	if (!UDFFirstArgument(udfc, STRING_BIT, &val1)){
		RETURNFAIL("pred:literal-not-identical needs 2 arguments.")
	}
	if(!UDFNextArgument(udfc, STRING_BIT, &val2)){
		RETURNFAIL("pred:literal-not-identical needs 2 arguments.")
	}
	l = strlen(val1.lexemeValue->contents);
	if (l != strlen(val2.lexemeValue->contents)){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	} else if (0 != strcmp(val1.lexemeValue->contents, val2.lexemeValue->contents)){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	} else {
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
}


void rif_cast_as(Environment *env, UDFContext *udfc, UDFValue *out){
	int err;
	CLIPSValue newclipsval;
	char *lexical;
	const char *uri = (const char*) udfc->context;
	UDFValue myval;
	CLIPSValue cpyval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error for rif_cast_as");
		UDFThrowError(udfc);
		return;
	}
	lexical = extract_lexical(env, myval.header);
	if (lexical == NULL){
		Writeln(env, "Argument Error for rif_cast_as");
		UDFThrowError(udfc);
		return;
	}

	err = value_and_datatype_to_clipsvalue(env, lexical, strlen(lexical), uri, strlen(uri), &newclipsval);
	free(lexical);
	if (err == 0){
		out->value = newclipsval.value;
	} else {
		Writeln(env, "rif_cast_as failed");
		UDFThrowError(udfc);
		return;
	}
}


void check_datatype(Environment *env, UDFContext *udfc, UDFValue *out){
	const char* datatype = (const char*) udfc->context;
	bool tmpb;
	UDFValue val;
	if (!UDFFirstArgument(udfc, STRING_BIT, &val)){
		Write(env, "Argument Error for check datatype");
		Writeln(env, datatype);
		UDFThrowError(udfc);
		return;
	}
	FINDDATATYPE(dt_pos, dt_length, val.lexemeValue);
	tmpb = (0 == strcmp(dt_pos, datatype));
	out->lexemeValue = CreateBoolean(env, tmpb);
}

void check_not_datatype(Environment *env, UDFContext *udfc, UDFValue *out){
	const char* datatype = (const char*) udfc->context;
	bool tmpb;
	UDFValue val;
	if (!UDFFirstArgument(udfc, STRING_BIT, &val)){
		Write(env, "Argument Error for check datatype");
		Writeln(env, datatype);
		UDFThrowError(udfc);
		return;
	}
	FINDDATATYPE(dt_pos, dt_length, val.lexemeValue);
	tmpb = (0 != strcmp(dt_pos, datatype));
	out->lexemeValue = CreateBoolean(env, tmpb);
}
