#include "crifi_numeric.h"

#include <n3parser.h>
#include "datatypes.h"

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




void crifi_numeric_create_true(NumericValue *val){
	val->t = NT_BOOLEAN;
	val->dividend = 1;
	val->divisor = 1;
}

void crifi_numeric_create_false(NumericValue *val){
	val->t = NT_BOOLEAN;
	val->dividend = 0;
	val->divisor = 1;
}

NumericValue crifi_numeric_cast_as_boolean(NumericValue val){
	NumericValue ret = {.t = NT_BOOLEAN, .divisor=1};
	switch (val.t){
		case NT_BOOLEAN:
			return val;
		case NT_RATIONAL:
			fprintf(stderr, "cast rational to boolean\n");
			if (val.dividend == 0){
				ret.dividend = 0; //false
			} else {
				ret.dividend = 1; //true
			}
			break;
		case NT_FLOAT:
			if (val.f == 0.0 || val.f == -0.0){
				ret.dividend = 0; //false
			} else {
				ret.dividend = 1; //true
			}
			break;
		case NT_NAN:
		default:
			ret.dividend = 0; //false
	}
	return ret;
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
	return crifi_numeric_to_clipsvalue2(env, &val);
}

CLIPSValue crifi_numeric_to_clipsvalue2(Environment *env, NumericValue *val){
	CLIPSValue ret;
	char tmpout[30+sizeof(_XS_decimal_)];
	switch (val->t){
		case NT_BOOLEAN:
			crifi_numeric_create_boolean(env, val->dividend == 1, &ret);
			return ret;
		case NT_RATIONAL:
			return crifi_create_rational(env, val->dividend, val->divisor);
			break;
		case NT_FLOAT:
			return crifi_create_float(env, val->f);
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


bool clipsvalue_as_integer(Environment *env, CLIPSValue val, long long *value){
	NumericValue numval;
	if (!clipsvalue_as_numeric_value(env, val, &numval)){
		return false;
	}
	if (numval.t == NT_RATIONAL){
		if (numval.dividend % numval.divisor != 0){
			return false;
		} else {
			*value = numval.dividend / numval.divisor;
			return true;
		}
	}
	return false;
}
