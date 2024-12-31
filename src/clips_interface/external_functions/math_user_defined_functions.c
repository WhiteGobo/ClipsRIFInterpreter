/**
 * Defines user defined functions for rif builtin functions
 */

#include <clips.h>
#include <n3parser.h>
#include <math.h>
#include "math_user_defined_functions.h"


typedef enum {
	NT_RATIONAL,
	NT_FLOAT,
	NT_ERROR,
	NT_NAN
} NUMERIC_TYPE;

typedef struct {
	NUMERIC_TYPE t;
	union {
		float f;
		long int dividend;
		const char* error_description;

		///describe if its +infinity or -infinity for example
		unsigned long nan_properties;
	};
	union {
		unsigned long int divisor;
		float precision;
	};
} numeric_value;

static numeric_value normal_rational(long int dividend, long int divisor){
	numeric_value ret;
	ret.t = NT_RATIONAL;
	if (divisor < 0){
		ret.dividend = -dividend;
		ret.divisor = -divisor;
	} else {
		ret.dividend = dividend;
		ret.divisor = divisor;
	}
	return ret;
}

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

static char* format_float_within_precision(float value, float precision){
	size_t i;
	float x, cmp;
	char myformat[10];
	char *ret;
	if (precision != 0.0 && value != 0.0){
		i = 0;
		x = abs(precision);
		cmp = abs(value);
		while (precision < cmp){
			i += 1;
			precision *= 10;
		}
	} else {
		i = 2;
	}
	sprintf(myformat, "%s.%de", "%", i);
	ret = malloc(5 + i);
	sprintf(ret, myformat, value);
	return ret;
}

static bool castable_as_rational(char *x, size_t xl){
	return false;
}

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

static numeric_value toNumeric_cant_transform_plainliteral = {
	.t = NT_ERROR,
	.error_description = "Cant transform plain literal to numeric value"
};
static const char default_err_toNumeric[]\
		     = "default error for UDFValueToNumericValue";

/**
 * duplicate of clipsvalue_as_numeric_value from numeric
 */
static numeric_value UDFValueToNumericValue(UDFValue val) {
	char *valueString, *endptr;
	numeric_value q;
	q.t = NT_ERROR;
	q.error_description = default_err_toNumeric;
	switch (val.header->type){
		//case FLOAT_TYPE:
		//	val.floatValue
		//	break;
		//case INT_TYPE:
		//	val.integerValue
		//	break;
		//case BOOLEAN_TYPE:
		//	break;
		case STRING_TYPE:
			if(ISPLAINLITERAL(val.lexemeValue)){
				return toNumeric_cant_transform_plainliteral;
			}
			FINDDATATYPE(dt_pos, dt_length, val.lexemeValue);
			valueString = clipslexeme_to_value(val.lexemeValue);
			if (castable_as_long(dt_pos, dt_length)) {
				//q = normal_rational(atol(valueString), 1);
				q.t = NT_RATIONAL;
				q.dividend = atol(valueString);
				q.divisor = 1;
			} else if (castable_as_double(dt_pos, dt_length)){
				q.t = NT_FLOAT;
				q.f = strtod(valueString, &endptr);
				q.precision = find_precision_float(valueString, q.f);
			} else if (castable_as_hexadecimal(dt_pos, dt_length)){
				q.t = NT_RATIONAL;
				q.dividend = strtol(valueString, &endptr, 16);
				q.divisor = 1;
			}
			free(valueString);
	}
	return q;
}

static char default_error_numeric_add[] = "default error for numeric_add";

/*
 * retains errors
 */
static numeric_value numeric_add(numeric_value val1, numeric_value val2){
	long int x, y;
	float tmp;
	numeric_value q;
	if (val1.t == NT_ERROR) return val1;
	if (val2.t == NT_ERROR) return val2;
	q.t = NT_ERROR;
	q.error_description = default_error_numeric_add;
	switch (val1.t){
		case NT_RATIONAL:
			switch (val2.t){
				case NT_RATIONAL:
					x = (val1.dividend * val2.divisor)\
						     + (val2.dividend * val1.divisor);
					y = val1.divisor * val2.divisor;
					return normal_rational(x, y);
					break;
				case NT_FLOAT:
					q.t = NT_FLOAT;
					tmp = val1.dividend / val1.divisor;
					q.f = tmp + val2.f;
					q.precision = val2.precision;
					return q;
					break;
			}
			break;
		case NT_FLOAT:
			switch (val2.t){
				case NT_RATIONAL:
					q.t = NT_FLOAT;
					tmp = val2.dividend / val2.divisor;
					q.f = tmp + val1.f;
					q.precision = val1.precision;
					return q;
					break;
				case NT_FLOAT:
					q.t = NT_FLOAT;
					q.f = val1.f + val2.f;
					q.precision = val1.precision\
						      + val2.precision;
					return q;
					break;
			}
			break;
	}
	return q;
}

/*
 * retains errors
 */
static numeric_value numeric_subtract(numeric_value val1, numeric_value val2){
	long int x, y;
	float tmp, tmpp;
	numeric_value q;
	if (val1.t == NT_ERROR) return val1;
	if (val2.t == NT_ERROR) return val2;
	q.t = NT_ERROR;
	q.error_description = default_error_numeric_add;
	switch (val1.t){
		case NT_RATIONAL:
			switch (val2.t){
				case NT_RATIONAL:
					x = (val1.dividend * val2.divisor)\
						     - (val2.dividend * val1.divisor);
					y = val1.divisor * val2.divisor;
					return normal_rational(x, y);
					break;
				case NT_FLOAT:
					q.t = NT_FLOAT;
					tmp = val1.dividend / val1.divisor;
					tmpp = 1 / val1.divisor;
					q.f = tmp - val2.f;
					q.precision = val2.precision;
					if (tmpp < val2.precision){
						q.precision = tmpp;
					} else {
						q.precision = val2.precision;
					}
					return q;
					break;
			}
			break;
		case NT_FLOAT:
			switch (val2.t){
				case NT_RATIONAL:
					q.t = NT_FLOAT;
					tmp = val2.dividend / val2.divisor;
					tmpp = 1 / val2.divisor;
					q.f = val2.f - tmp;
					if (tmpp < val1.precision){
						q.precision = tmpp;
					} else {
						q.precision = val1.precision;
					}
					return q;
				case NT_FLOAT:
					q.t = NT_FLOAT;
					q.f = val1.f - val2.f;
					if (val1.precision < val2.precision){
						q.precision = val1.precision;
					} else {
						q.precision = val2.precision;
					}
					return q;
					break;
			}
			break;
	}
	return q;
}

/*
 * retains errors
 */
static numeric_value numeric_multiply(numeric_value val1, numeric_value val2){
	long int x, y;
	float tmp;
	numeric_value q;
	if (val1.t == NT_ERROR) return val1;
	if (val2.t == NT_ERROR) return val2;
	q.t = NT_ERROR;
	q.error_description = default_error_numeric_add;
	switch (val1.t){
		case NT_RATIONAL:
			switch (val2.t){
				case NT_RATIONAL:
					x = val1.dividend * val2.dividend;
					y = val1.divisor * val2.divisor;
					return normal_rational(x, y);
					break;
				case NT_FLOAT:
					q.t = NT_FLOAT;
					tmp = val1.dividend / val1.divisor;
					q.f = tmp * val2.f;
					q.precision = tmp * val2.precision;
					return q;
					break;
			}
			break;
		case NT_FLOAT:
			switch (val2.t){
				case NT_RATIONAL:
					q.t = NT_FLOAT;
					tmp = val2.dividend / val2.divisor;
					q.f = tmp * val1.f;
					q.precision = tmp * val1.precision;
					return q;
					break;
				case NT_FLOAT:
					q.t = NT_FLOAT;
					q.f = val1.f * val2.f;
					q.precision = (val1.precision * val2.f)\
						      +(val2.precision*val1.f);
					return q;
					break;
			}
			break;
	}
	return q;
}

/*
 * retains errors
 */
static numeric_value numeric_divide(numeric_value val1, numeric_value val2){
	long int x, y;
	float tmp1, tmp2;
	numeric_value q;
	if (val1.t == NT_ERROR) return val1;
	if (val2.t == NT_ERROR) return val2;
	q.t = NT_ERROR;
	q.error_description = default_error_numeric_add;
	switch (val1.t){
		case NT_RATIONAL:
			switch (val2.t){
				case NT_RATIONAL:
					x = val1.dividend * val2.divisor;
					y = val2.dividend * val1.divisor;
					return normal_rational(x, y);
					break;
				case NT_FLOAT:
					q.t = NT_FLOAT;
					tmp1 = val1.dividend / val1.divisor;
					q.f = tmp1 / val2.f;
					q.precision\
						= q.f * (val2.precision/val2.f);
					return q;
					break;
			}
			break;
		case NT_FLOAT:
			switch (val2.t){
				case NT_RATIONAL:
					q.t = NT_FLOAT;
					tmp2 = val2.dividend / val2.divisor;
					q.f = tmp2 / val1.f;
					q.precision\
						= q.f * (val1.precision/val1.f);
					return q;
					break;
				case NT_FLOAT:
					q.t = NT_FLOAT;
					q.f = val1.f / val2.f;
					q.precision = q.f * (\
						(val1.precision / val1.f)
						+ (val2.precision / val2.f));
					break;
			}
			break;
	}
	return q;
}

/*
 * retains errors
 */
static numeric_value numeric_integer_divide(numeric_value val1, numeric_value val2){
	float tmp1, tmp2;
	numeric_value q;
	long long tmp3;
	if (val1.t == NT_ERROR) return val1;
	if (val2.t == NT_ERROR) return val2;
	q.t = NT_ERROR;
	q.error_description = default_error_numeric_add;
	switch (val1.t){
		case NT_RATIONAL:
			switch (val2.t){
				case NT_RATIONAL:
					q.t = NT_RATIONAL;
					tmp1 = val1.dividend / val1.divisor;
					tmp2 = val2.dividend / val2.divisor;
					tmp3 = tmp1 / tmp2;
					q.dividend = tmp3;
					q.divisor = 1;
					return q;
					break;
				case NT_FLOAT:
					q.t = NT_RATIONAL;
					tmp1 = val1.dividend / val1.divisor;
					tmp3 = tmp1 / val2.f;
					q.dividend = tmp3;
					q.divisor = 1;
					return q;
					break;
			}
			break;
		case NT_FLOAT:
			switch (val2.t){
				case NT_RATIONAL:
					q.t = NT_RATIONAL;
					tmp2 = val2.dividend / val2.divisor;
					tmp3 = val1.f / tmp2;
					q.dividend = tmp3;
					q.divisor = 1;
					return q;
					break;
				case NT_FLOAT:
					q.t = NT_RATIONAL;
					tmp3 = val1.f / val2.f;
					q.dividend = tmp3;
					q.divisor = 1;
					return q;
					break;
			}
			break;
	}
	return q;
}

/*
 * retains errors
 */
static numeric_value numeric_integer_mod(numeric_value val1, numeric_value val2){
	float tmp;
	long long dividend;
	unsigned long long divisor;
	numeric_value q;
	if (val1.t == NT_ERROR) return val1;
	if (val2.t == NT_ERROR) return val2;
	q.t = NT_ERROR;
	q.error_description = default_error_numeric_add;
	switch (val1.t){
		case NT_RATIONAL:
			switch (val2.t){
				case NT_RATIONAL:
					q.t = NT_RATIONAL;
					dividend = val1.dividend * val2.divisor;
					divisor = val2.dividend * val1.divisor;
					q.dividend = dividend % divisor;
					q.divisor = 1;
					return q;
					break;
				case NT_FLOAT:
					q.t = NT_FLOAT;
					tmp = val1.dividend / val1.divisor;
					q.dividend = fmod(tmp, val2.f);
					q.precision = val2.precision;
					return q;
					break;
			}
			break;
		case NT_FLOAT:
			switch (val2.t){
				case NT_RATIONAL:
					q.t = NT_RATIONAL;
					tmp = val2.dividend / val2.divisor;
					q.dividend = fmod(tmp, val1.f);
					q.precision = val1.precision;
					return q;
					break;
				case NT_FLOAT:
					q.t = NT_FLOAT;
					q.dividend = fmod(val1.f, val2.f);
					q.precision = val2.precision;
					return q;
					break;
			}
			break;
	}
	return q;
}

/*
 * retains errors
 */
static bool numeric_equal(numeric_value val1, numeric_value val2){
	float tmp;
	numeric_value q;
	if (val1.t == NT_ERROR) return false;
	if (val2.t == NT_ERROR) return false;
	q.t = NT_ERROR;
	q.error_description = default_error_numeric_add;
	switch (val1.t){
		case NT_RATIONAL:
			switch (val2.t){
				case NT_RATIONAL:
					return (val1.dividend * val2.divisor)\
						== (val2.dividend*val1.divisor);
					break;
				case NT_FLOAT:
					tmp = val1.dividend / val1.divisor;
					return tmp == val2.f;
					break;
			}
			break;
		case NT_FLOAT:
			switch (val2.t){
				case NT_RATIONAL:
					tmp = val2.dividend / val2.divisor;
					return tmp == val1.f;
					break;
				case NT_FLOAT:
					return val1.f == val2.f;
					break;
			}
			break;
	}
	return false;
}

static bool numeric_not_equal(numeric_value val1, numeric_value val2){
	return !numeric_equal(val1, val2);
}

/*
 * retains errors
 */
static bool numeric_less_than(numeric_value val1, numeric_value val2){
	long int x, y;
	float tmp;
	numeric_value q;
	if (val1.t == NT_ERROR) return false;
	if (val2.t == NT_ERROR) return false;
	q.t = NT_ERROR;
	q.error_description = default_error_numeric_add;
	switch (val1.t){
		case NT_RATIONAL:
			switch (val2.t){
				case NT_RATIONAL:
					x =val1.dividend * val2.divisor;
					y =val2.dividend*val1.divisor;
					return x < y;
					break;
				case NT_FLOAT:
					tmp = val1.dividend / val1.divisor;
					return tmp < val2.f;
					break;
			}
			break;
		case NT_FLOAT:
			switch (val2.t){
				case NT_RATIONAL:
					tmp = val2.dividend / val2.divisor;
					return tmp < val1.f;
					break;
				case NT_FLOAT:
					return val1.f < val2.f;
					break;
			}
			break;
	}
	return false;
}

static bool numeric_greater_than_or_equal(numeric_value val1, numeric_value val2){
	return !numeric_less_than(val1, val2);
}

static bool numeric_greater_than(numeric_value val1, numeric_value val2){
	return numeric_less_than(val2, val1);
}

static bool numeric_less_than_or_equal(numeric_value val1, numeric_value val2){
	return !numeric_less_than(val2, val1);
}


static bool numeric_value_to_n3(Environment *env, numeric_value val, UDFValue *out){
	unsigned int i;
	long r, q, tmpl;
	double x;
	switch (val.t){
		case NT_RATIONAL:
			i = 0;
			q = val.divisor;
			r = val.dividend;
			if (r%q == 0){
				tmpl = r/q;
				TEMPORARYINTERNALREPRESENTATION(tmpi, tmpl, 11,\
							"%d", _XS_integer_);
				out->lexemeValue = CreateString(env, tmpi);
				return true;
			}
			while ((0 == (q % 10)) && (0 == (r%10))) {
				q /= 10;
				r /= 10;
			}
			x = r/q;
			TEMPORARYINTERNALREPRESENTATION(tmpx, x, \
						30, "%d", _XS_decimal_);
			out->lexemeValue = CreateString(env, tmpx);
			return true;
			break;
		case NT_ERROR:
		case NT_NAN:
		default:
			return false;
	}
	return false;
}


#define NUMERICLISTCALCULATOR(action, actionname) \
	const char* argerr = "Argument Error for "actionname;\
	numeric_value val1, val2;\
	UDFValue myval;\
	unsigned int l = UDFArgumentCount(udfc);\
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval) || l==0){\
		Writeln(env, argerr);\
		UDFThrowError(udfc);\
		SetErrorValue(env, &(CreateString(env, argerr)->header));\
		return;\
	}\
	val1 = UDFValueToNumericValue(myval);\
	if (val1.t == NT_ERROR){\
		WriteUDFValue(env, STDOUT, &myval);\
		Write(env, " cant be transformed to numeric value. ");\
		Writeln(env, val1.error_description);\
		UDFThrowError(udfc);\
		SetErrorValue(env, &(CreateString(env, argerr)->header));\
		return;\
	}\
	for (int i=1; i<l; i++){\
		if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &myval)){\
			Writeln(env, argerr);\
			UDFThrowError(udfc);\
			SetErrorValue(env, &(CreateString(env, argerr)->header));\
			return;\
		}\
		val2 = UDFValueToNumericValue(myval);\
		val1 = action(val1, val2);\
	}\
	if (val1.t == NT_ERROR){\
		Writeln(env, val1.error_description);\
		UDFThrowError(udfc);\
		SetErrorValue(env, &(CreateString(env, val1.error_description)->header));\
		return;\
	}\
	if (!numeric_value_to_n3(env, val1, out)){\
		Writeln(env, "Failed to return numeric value.");\
		UDFThrowError(udfc);\
		SetErrorValue(env, &(CreateString(env, "Failed to return numeric value.")->header));\
		return;\
	}

void rif_numeric_add(Environment *env, UDFContext *udfc, UDFValue *out) {
	NUMERICLISTCALCULATOR(numeric_add, "numeric_add");
}

void rif_numeric_subtract(Environment *env, UDFContext *udfc, UDFValue *out){
	NUMERICLISTCALCULATOR(numeric_subtract, "numeric_subtract");
}

void rif_numeric_multiply(Environment *env, UDFContext *udfc, UDFValue *out){
	NUMERICLISTCALCULATOR(numeric_multiply, "numeric_multiply");
}

void rif_numeric_divide(Environment *env, UDFContext *udfc, UDFValue *out){
	NUMERICLISTCALCULATOR(numeric_divide, "numeric_divide");
	printf("qwertz %s\n", out->lexemeValue->contents);\
}

void rif_numeric_integer_divide(Environment *env, UDFContext *udfc, UDFValue *out){
	NUMERICLISTCALCULATOR(numeric_integer_divide, "numeric_integer_divide");
}

void rif_numeric_integer_mod(Environment *env, UDFContext *udfc, UDFValue *out){
	NUMERICLISTCALCULATOR(numeric_integer_mod, "numeric_integer_mod");
}

#undef NUMERICLISTCALCULATOR

#define NUMERICCOMPARER(action, actionname) \
	numeric_value val1, val2;\
	bool truth;\
	UDFValue myval;\
	unsigned int l = UDFArgumentCount(udfc);\
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval) || l==0){\
		Writeln(env, "Argument Error for "actionname);\
		UDFThrowError(udfc);\
		SetErrorValue(env, &(CreateString(env, "Argument Error for "actionname)->header));\
		return;\
	}\
	val1 = UDFValueToNumericValue(myval);\
	if (val1.t == NT_ERROR){\
		WriteUDFValue(env, STDOUT, &myval);\
		Write(env, " cant be transformed to numeric value. ");\
		Writeln(env, val1.error_description);\
		UDFThrowError(udfc);\
		SetErrorValue(env, &(CreateString(env, "Argument transform error for "actionname)->header));\
		return;\
	}\
	for (int i=1; i<l; i++){\
		if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &myval)){\
			Writeln(env, "Argument Error for numeric add");\
			UDFThrowError(udfc);\
			SetErrorValue(env, &(CreateString(env, "Argument error for "actionname)->header));\
			return;\
		}\
		val2 = UDFValueToNumericValue(myval);\
		if (val2.t == NT_ERROR){\
			Writeln(env, val1.error_description);\
			UDFThrowError(udfc);\
			SetErrorValue(env, &(CreateString(env, val1.error_description)->header));\
			return;\
		}\
		truth = action(val1, val2);\
		if (!truth) {\
			out->lexemeValue = CreateBoolean(env, false);\
			return;\
		}\
		val1 = val2;\
	}\
	out->lexemeValue = CreateBoolean(env, true);

void rif_numeric_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	NUMERICCOMPARER(numeric_equal, "numeric_equal");
}

void rif_numeric_not_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	NUMERICCOMPARER(numeric_not_equal, "numeric_not_equal");
}

void rif_numeric_less_than(Environment *env, UDFContext *udfc, UDFValue *out){
	NUMERICCOMPARER(numeric_less_than, "numeric_less_than");
}

void rif_numeric_less_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	NUMERICCOMPARER(numeric_less_than_or_equal, "numeric_less_than_or_equal");
}

void rif_numeric_greater_than(Environment *env, UDFContext *udfc, UDFValue *out){
	NUMERICCOMPARER(numeric_greater_than, "numeric_greather_than");
}

void rif_numeric_greater_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	NUMERICCOMPARER(numeric_greater_than_or_equal, "numeric_greater_than_or_equal");
}

#undef NUMERICCOMPARER



void rif_is_literal_double(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = (val1.t == NT_FLOAT) || (val1.t == NT_RATIONAL);
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}


void rif_is_literal_float(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = val1.t == NT_FLOAT || val1.t == NT_RATIONAL;
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}

void rif_is_literal_hexBinary(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = ((ContextTypecheck*) udfc->context)->invert;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = val1.t == NT_FLOAT || val1.t == NT_RATIONAL;
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}

void rif_is_literal_decimal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = ((ContextTypecheck*) udfc->context)->invert;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = val1.t == NT_FLOAT || val1.t == NT_RATIONAL;
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}
void rif_is_literal_integer(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = ((ContextTypecheck*) udfc->context)->invert;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = val1.t == NT_FLOAT || val1.t == NT_RATIONAL;
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}
void rif_is_literal_long(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = ((ContextTypecheck*) udfc->context)->invert;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = val1.t == NT_FLOAT || val1.t == NT_RATIONAL;
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}
void rif_is_literal_int(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = ((ContextTypecheck*) udfc->context)->invert;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = val1.t == NT_FLOAT || val1.t == NT_RATIONAL;
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}
void rif_is_literal_short(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = ((ContextTypecheck*) udfc->context)->invert;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = val1.t == NT_FLOAT || val1.t == NT_RATIONAL;
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}
void rif_is_literal_byte(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = ((ContextTypecheck*) udfc->context)->invert;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = val1.t == NT_FLOAT || val1.t == NT_RATIONAL;
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}
void rif_is_literal_nonNegativeInteger(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = ((ContextTypecheck*) udfc->context)->invert;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = val1.t == NT_FLOAT || val1.t == NT_RATIONAL;
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}
void rif_is_literal_positiveInteger(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = ((ContextTypecheck*) udfc->context)->invert;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = val1.t == NT_FLOAT || val1.t == NT_RATIONAL;
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}
void rif_is_literal_unsignedLong(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = ((ContextTypecheck*) udfc->context)->invert;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = val1.t == NT_FLOAT || val1.t == NT_RATIONAL;
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}
void rif_is_literal_unsignedInt(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = ((ContextTypecheck*) udfc->context)->invert;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = val1.t == NT_FLOAT || val1.t == NT_RATIONAL;
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}
void rif_is_literal_unsignedShort(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = ((ContextTypecheck*) udfc->context)->invert;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = val1.t == NT_FLOAT || val1.t == NT_RATIONAL;
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}
void rif_is_literal_unsignedByte(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = ((ContextTypecheck*) udfc->context)->invert;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = val1.t == NT_FLOAT || val1.t == NT_RATIONAL;
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}
void rif_is_literal_nonPositiveInteger(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = ((ContextTypecheck*) udfc->context)->invert;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = val1.t == NT_FLOAT || val1.t == NT_RATIONAL;
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}
void rif_is_literal_negativeInteger(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = ((ContextTypecheck*) udfc->context)->invert;
	bool truth;
	numeric_value val1;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)){
		Writeln(env, "Argument Error");
		UDFThrowError(udfc);
		return;
	}
	val1 = UDFValueToNumericValue(myval);
	truth = (val1.t == NT_FLOAT) || (val1.t == NT_RATIONAL);
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}

/**
 *
 * TODO: Replicate of clipsvalue_as_integer
 */
bool udfvalue_as_integer(UDFValue val, long long *out){
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
