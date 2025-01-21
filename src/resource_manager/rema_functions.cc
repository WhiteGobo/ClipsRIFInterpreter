#include "rema_functions.h"
#include <n3parser.h>

#define RETURNFAIL(failure) \
		Writeln(env, failure);\
		SetErrorValue(env, &(CreateString(env, failure)->header));\
		out->voidValue = VoidConstant(env);\
		return;

void print_builtin_literal(Environment *env, UDFContext *udfc, UDFValue *out){
	int err;
	UDFValue udfval;
	CLIPSValue clipsval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is_literal_normalizedString.");
	}
	err = value_and_datatype_to_clipsvalue(env,
			udfval.lexemeValue->contents,
			strlen(udfval.lexemeValue->contents),
			NULL, 0, &clipsval);
	if (err==0){
		out->value = clipsval.value;
	}
}

#undef RETURNFAIL
