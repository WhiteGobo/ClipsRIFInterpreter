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

typedef enum {
	GENLOCAL_CNTXT_BNODE = 'b',
	GENLOCAL_CNTXT_URI = 'u',
	GENLOCAL_CNTXT_STRING = 's'
} GENLOCAL_CNTXT_ID;

char* genclipscode_local(Environment *env, CLIPSValue context, const char *value){
	char *cntxt_str;
	char* result;
	GENLOCAL_CNTXT_ID cntxt_id;
	size_t l_value, l_cntxt;
	if (value == NULL) {
		return NULL;
	}
	if (clipsvalue_is_literal(env, context)) {
		cntxt_str = extract_lexical(env, context.header);
		cntxt_id = GENLOCAL_CNTXT_STRING;
	} else if (clipsvalue_is_uri(env, context)){
		cntxt_str = extract_uri(env, context.header);
		cntxt_id = GENLOCAL_CNTXT_URI;
	} else if (clipsvalue_is_bnode(env, context)){
		cntxt_str = extract_bnodeid(env, context.header);
		cntxt_id = GENLOCAL_CNTXT_BNODE;
	} else {
		return NULL;
	}
	l_value = strlen(value);
	l_cntxt = strlen(cntxt_str);
	if (l_value == 0 || l_cntxt == 0 ){
		free(cntxt_str);
		return NULL;
	}
	result = malloc(l_value + l_cntxt + 30);
	if (result != NULL) {
		//sprintf(result, "_:l%c%sn%s", cntxt_id, cntxt_str, value);
		sprintf(result, "<http://white.gobo/local/%c/%s#%s>", cntxt_id, cntxt_str, value);
	}
	free(cntxt_str);
	return result;
}
