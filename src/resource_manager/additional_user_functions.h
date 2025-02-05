#pragma once

#include "resource_manager.h"
#include <ffi_clips_interface.h>
#include <string>

#define _CRIFI_RM_import_ "http://white.gobo/ResourceManager/import"

///TODO: replace (create-clips-script) with this, maybe
#define _CRIFI_RM_create_clips_script_ "http://white.gobo/ResourceManager/create-clips-script"

///will generate logic via generate_rdf_entailment
#define _ENTAILMENT_RDF_ "http://www.w3.org/ns/entailment/RDF"
#define _ENTAILMENT_RDFS_ "http://www.w3.org/ns/entailment/RDFS"
#define _ENTAILMENT_OWLDIRECT_ "http://www.w3.org/ns/entailment/OWL-Direct"
#define _ENTAILMENT_SIMPLE_ "http://www.w3.org/ns/entailment/Simple"

#ifndef CRIFI_RM_INDEX_DATA
///id for resourcemanager plugin for clips
#define CRIFI_RM_INDEX_DATA USER_ENVIRONMENT_DATA + 0
#endif



typedef struct indexData
{
	struct loadingInfo* nextinfo;
} RdfResourceLoadingData;
#define LoadingData(theEnv) \
	((struct indexData *) GetEnvironmentData(theEnv,CRIFI_RM_INDEX_DATA))

bool add_needed_user_functions(crifi_graph graph,
		LoadingFunction* loading_functions,
		const void **loading_function_context,
		unsigned int loading_functions_length,
		std::string *output);

bool append_loading_function(crifi_graph graph,
		LoadingFunction loading_function,
		const void *context
		);

void free_loading_functions(Environment *env);

std::string *create_rules(struct TriplesLinkedList* triples, const char* profile);
