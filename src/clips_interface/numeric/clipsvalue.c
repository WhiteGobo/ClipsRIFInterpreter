#include "crifi_numeric.h"
#include <clips.h>
#include "info_query.h"
#include "datatypes.h"

void crifi_numeric_create_boolean(Environment *env, bool value, CLIPSValue *result){
	if (value){
		result->lexemeValue = TrueSymbol(env);
	} else {
		result->lexemeValue = FalseSymbol(env);
	}
}

static bool numeric_value_from_lexical_and_datatype(char *lexical, char *datatype, NumericValue *out){
	bool success = false;
	char *endptr;
	long d;
	double *dbl;
	int dt_length = strlen(datatype);
	if (castable_as_long(lexical, datatype, strlen(datatype))) {
		out->t = NT_RATIONAL;
		out->dividend = atol(lexical);
		out->divisor = 1;
		success = true;
	} else if (castable_as_double(lexical, datatype, dt_length)){
		out->t = NT_FLOAT;
		out->f = strtod(lexical, &endptr);
		out->precision = out->f /1000;
		success = endptr != NULL;
	} else if (castable_as_true(lexical, datatype, dt_length)) {
		crifi_numeric_create_true(out);
		success = true;
	} else if (castable_as_false(lexical, datatype, dt_length)) {
		crifi_numeric_create_false(out);
		success = true;
	} else if (castable_as_hexadecimal(lexical, datatype, dt_length)) {
		out->t = NT_RATIONAL;
		out->dividend = strtol(lexical, &endptr, 16);
		out->divisor = 1;
		success = endptr != NULL;
	}
	if (!success){
		out->t = NT_NAN;
	}
	return success;
}

bool clipsvalue_as_numeric_value(Environment *env, CLIPSValue val, NumericValue *out) {
	char *lexical, *datatype;
	char *valueString, *endptr;
	bool success = false;
	switch (val.header->type){
		case FLOAT_TYPE:
			out->f = val.floatValue->contents;
			out->t = NT_FLOAT;
			out->precision = out->f / 100000;
			success = true;
			break;
		case INTEGER_TYPE:
			out->t = NT_RATIONAL;
			out->dividend = val.integerValue->contents;
			out->divisor = 1;
			success = true;
			break;
		case SYMBOL_TYPE:
			if (val.lexemeValue == TrueSymbol(env)){
				crifi_numeric_create_true(out);
				success = true;
			} else if (val.lexemeValue == FalseSymbol(env)){
				crifi_numeric_create_false(out);
				success = true;
			}
			break;
	}
	if (success){
		return true;
	}
	lexical = extract_lexical(env, val.header);
	datatype = extract_datatype(env, val.header);
	success = numeric_value_from_lexical_and_datatype(lexical, datatype, out);
	free(lexical);
	free(datatype);
	return success;
}
