#include "import_user_defined_functions.h"
#include "crifi_import.h"
#include "info_query.h"

#define SETERROR(errormessage) \
		SetErrorValue(env, &(CreateString(env, errormessage)->header));

static void set_error_combine(Environment *env, CLIPSValue *values, int number_values){
	CLIPSValue errval;
	MultifieldBuilder *mb;
	Multifield *mf;
	mb = CreateMultifieldBuilder(env,10);
	for (int i=0; i< number_values; i++){
		MBAppend(mb, values + i);
	}
	mf = MBCreate(mb);
	MBDispose(mb);
	SetErrorValue(env, &(mf->header));
}

static void set_error_string_uri(Environment *env, const char *string, CLIPSValue *uri){
	char *qq, *extra_str;
	CLIPSValue ret;
	extra_str = extract_uri(env, uri->header);
	if (extra_str == NULL){
		extra_str = extract_lexical(env, uri->header);
	}
	if (extra_str == NULL){
		extra_str = malloc(sizeof("(NULL)")+1);
		strcpy(extra_str, "(NULL)");
	}
	qq = malloc(strlen(string) + strlen(extra_str) + 1);
	sprintf(qq, string, extra_str);
	SetErrorValue(env, &(CreateString(env, qq)->header));
	free(extra_str);
}

void crifi_import(Environment *env, UDFContext *udfc, UDFValue *out){
	RET_CRIFI_IMPORT err_import;
	UDFValue tmpudfval;
	int number_additional_args;
	CLIPSValue import_location = {.voidValue = VoidConstant(env)};
	CLIPSValue entailment_regime = {.voidValue = VoidConstant(env)};
	CLIPSValue *values = NULL;
	CLIPSValue errlist[2];

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
			set_error_string_uri(env, "crifi:import doesnt know "
					"how to find: %s", &import_location);
			//SETERROR("crifi:import doesnt know how to find:");
			break;
		case RET_CRIFI_IMPORT_COULDNT_LOCATE_SOURCE:
			SETERROR("crifi:import couldnt has method to locate "
					"but couldnt load source");
			break;
		case RET_CRIFI_IMPORT_REJECTED_PROFILE:
			set_error_string_uri(env, "crifi:import doesnt "
					"support given entailment profile: %s",
					&entailment_regime);
			break;
		case RET_CRIFI_IMPORT_ASSERT_FRAME_FAILED:
			SETERROR("crifi:import failed because broken library. "
					"assert_frame unexpectedly thrown "
					"error.");
			break;
		case RET_CRIFI_IMPORT_INVALIDCONTEXT:
		case RET_CRIFI_IMPORT_PROCESS_FAILED:
		case RET_CRIFI_IMPORT_UNKNOWN_ERROR:
		default:
			SETERROR("crifi:import failed to execute import "
					"with unknown error");
	}
}
