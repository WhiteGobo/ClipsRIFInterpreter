#include <clips.h>
#include "pred_user_defined_functions.h"
#include "n3parser.h"

/**
 * Compares two literal strings on equality.
 * No checks for correct arguments.
 */
void pred_literal_not_identical(Environment *env, UDFContext *udfc, UDFValue *out){
	unsigned long l;
	UDFValue val1, val2;
	if (!UDFFirstArgument(udfc, STRING_BIT, &val1)){
		UDFThrowError(udfc);
	}
	if(!UDFNextArgument(udfc, STRING_BIT, &val2)){
		UDFThrowError(udfc);
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
	const char *uri = (const char*) udfc->context;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error for rif_cast_as");
		UDFThrowError(udfc);
		return;
	}
	//if myval.header != lexeme thingie
	FINDVALUE(value_pos, value_length, myval.lexemeValue);
	char newstring[value_length + strlen(uri) + sizeof("^^\0")];
	memcpy(newstring, value_pos, value_length);
	sprintf(newstring + value_length, "^^%s", uri);
	out->lexemeValue = CreateString(env, newstring);
}


void check_datatype(Environment *env, UDFContext *udfc, UDFValue *out){
	const char* datatype = (const char*) udfc->context;
	printf("\ncheck %s\n", datatype);
	bool tmpb;
	UDFValue val;
	if (!UDFFirstArgument(udfc, STRING_BIT, &val)){
		Write(env, "Argument Error for check datatype");
		Writeln(env, datatype);
		UDFThrowError(udfc);
		return;
	}
	printf("got arg: %s\n", val.lexemeValue->contents);
	FINDDATATYPE(dt_pos, dt_length, val.lexemeValue);
	tmpb = (0 == strcmp(dt_pos, datatype));
	if (!tmpb) printf("qwertz %s check failed\n", datatype);
	out->lexemeValue = CreateBoolean(env, tmpb);
}

void check_not_datatype(Environment *env, UDFContext *udfc, UDFValue *out){
	const char* datatype = (const char*) udfc->context;
	printf("check not %s\n", datatype);
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
	if (!tmpb) printf("qwertz not %s check failed\n", datatype);
	out->lexemeValue = CreateBoolean(env, tmpb);
}
