#include <n3parser.h>
#include <clips.h>
#include "constfunctions.h"

static bool AddUDF_witherrorprint(
		Environment *env,
		UDFDescription qq
		){
	void *cntxt;
	if (CT_static == qq.contextType){
		cntxt = qq.context;
	} else if (CT_generate == qq.contextType ) {
		cntxt = "brubru";
	}
	AddUDFError err = AddUDF(env, qq.clipsName, qq.returnTypes,
			qq.minArgs, qq.maxArgs, qq.argTypes, qq.cfp,
			qq.cName, cntxt);
	switch (err) {
		case AUE_NO_ERROR:
			return true;
			break;
		case AUE_MIN_EXCEEDS_MAX_ERROR:
			fprintf(stderr, "2 %s\n", qq.clipsName);
			break;
		case AUE_FUNCTION_NAME_IN_USE_ERROR:
			fprintf(stderr, "3 %s\n", qq.clipsName);
			break;
		case AUE_INVALID_ARGUMENT_TYPE_ERROR:
			fprintf(stderr, "4 %s\n", qq.clipsName);
			break;
		case AUE_INVALID_RETURN_TYPE_ERROR:
			fprintf(stderr, "5 %s\n", qq.clipsName);
			break;
	}
	return err == AUE_NO_ERROR;
}

/**
 * TODO: there are segfaults if this function return false
 */
bool add_literal_user_functions(Environment* env){
	for (UDFDescription *x = builtinFunctionList; x->clipsName != NULL; x++){
		if (!AddUDF_witherrorprint(env, *x)) {
			return false;
		}
	}
	return true;
}
