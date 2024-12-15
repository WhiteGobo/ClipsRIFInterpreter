#pragma once

#include <ffi_clips_interface.h>
#include <string>

#define _CRIFI_RM_import_ "http://white.gobo/ResourceManager/import"

///TODO: replace (create-clips-script) with this, maybe
#define _CRIFI_RM_create_clips_script_ "http://white.gobo/ResourceManager/create-clips-script"

///will generate logic via generate_rdf_entailment
#define _ENTAILMENT_RDF_ "http://www.w3.org/ns/entailment/RDF"

#ifndef CRIFI_RM_INDEX_DATA
///id for resourcemanager plugin for clips
#define CRIFI_RM_INDEX_DATA USER_ENVIRONMENT_DATA + 0
#endif


typedef struct TriplesLinkedList* (*LoadingFunction)(
		const void *context, const char *location);

typedef struct loadingInfo
{
	LoadingFunction loadingFunction;
	const void *context;
	struct loadingInfo* nextinfo;
} LoadingInfo;

typedef struct indexData
{
	struct loadingInfo* nextinfo;
} RdfResourceLoadingData;
#define LoadingData(theEnv) \
	((struct indexData *) GetEnvironmentData(theEnv,CRIFI_RM_INDEX_DATA))

bool add_needed_user_functions(struct clips_graph_container graph,
		LoadingFunction* loading_functions,
		const void **loading_function_context,
		unsigned int loading_functions_length);

bool append_loading_function(struct clips_graph_container graph,
		LoadingFunction loading_function,
		const void *context
		);

void free_loading_functions(Environment *env);

std::string *create_rules(struct TriplesLinkedList* triples, const char* profile);
