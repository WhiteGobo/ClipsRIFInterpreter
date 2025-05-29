#include "info_query.h"

char* genclipscode_iri(Environment *env, char* iri){
	char* result = malloc(strlen(iri) + sizeof("<> "));
	if (result != NULL) {
		sprintf(result, "<%s>", iri);
	}
	return result;
}

char* genclipscode_lexical(Environment *env, CLIPSValue clipsvalue){
	int err;
	size_t datatype_length, value_length;
	char *value, *datatype = NULL, *lang, *lexical;
	char *valuestring;
	char *clipsstring, *result;
	CLIPSValue tmp_cv;

	lexical = extract_lexical(env, clipsvalue.header);
	if (lexical == NULL) return NULL;
	lang = extract_lang(env, clipsvalue.header);
	if (lang != NULL){
		err = value_and_lang_to_clipsvalue(env,
				lexical, strlen(lexical),
				lang, strlen(lang), &tmp_cv);
		if (err != 0){
			return NULL;
		}
	} else {
		datatype = extract_datatype(env, clipsvalue.header);
		if (datatype == NULL){
			free(datatype);
			return NULL;
		}
		if (datatype != NULL){
			datatype_length = strlen(datatype);
		} else {
			datatype_length = 0;
		}
		err = value_and_datatype_to_clipsvalue(env,
				lexical, strlen(lexical),
				datatype, datatype_length, &tmp_cv);
		if (err != 0){
			return NULL;
		}
	}
	free(lexical);
	free(datatype);
	free(lang);

	switch(tmp_cv.header->type){
                case SYMBOL_TYPE:
			valuestring = tmp_cv.lexemeValue->contents;
			result = malloc(strlen(valuestring) + 5);
			if (result == NULL) return NULL;
			sprintf(result, "<%s>", valuestring);
			break;
		case STRING_TYPE:
			valuestring = tmp_cv.lexemeValue->contents;
			result = malloc(strlen(valuestring) + 5);
			if (result == NULL) return NULL;
			sprintf(result, "\"%s\"", valuestring);
			break;
		case INTEGER_TYPE:
			result = malloc(30);
			if (result == NULL) return NULL;
			sprintf(result, "%d", tmp_cv.integerValue->contents);
			break;
		case FLOAT_TYPE:
			result = malloc(30);
			if (result == NULL) return NULL;
			sprintf(result, "%f", tmp_cv.floatValue->contents);
			break;
		default:
			return NULL;
	}
	return result;
}


char* genclipscode_local(Environment *env, CLIPSValue context, const char *value){
	char *cntxt_str;
	char* result;
	switch(context.header->type){
                case SYMBOL_TYPE:
		case STRING_TYPE:
			cntxt_str = context.lexemeValue->contents;
			break;
		default:
			return NULL;
	}
	result = malloc(strlen(value) + strlen(cntxt_str) + sizeof(10));
	if (result != NULL) {
		sprintf(result, "_:l%sn%s", cntxt_str, value);
	}
	return result;
}
