#include "info_query.h"

char* genclipscode_iri(Environment *env, char* iri){
	char* result = malloc(strlen(iri) + sizeof("<> "));
	if (result != NULL) {
		sprintf(result, "<%s>", iri);
	}
	return result;
}

char* genclipscode_lexical(Environment *env, char* value, char* datatype){
	size_t datatype_length, value_length;
	char *clipsstring, *result;
	value_length = strlen(value);
	if (datatype != NULL){
		datatype_length = strlen(datatype);
	} else {
		datatype_length = 0;
	}
	clipsstring = value_and_datatype_to_string(value, value_length,
						datatype, datatype_length);
	if (clipsstring == NULL){
		return NULL;
	}
	result = malloc(strlen(clipsstring) + sizeof("\"\" "));
	if (result != NULL){
		sprintf(result, "\"%s\"", clipsstring);
	}
	free(clipsstring);
	return result;
}
