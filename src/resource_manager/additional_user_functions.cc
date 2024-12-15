#include <ffi_clips_interface.h>
#include "additional_user_functions.h"
#include <n3parser.h>
#include "resource_manager.h"


typedef struct UDFDescription_ {
	const char *clipsName;
	const char *returnTypes;
	unsigned short minArgs;
	unsigned short maxArgs;
	const char *argTypes;
	UserDefinedFunction *cfp;
	const char *cName;
} UDFDescription;

static bool add_udf_witherrorprint(
		Environment *env,
		UDFDescription qq
		){

	AddUDFError err = AddUDF(env, qq.clipsName, qq.returnTypes,
			qq.minArgs, qq.maxArgs, qq.argTypes, qq.cfp,
			qq.cName, NULL);
	switch (err) {
		case AUE_NO_ERROR:
			return true;
			break;
		case AUE_MIN_EXCEEDS_MAX_ERROR:
			Writeln(env,"Internal error 11. "
					"Cant load ResourceManager plugin.");
			ExitRouter(env,EXIT_FAILURE);
			break;
		case AUE_FUNCTION_NAME_IN_USE_ERROR:
			Writeln(env,"Internal error 12. "
					"Cant load ResourceManager plugin.");
			ExitRouter(env,EXIT_FAILURE);
			break;
		case AUE_INVALID_ARGUMENT_TYPE_ERROR:
			Writeln(env,"Internal error 13. "
					"Cant load ResourceManager plugin.");
			ExitRouter(env,EXIT_FAILURE);
			break;
		case AUE_INVALID_RETURN_TYPE_ERROR:
			Writeln(env,"Internal error 14. "
					"Cant load ResourceManager plugin.");
			ExitRouter(env,EXIT_FAILURE);
			break;
	}
	return err == AUE_NO_ERROR;
}

static void set_error_import_directive(Environment *env, const char* profile, const char* location){
	CLIPSValue err;
	char q[50 + strlen(location) + strlen(profile)];
	sprintf(q, "import_directive couldnt create rules for (%s, %s)\n",
			profile, location);
	err.lexemeValue = CreateString(env,q);
	SetErrorValue(env, err.header);
}

static void import_directive(Environment *env, UDFContext *udfc, UDFValue *out){
	struct TriplesLinkedList* triples;
	//LoadingInfo *loading_info;
	struct indexData *data;
	UDFValue location_val, profile_val;
	char *location, *profile;
	std::string *as_rules_clips;
	if (!UDFFirstArgument(udfc, LEXEME_BITS | VOID_BIT, &location_val)){
		Writeln(env, "Failed loading first argument import_directive");
		UDFThrowError(udfc);
		SetErrorValue(env, &(CreateString(env, "import_directive")->header));
		out->value = CreateString(env, "");
		return;
	}
	if (UDFHasNextArgument(udfc)){
		if (!UDFNextArgument(udfc, VOID_BIT | LEXEME_BITS, &profile_val)){
			Writeln(env, "failed loading second argument "
					"import_directive");
			UDFThrowError(udfc);
			SetErrorValue(env, &(CreateString(env, "import_directive")->header));

			out->value = CreateString(env, "");
			return;
		}
		//profile = profile_val.lexemeValue->contents;
		profile = extract_lexical(env, profile_val.lexemeValue);
	} else {
		profile = NULL;
	}
	//location = location_val.lexemeValue->contents;
	location = extract_lexical(env, location_val.lexemeValue);

	data = LoadingData(env);
	for (LoadingInfo *loading_info = data->nextinfo;
			loading_info != NULL;
			loading_info = loading_info->nextinfo){
		triples = loading_info->loadingFunction(loading_info->context, location);
		if (triples != NULL){
			as_rules_clips = create_rules(triples, profile);
			printf("qwertz6\n");
			if (as_rules_clips != nullptr){
			printf("qwertz7\n");
				out->value = CreateString(env,
						as_rules_clips->c_str());
				printf("import_rules created rules:\n%s\n\n", as_rules_clips->c_str());
				delete(as_rules_clips);
			} else {
			printf("qwertz8\n");
				set_error_import_directive(env, profile,
						location);
				out->value = CreateString(env, "");
			}
			free(location);
			free(profile);
			return;
		}
	}
	free(location);
	free(profile);
	out->value = CreateString(env, "");
}

std::string *create_rules(struct TriplesLinkedList* triples, const char* profile){
	std::string *newrules;
	if (0==strcmp(profile, _ENTAILMENT_RDF_)){
		return generate_rdf_entailment(triples);
	} else if (profile == NULL){
		printf("no entailment chosen\n");
	} else {
		fprintf(stderr, "cant handle entailment: %s\n", profile);
	}
	return nullptr;
}


static UDFDescription resourceManagerClipsFunctions[] = {
	{"<" _CRIFI_RM_import_ ">", "*", 1, 2, "syv",
		import_directive, "import_directive"},
	{NULL, NULL, 0,0, NULL, NULL, NULL}
};

bool add_needed_user_functions(struct clips_graph_container graph,
		LoadingFunction* loading_functions,
		const void **loading_function_context,
		unsigned int loading_functions_length){
	Environment *env = graph.environment;

	if (! AllocateEnvironmentData(env, CRIFI_RM_INDEX_DATA,
						sizeof(struct indexData),
						free_loading_functions))
	{
		Writeln(env,"Internal error 0. "
				"Cant load ResourceManager plugin.");
		ExitRouter(env,EXIT_FAILURE);
	}
	LoadingData(env)->nextinfo=NULL;

	if (loading_functions != NULL){
		for (unsigned int i=0; i<loading_functions_length; i++){
			if(!append_loading_function(
						graph,
						loading_functions[i],
						loading_function_context[i]))
			{
				Writeln(env,"Internal error 2. "
					"Cant load ResourceManager plugin.");
				ExitRouter(env, EXIT_FAILURE);
			}
		}
	}

	for (UDFDescription *x = resourceManagerClipsFunctions; x->clipsName != NULL; x++){
		if (!add_udf_witherrorprint(graph.environment, *x)) {
			return false;
		}
	}
	return true;
}

bool append_loading_function(struct clips_graph_container graph,
		LoadingFunction loading_function,
		const void *context){
	RdfResourceLoadingData *env_data;
	if(loading_function == NULL) return false;
	LoadingInfo *tmpinfo;
	LoadingInfo *newinfo = (LoadingInfo *) malloc(sizeof(LoadingInfo));
	if (newinfo==NULL) return false;
	newinfo->loadingFunction = loading_function;
	newinfo->context = context;
	newinfo->nextinfo = NULL;
	env_data = LoadingData(graph.environment);
	if (env_data->nextinfo != NULL) {
		while (tmpinfo->nextinfo != NULL){
			tmpinfo = tmpinfo->nextinfo;
		}
		tmpinfo->nextinfo = newinfo;
	} else {
		env_data->nextinfo = newinfo;
	}
	return true;
}

void free_loading_functions(Environment *env){
	LoadingInfo *tmp1, *tmp2;
	struct indexData *data = LoadingData(env);
	tmp1 = data->nextinfo;
	data->nextinfo = NULL;
	while (tmp1!=NULL){
		tmp2 = tmp1->nextinfo;
		free(tmp1);
		tmp1 = tmp2;
	}
}
