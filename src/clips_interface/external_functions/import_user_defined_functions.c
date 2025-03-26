#include "import_user_defined_functions.h"
#include "crifi_import.h"


void crifi_import(Environment *env, UDFContext *udfc, UDFValue *out){
	CLIPSValue *import_location = NULL;
	CLIPSValue *entailment_regime = NULL;
	CLIPSValue *values = NULL;
	RET_CRIFI_IMPORT err = crifi_execute_import(env, import_location, entailment_regime, values, 0);
	out->lexemeValue = CreateBoolean(env, err == RET_CRIFI_IMPORT_NOERROR);
}
