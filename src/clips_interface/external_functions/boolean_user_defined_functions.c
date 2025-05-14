#include "boolean_user_defined_functions.h"
#include "info_query.h"
#include "crifi_numeric.h"

#include "errormanagment.h"
#define RETURNFAIL(failure) \
		crifi_udf_error(env, failure, out);\
		return;

#define RETURNONVOID(env, udfval)\
		if(udfval.voidValue == VoidConstant(env)){return;}

void rif_is_literal_boolean(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool truth;
	UDFValue udfinput;
	CLIPSValue clipsinput;
	NumericValue val;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfinput)){
		RETURNFAIL("Argerror for pred:is-literal-boolean");
	}
	clipsinput.value = udfinput.value;
	//every numeric value can be cast to xs:boolean
	truth = clipsvalue_as_numeric_value(env, clipsinput, &val);
	if (truth){
		fprintf(stderr, "is literal boolean\n");
	} else {
		fprintf(stderr, "is literal not boolean\n");
	}
	if (invert){
		fprintf(stderr, "invert success\n");
		truth = !truth;
	}
	out->lexemeValue = CreateBoolean(env, truth);
}


void rif_cast_boolean(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfinput;
	CLIPSValue clipsinput, clipsoutput;
	NumericValue val;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfinput)){
		RETURNFAIL("Argerror for xs:boolean");
	}
	clipsinput.value = udfinput.value;
	fprintf(stderr, "brubru\n");
	if(!clipsvalue_as_numeric_value(env, clipsinput, &val)){
		RETURNFAIL("Missing guard for xs:boolean.");
	}
	val = crifi_numeric_cast_as_boolean(val);
	clipsoutput = crifi_numeric_to_clipsvalue2(env, &val);
	out->value = clipsoutput.value;
}


void rif_boolean_less_than(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfinput_left, udfinput_right;
	CLIPSValue clips_left, clips_right;
	NumericValue left, right;
	bool truth;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfinput_left)){
		RETURNFAIL("Argerror for pred:boolean-equal");
	}
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &udfinput_right)){
		RETURNFAIL("Argerror for pred:boolean-equal");
	}
	clips_left.value = udfinput_left.value;
	clips_right.value = udfinput_right.value;
	if(!clipsvalue_as_numeric_value(env, clips_left, &left)){
		RETURNFAIL("Missing guard for xs:boolean.");
	}
	if(!clipsvalue_as_numeric_value(env, clips_right, &right)){
		RETURNFAIL("Missing guard for xs:boolean.");
	}
	left = crifi_numeric_cast_as_boolean(left);
	right = crifi_numeric_cast_as_boolean(right);
	truth = left.dividend < right.dividend;
	out->lexemeValue = CreateBoolean(env, truth);
}


void rif_boolean_greater_than(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfinput_left, udfinput_right;
	CLIPSValue clips_left, clips_right;
	NumericValue left, right;
	bool truth;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfinput_left)){
		RETURNFAIL("Argerror for pred:boolean-equal");
	}
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &udfinput_right)){
		RETURNFAIL("Argerror for pred:boolean-equal");
	}
	clips_left.value = udfinput_left.value;
	clips_right.value = udfinput_right.value;
	if(!clipsvalue_as_numeric_value(env, clips_left, &left)){
		RETURNFAIL("Missing guard for xs:boolean.");
	}
	if(!clipsvalue_as_numeric_value(env, clips_right, &right)){
		RETURNFAIL("Missing guard for xs:boolean.");
	}
	left = crifi_numeric_cast_as_boolean(left);
	right = crifi_numeric_cast_as_boolean(right);
	truth = left.dividend > right.dividend;
	out->lexemeValue = CreateBoolean(env, truth);
}


void rif_boolean_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfinput_left, udfinput_right;
	CLIPSValue clips_left, clips_right;
	NumericValue left, right;
	bool truth;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfinput_left)){
		RETURNFAIL("Argerror for pred:boolean-equal");
	}
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &udfinput_right)){
		RETURNFAIL("Argerror for pred:boolean-equal");
	}
	clips_left.value = udfinput_left.value;
	clips_right.value = udfinput_right.value;

	if(!clipsvalue_as_numeric_value(env, clips_left, &left)){
		RETURNFAIL("Missing guard for xs:boolean.");
	}
	if(!clipsvalue_as_numeric_value(env, clips_right, &right)){
		RETURNFAIL("Missing guard for xs:boolean.");
	}
	left = crifi_numeric_cast_as_boolean(left);
	right = crifi_numeric_cast_as_boolean(right);
	truth = left.dividend == right.dividend;
	out->lexemeValue = CreateBoolean(env, truth);
}
