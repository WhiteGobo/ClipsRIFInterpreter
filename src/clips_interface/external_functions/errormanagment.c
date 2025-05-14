#include "errormanagment.h"

void crifi_udf_error(Environment *env, const char *errormessage, UDFValue *out){
	out->voidValue = VoidConstant(env);
	SetErrorValue(env, &(CreateString(env, errormessage)->header));
	Halt(env);
}

