#include "import_user_defined_functions.h"
#include "crifi_import.h"


void crifi_import(Environment *env, UDFContext *udfc, UDFValue *out){
	RET_CRIFI_IMPORT err_import;
	UDFValue tmpudfval;
	int number_additional_args;
	CLIPSValue import_location = {.voidValue = VoidConstant(env)};
	CLIPSValue entailment_regime = {.voidValue = VoidConstant(env)};
	CLIPSValue *values = NULL;

	number_additional_args = UDFArgumentCount(udfc) - 2;
	if (number_additional_args < 0){
		return;
	}

	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudfval)){
		return;
	}
	import_location.header = tmpudfval.header;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudfval)){
		return;
	}
	entailment_regime.header = tmpudfval.header;

	if (number_additional_args > 0){
		values = calloc(number_additional_args, sizeof(CLIPSValue));
		for (int i =0; i<number_additional_args; i++){
			if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudfval)){
				values[i].header = tmpudfval.header;
			}
		}
	} else {
		values = NULL;
		number_additional_args = 0;
	}

	err_import = crifi_execute_import(env, &import_location, &entailment_regime, values, number_additional_args);
	out->lexemeValue = CreateBoolean(env, err_import == RET_CRIFI_IMPORT_NOERROR);
}
