#include <ffi_clips_interface.h>
#include "additional_user_functions.h"


typedef struct UDFDescription_ {
	const char *clipsName;
	const char *returnTypes;
	unsigned short minArgs;
	unsigned short maxArgs;
	const char *argTypes;
	UserDefinedFunction *cfp;
	const char *cName;
} UDFDescription;

static void mycleanupfunction(Environment *env){
}

static bool add_udf_witherrorprint(
		Environment *env,
		UDFDescription qq
		){
	if (! AllocateEnvironmentData(env,INDEX_DATA,
				sizeof(struct indexData), mycleanupfunction))
	{
		Writeln(env,"Error allocating environment data for INDEX_DATA");
		ExitRouter(env,EXIT_FAILURE);
	}
	IndexData(env)->index = 1;


	AddUDFError err = AddUDF(env, qq.clipsName, qq.returnTypes,
			qq.minArgs, qq.maxArgs, qq.argTypes, qq.cfp,
			qq.cName, NULL);
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

static void import_directive(Environment *env, UDFContext *udfc, UDFValue *out){
	out->integerValue = CreateInteger(env,IndexData(env)->index++);
}

static UDFDescription resourceManagerClipsFunctions[] = {
	{"<" _CRIFI_RM_import_ ">", "*", 0, UNBOUNDED, "*",
		import_directive, "import_directive"},
	{NULL, NULL, 0,0, NULL, NULL, NULL}
};

bool add_needed_user_functions(struct clips_graph_container graph){
	Environment *env = graph.environment;
	for (UDFDescription *x = resourceManagerClipsFunctions; x->clipsName != NULL; x++){
		if (!add_udf_witherrorprint(graph.environment, *x)) {
			return false;
		}
	}
	return true;
}
