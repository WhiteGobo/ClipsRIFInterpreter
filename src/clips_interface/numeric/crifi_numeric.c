#include "crifi_numeric.h"

#include <n3parser.h>

CLIPSValue crifi_create_integer(Environment *env, long long value){
	CLIPSValue ret;
	char tmpstring[20], tmpout[20+sizeof(_XS_integer_)];

	sprintf(tmpstring, "%d", value);
	value_and_datatype_to_slotstring(tmpout,
			tmpstring, strlen(tmpstring),
			_XS_integer_, sizeof(_XS_integer_));
	ret.lexemeValue = CreateString(env, tmpout);
	return ret;
}

static void cut_trailing_zeros(char *x){
	char *endptr = x;
	while (*endptr != '\0') endptr++;
	endptr -= 1;
	while (*endptr == '0' && endptr > x){
		*endptr = '\0';
		endptr--;
	}
}

CLIPSValue crifi_create_float(Environment *env, double value){
	CLIPSValue ret;
	char tmpstring[30], tmpout[30+sizeof(_XS_decimal_)];
	if (abs(value) < 1000000 && abs(value) > 0.000001){
		sprintf(tmpstring, "%f", value);
		cut_trailing_zeros(tmpstring);
		value_and_datatype_to_slotstring(tmpout,
				tmpstring, strlen(tmpstring),
				_XS_decimal_, sizeof(_XS_decimal_));
		ret.lexemeValue = CreateString(env, tmpout);
		return ret;
	}
	sprintf(tmpstring, "%e", value);
	value_and_datatype_to_slotstring(tmpout,
			tmpstring, strlen(tmpstring),
			_XS_decimal_, sizeof(_XS_decimal_));
	ret.lexemeValue = CreateString(env, tmpout);
	return ret;
}

CLIPSValue crifi_create_rational(Environment *env, long long dividend, long long divisor){
	CLIPSValue ret;
	long r, q, tmpl;
	char tmpstring[30], tmpout[30+sizeof(_XS_decimal_)];
	double value;
	if (0 == (dividend % divisor)){
		return crifi_create_integer(env, dividend / divisor);
	}
	value = ((double)dividend) / divisor;
	return crifi_create_float(env, value);
}

/*
bool clipsvalue_as_integer(CLIPSValue val, long long *out){
	bool check;
	char *valueString, *endptr;
	switch (val.header->type){
		case INTEGER_TYPE:
			*out = val.integerValue->contents;
			break;
		//case BOOLEAN_TYPE:
		//	break;
		case STRING_TYPE:
			if(ISPLAINLITERAL(val.lexemeValue)){
				return false;
			}
			FINDDATATYPE(dt_pos, dt_length, val.lexemeValue);
			valueString = clipslexeme_to_value(val.lexemeValue);
			if (castable_as_long(dt_pos, dt_length)) {
				*out = atol(valueString);
				check = true;
			} else if (castable_as_hexadecimal(dt_pos, dt_length)){
				*out = strtol(valueString, &endptr, 16);
				check = true;
			}
			free(valueString);
			return check;
	}
	return false;
}
*/

static bool castable_as_double(char *x, size_t xl){
	if (ISURI(x, xl, _XS_decimal_)) return true;
	if (ISURI(x, xl, _XS_double_)) return true;
	if (ISURI(x, xl, _XS_float_)) return true;
	return false;
}

static bool castable_as_hexadecimal(char *x, size_t xl){
	if (ISURI(x, xl, _XS_hexBinary_)) return true;
	return false;
}

static bool castable_as_long(char *x, size_t xl){
	if (ISURI(x, xl, _XS_integer_)) return true;
	if (ISURI(x, xl, _XS_long_)) return true;
	if (ISURI(x, xl, _XS_int_)) return true;
	if (ISURI(x, xl, _XS_short_)) return true;
	if (ISURI(x, xl, _XS_byte_)) return true;
	if (ISURI(x, xl, _XS_nonNegativeInteger_)) return true;
	if (ISURI(x, xl, _XS_positiveInteger_)) return true;
	if (ISURI(x, xl, _XS_unsignedLong_)) return true;
	if (ISURI(x, xl, _XS_unsignedInt_)) return true;
	if (ISURI(x, xl, _XS_unsignedShort_)) return true;
	if (ISURI(x, xl, _XS_unsignedByte_)) return true;
	if (ISURI(x, xl, _XS_nonPositiveInteger_)) return true;
	if (ISURI(x, xl, _XS_negativeInteger_)) return true;
	return false;
}

/**
 * TODO: i have no clue how to check for failure in atol
 */
static bool value_datatype_pair_to_integer(char *value, char *datatype, long int *out){
	if (!castable_as_long(datatype, strlen(datatype))) return false;
	*out = atol(value);
	return true;
}

/*
#define __ISDIGIT__(x) *x=='0' || *x=='1' || *x=='2' || *x=='3' || *x=='4' || *x=='5' || *x=='6' || *x=='7' || *x=='8' || *x=='9'
static float find_precision_float(const char *formatted_value, double value){
	const char *tmp;
	float x = 0.0;
	tmp = formatted_value;
	while (__ISDIGIT__(tmp)){
		x *= 0.1;
		tmp += 1;
	}
	if (*tmp == '.'){
		tmp += 1;
		while (__ISDIGIT__(tmp)){
			x *= 0.1;
			tmp += 1;
		}
	}
	return x * value;
}
#undef __ISDIGIT__
*/

static bool value_datatype_pair_to_double(char *value, char* datatype, double *out){
	char *endptr;
	if (!castable_as_double(datatype, strlen(datatype))) return false;
	*out = strtod(value, &endptr);
	//q.precision = find_precision_float(valueString, q.f);
	return endptr != NULL;
}

static bool value_datatype_pair_to_hexadecimal(char *value, char* datatype, long int *out){
	char *endptr;
	if (!castable_as_hexadecimal(datatype, strlen(datatype))) return false;
	*out = strtol(value, &endptr, 16);
	return endptr != NULL;
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
		//case BOOLEAN_TYPE:
		//	break;
		case STRING_TYPE:
			lexical = extract_lexical(env, val.lexemeValue);
			datatype = extract_datatype(env, val.lexemeValue);
			if (value_datatype_pair_to_integer(lexical, datatype, &(out->dividend))){
				out->t = NT_RATIONAL;
				out->divisor = 1;
				success = true;
			} else if (value_datatype_pair_to_double(lexical, datatype, &(out->f))){
				out->t = NT_FLOAT;
				//q.precision = find_precision_float(valueString, q.f);
				out->precision = out->f /100;
				success = true;
			} else if (value_datatype_pair_to_hexadecimal(lexical, datatype, &(out->dividend))){
				out->t = NT_RATIONAL;
				out->divisor = 1;
				success = true;
			} else {
				out->t = NT_NAN;
				success = false;
			}
			free(lexical);
			free(datatype);
			break;
		default:
			out->t = NT_NAN;
			success = false;
	}
	return success;
}

double nv_as_float(NumericValue val){
	if (val.t == NT_FLOAT){
		return val.f;
	} else if (val.t == NT_RATIONAL){
		return ((double)val.dividend) / val.divisor;
	} else {
#ifdef NAN
		return NAN
#else
		return 0;
#endif
	}
}

CLIPSValue crifi_numeric_to_clipsvalue(Environment *env, NumericValue val){
	CLIPSValue ret;
	char tmpout[30+sizeof(_XS_decimal_)];
	switch (val.t){
		case NT_RATIONAL:
			return crifi_create_rational(env, val.dividend, val.divisor);
			break;
		case NT_FLOAT:
			return crifi_create_float(env, val.f);
			break;
		case NT_NAN:
    			//"-INF"^^xs:float //alternativly
			value_and_datatype_to_slotstring(tmpout,
					"NaN", sizeof("NaN"),
					_XS_decimal_, sizeof(_XS_decimal_));
			ret.lexemeValue = CreateString(env, tmpout);
			return ret;
			break;
	}
}
