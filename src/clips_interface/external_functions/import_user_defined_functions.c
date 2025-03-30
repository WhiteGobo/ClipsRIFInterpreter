#include "import_user_defined_functions.h"
#include "crifi_import.h"

#define SETERROR(errormessage) \
		SetErrorValue(env, &(CreateString(env, errormessage)->header));

void crifi_import(Environment *env, UDFContext *udfc, UDFValue *out){
	RET_CRIFI_IMPORT err_import;
	UDFValue tmpudfval;
	int number_additional_args;
	CLIPSValue import_location = {.voidValue = VoidConstant(env)};
	CLIPSValue entailment_regime = {.voidValue = VoidConstant(env)};
	CLIPSValue *values = NULL;

	out->lexemeValue = FalseSymbol(env);

	number_additional_args = UDFArgumentCount(udfc) - 2;
	if (number_additional_args < 0){
		SETERROR("crifi:import has to few arguments");
		return;
	}

	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudfval)){
		SETERROR("Argument Error for crifi:import");
		return;
	}
	import_location.header = tmpudfval.header;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudfval)){
		SETERROR("Argument Error for crifi:import");
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

	switch(err_import){
		case RET_CRIFI_IMPORT_NOERROR:
			out->lexemeValue = TrueSymbol(env);
			break;
		case RET_CRIFI_BROKEN_ALGORITHM:
			SETERROR("crifi:import is broken.");
			break;
		case RET_CRIFI_IMPORT_UNHANDLED:
			SETERROR("crifi:import doesnt know how to find:");
			break;
		case RET_CRIFI_IMPORT_COULDNT_LOCATE_SOURCE:
			SETERROR("crifi:import couldnt has method to locate "
					"but couldnt load source");
			break;
		case RET_CRIFI_IMPORT_REJECTED_PROFILE:
			SETERROR("crifi:import doesnt support "
					"given entailment profile");
			break;
		case RET_CRIFI_IMPORT_INVALIDCONTEXT:
		case RET_CRIFI_IMPORT_PROCESS_FAILED:
		case RET_CRIFI_IMPORT_UNKNOWN_ERROR:
		default:
			SETERROR("crifi:import failed to execute import "
					"with unknown error");
	}
}
