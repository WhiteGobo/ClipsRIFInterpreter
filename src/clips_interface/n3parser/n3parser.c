/** \file n3parser.c
 * 
 */

#include "percent_encode.h"
#include <regex.h>
#include "n3parser.h"
#include "ffi_constants.h"
#include <clips.h>

#define SETERROR(env, msg) SetErrorValue(env, (TypeHeader*) CreateString(env, msg));

static bool isURIRef(Utf8String node){return node[0] == '<';}
static bool isBlankNode(Utf8String node){return node[0] == '_';}
static bool isLiteral(Utf8String node){
	return ((node[0] == '"') || (node[0] == '\''));
}

/**
 * Transforms percent encoding to utf8
 * To safely use this, dst should have size 3*len
 */
size_t percent_encode(char* dst, const char *src, const size_t len)
{
	size_t i = 0, j = 0;
	while (i < len)
	{
		const char octet = src[i++];
		const int32_t code = ((int32_t*)uri_encode_tbl)[ (unsigned char)octet ];
		if (code) {
			*((int32_t*)&dst[j]) = code;
			j += 3;
		}
		else dst[j++] = octet;
	}
	dst[j] = '\0';
	return j;
}

/**
 * Transforms utf8 to percent encoding
 * TODO: remove hexval
 */
int percent_decode(char *dst, const char *src, const size_t len)
{
	size_t i = 0, j = 0;
	while(i < len)
	{
		int copy_char = 1;
		if(src[i] == '%' && i + 2 < len)
		{
			const unsigned char v1 = hexval[ (unsigned char)src[i+1] ];
			const unsigned char v2 = hexval[ (unsigned char)src[i+2] ];

			/* skip invalid hex sequences */
			if ((v1 | v2) != 0xFF)
			{
				dst[j] = (v1 << 4) | v2;
				j++;
				i += 3;
				copy_char = 0;
			}
		}
		if (copy_char)
		{
			dst[j] = src[i];
			i++;
			j++;
		}
	}
	dst[j] = '\0';
	return j;
}


int value_and_lang_to_slotstring(char* result, const char* value, size_t value_length, const char* lang, size_t lang_length){
	char* result_tmp;
	//char* result = malloc( 3*value_length + lang_length + 3);
	size_t offset = percent_encode(result, value, value_length);
	result_tmp = result + offset;
	result_tmp[0] = '@';
	result_tmp[1] = '@';
	result_tmp += 2;
	memcpy(result_tmp, lang, lang_length);
	result_tmp += lang_length;
	result_tmp[0] = '\0';
	return 0;
}

#define COMPARE_RDF_STRING(dt, dt_l) dt_l >= sizeof(_RDF_string_)-1 && (0 == memcmp(dt, _RDF_string_, sizeof(_RDF_string_)-1))
/**
 *
 * result has to be 3*value_length + datatype_length + sizeof("^^\0")
 * defaults to _RDF_string_ if NULL is given as datatype
 */
int value_and_datatype_to_slotstring(char* result, const char* value, size_t value_length, const char* datatype, size_t datatype_length){
	if (datatype != NULL && ISURI(datatype, datatype_length, _RDF_langString_)){
		return value_and_lang_to_slotstring(result, value, value_length, "", 0);
	}
	char* result_tmp;
	//char* result = malloc( 3*value_length + datatype_length + 3);
	size_t offset = percent_encode(result, value, value_length);
	result_tmp = result + offset;
	if (
			datatype == NULL 
			|| ISURI(datatype, datatype_length, _RDF_string_)
			|| ISURI(datatype, datatype_length, _XS_string_)
	   ){
		result_tmp[0] = '\0';
		return 0;
	}
	result_tmp[0] = '^';
	result_tmp[1] = '^';
	result_tmp += 2;
	memcpy(result_tmp, datatype, datatype_length);
	result_tmp[datatype_length] = '\0';
	return 0;
	//return result;
}
#undef COMPARE_RDF_STRING

/**
 *
 * result has to be 3*value_length + lang_length + sizeof("@@\0")
 */
static char* value_and_lang_to_n3(const char* value, const char* lang){
	size_t value_length = strlen(value);
	size_t lang_length = strlen(lang);
	char* result = malloc( value_length + lang_length + 8);
	char* result_tmp;
	size_t offset = percent_encode(result, value, value_length);
	result_tmp = result + offset;
	result_tmp[0] = '@';
	result_tmp += 1;
	memcpy(result_tmp, lang, lang_length);
	result_tmp += lang_length;
	result_tmp[0] = '\0';
	return result;
}

static char* value_and_datatype_to_n3(const char* value, const char* datatype){
	size_t datatype_length = strlen(datatype);
	if (ISURI(datatype, datatype_length, _RDF_langString_)){
		return value_and_lang_to_n3(value, "");
	}
	size_t value_length = strlen(value);
	char *result\
		= malloc( value_length + datatype_length + sizeof("\"\"^^<>"));
	char* result_tmp;
	size_t offset = 0;
	result_tmp = result;
	result_tmp[0] = '"';
	result_tmp += 1;
       	offset = percent_decode(result_tmp, value, value_length);
	result_tmp = result + offset;
	result_tmp[1] = '"';
	result_tmp[2] = '^';
	result_tmp[3] = '^';
	result_tmp[4] = '<';
	result_tmp += 5;
	memcpy(result_tmp, datatype, datatype_length);
	result_tmp[datatype_length] = '>';
	result_tmp[datatype_length+1] = '\0';
	return result;
}


static int blanknode_as_clipsvalue(Environment *env, N3String node, CLIPSValue *target){
	target->lexemeValue = CreateSymbol(env, node);
	return 0;
}

static int literal_to_clipsvalue(Environment *env, N3String node, CLIPSValue *result){
	int err;
	const size_t max_matches = 3; //1 + #groups 
	regmatch_t matches[5];
	char *newnode, *tmpnew;
	const char *value, *datatype, *lang, *tmpold;
	size_t value_length, datatype_length, lang_length;

	CRIFIN3ParserData* rgx = LoadingCRIFIN3ParserData(env);

	/*
	if (0 != init_regex()){
		//fprintf(stderr, "Failed to compile regex_datatype\n");
		return 3;
	}*/
	//err = regexec(&reg_datatype, node, max_matches, matches, 0);
	err = regexec(&(rgx->reg_datatype), node, max_matches, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		datatype_length = matches[2].rm_eo - matches[2].rm_so;
		datatype = node + matches[2].rm_so;
		return value_and_datatype_to_clipsvalue(env, value, value_length, datatype, datatype_length, result);
	} else if (err != REG_NOMATCH){
		//fprintf(stderr, "Regex expression produced error.0\n");
		return 2;
	}
	//err = regexec(&reg_datatype_single, node, max_matches, matches, 0);
	err = regexec(&(rgx->reg_datatype_single), node, max_matches, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		datatype_length = matches[2].rm_eo - matches[2].rm_so;
		datatype = node + matches[2].rm_so;
		return value_and_datatype_to_clipsvalue(env, value, value_length, datatype, datatype_length, result);
	} else if (err != REG_NOMATCH){
		//fprintf(stderr, "Regex expression produced error.1\n");
		return 2;
	}

	//err = regexec(&reg_lang, node, 1+4, matches, 0);
	err = regexec(&(rgx->reg_lang), node, 1+4, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		lang_length = matches[4].rm_eo - matches[4].rm_so;
		lang = node + matches[4].rm_so;
		return value_and_lang_to_clipsvalue(env, value, value_length, lang, lang_length, result);
	} else if (err != REG_NOMATCH){
		//fprintf(stderr, "Regex expression produced error.1\n");
		return 2;
	}
	//err = regexec(&reg_lang_single, node, 1+4, matches, 0);
	err = regexec(&(rgx->reg_lang_single), node, 1+4, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		lang_length = matches[4].rm_eo - matches[4].rm_so;
		lang = node + matches[4].rm_so;
		return value_and_lang_to_clipsvalue(env, value, value_length, lang, lang_length, result);
	} else if (err != REG_NOMATCH){
		//fprintf(stderr, "Regex expression produced error.1\n");
		return 2;
	}
	err = regexec(&(rgx->reg_simple), node, max_matches, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		return value_and_datatype_to_clipsvalue(env, value, value_length, NULL, 0, result);
	} else if (err != REG_NOMATCH){
		//fprintf(stderr, "Regex expression produced error.1\n");
		return 2;
	}
	err = regexec(&(rgx->reg_simple_single), node, max_matches, NULL, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		return value_and_datatype_to_clipsvalue(env, value, value_length, NULL, 0, result);
	} else if (err != REG_NOMATCH){
		//fprintf(stderr, "Regex expression produced error.1\n");
		return 2;
	}
	return 1;
}

int n3_as_clipsvalue(Environment *env, N3String node, CLIPSValue *target){
	int err;
	CLIPSValue ret;
	regmatch_t matches[5];
	CRIFIN3ParserData *data = LoadingCRIFIN3ParserData(env);

	err = regexec(&(data->reg_uriref), node, 5, matches, 0);
	if (err == 0) {
		target->lexemeValue = CreateSymbol(env, node);
		return 0;
	} else if (err != REG_NOMATCH){
		return 2;
	}

	err = regexec(&(data->reg_blanknode), node, 5, matches, 0);
	if (err == 0) {
		return blanknode_as_clipsvalue(env, node, target);
	} else if (err != REG_NOMATCH){
		return 2;
	}

	err = literal_to_clipsvalue(env, node, target);
	if (err == 0){
		return 0;
	} else if (err != 1){
		return err;
	}
	return 1;
}


char *clipsvalue_to_n3(Environment *env, CLIPSValue value){
	char *lexical, *lang, *datatype, *retval;
	if (value.header->type == SYMBOL_TYPE){
		const char *tmp = value.lexemeValue->contents;
		char *term = (char*) malloc((strlen(tmp)+1)*sizeof(char));
		strcpy(term, tmp);
		return term;
	} else if (value.header->type == STRING_TYPE) {
		lexical = lexeme_extract_lexical(env, value.lexemeValue);
		if(NULL != strstr(value.lexemeValue->contents, "@@")){
			lang = lexeme_extract_lang(env, value.lexemeValue);
			retval = value_and_lang_to_n3(lexical, lang);
			free(lang);
		} else {
			datatype = lexeme_extract_datatype(env, value.lexemeValue);
			retval = value_and_datatype_to_n3(lexical, datatype);
			free(datatype);
		}
		free(lexical);
		return retval;
	}
	return NULL;
}

char *clipslexeme_to_value(CLIPSLexeme *value){
	const char *tmpptr;
	char *val, *endptr;
	int l;
	tmpptr = value->contents;
	endptr = strstr(tmpptr, "^^");
	if (endptr != NULL){
		l = endptr - tmpptr;
		val = malloc(3*l + sizeof("\0"));
		percent_decode(val, tmpptr, l);
		return val;
	}
	endptr = strstr(tmpptr, "@@");
	if (endptr != NULL){
		l = endptr - tmpptr;
		val = malloc(3*l + sizeof("\0"));
		percent_decode(val, tmpptr, l);
		return val;
	}
	l = strlen(tmpptr);
	val = malloc(3*l + sizeof("\0"));
	percent_decode(val, tmpptr, l);
	return val;
}

void _clipsudf_percent_encoding(
		Environment *env, UDFContext *udfc, UDFValue *out) {
	char* lexeme;
	UDFValue myval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &myval)) return;
	//if (myval.header != STRING_TYPE) return;
	ASN3(n3representation, myval.lexemeValue->contents);
	out->lexemeValue = CreateString(env, n3representation);
}


char* lexeme_extract_lexical(Environment *env, CLIPSLexeme *lexeme){
	if (lexeme == NULL) return NULL;
	size_t length;
	char* retString;
	char* pos = strstr(lexeme->contents, "^^");
	if (pos == NULL){ pos = strstr(lexeme->contents, "@@"); }
	if (pos != NULL){
		length = pos - lexeme->contents;
	} else {
		length = strlen(lexeme->contents);
	}
	retString = malloc(length + 1);
	percent_decode(retString, lexeme->contents, length);
	return retString;
}


char* lexeme_extract_datatype(Environment *env, CLIPSLexeme *lexeme){
	if (lexeme == NULL) return NULL;
	size_t length;
	char* retString;
	char* pos = strstr(lexeme->contents, "^^");
	if (pos != NULL){
		pos += 2;
		length = strlen(pos);
		retString = malloc(length+1);
		strcpy(retString, pos);
		return retString;
	}
	pos = strstr(lexeme->contents, "@@");
	if (pos != NULL){
		retString = malloc(sizeof(_RDF_langString_));
		strcpy(retString, _RDF_langString_);
		return retString;
	}

	retString = malloc(sizeof(_XS_string_));
	strcpy(retString, _XS_string_);
	return retString;
}

char* lexeme_extract_lang(Environment *env, CLIPSLexeme *lexeme){
	if (lexeme == NULL) return NULL;
	size_t length;
	char *retString, *dt;
	char* pos = strstr(lexeme->contents, "@@");
	if (pos == NULL){
		dt = lexeme_extract_datatype(env, lexeme);
		if (0 == strcmp(dt, _RDF_langString_)){
			retString = malloc(1);
			retString[0] = '\0';
		} else {
			retString = NULL;
		}
		free(dt);
		return retString;
	}
	pos += 2;
	length = strlen(pos);
	retString = malloc(length+1);
	strcpy(retString, pos);
	return retString;
}



char* value_and_datatype_to_string(const char* value, size_t value_length, const char* datatype, size_t datatype_length){
	size_t offset;
	char *result_tmp, *result_safe;
	result_safe = malloc( 3*value_length + datatype_length + 3);
	offset = percent_encode(result_safe, value, value_length);
	result_tmp = result_safe + offset;
	if (
			(datatype == NULL)
			|| (ISURI(datatype, datatype_length, _RDF_string_))
			|| (ISURI(datatype, datatype_length, _XS_string_))
	   ){
		result_tmp[0] = '\0';
	} else {
		result_tmp[0] = '^';
		result_tmp[1] = '^';
		result_tmp += 2;
		memcpy(result_tmp, datatype, datatype_length);
		result_tmp[datatype_length] = '\0';
	}
	return result_safe;
}

int value_and_datatype_to_clipsvalue(Environment *env, const char* value, size_t value_length, const char* datatype, size_t datatype_length, CLIPSValue *result){
	char *result_safe;
	if (datatype != NULL && ISURI(datatype, datatype_length, _RDF_langString_)){
		return value_and_lang_to_clipsvalue(env, value, value_length, "", 0, result);
	}
	result_safe = value_and_datatype_to_string(value, value_length, datatype, datatype_length);
	result->lexemeValue = CreateString(env, result_safe);
	free(result_safe);
	return 0;
}

char* value_and_lang_to_string(const char* value, size_t value_length, const char* lang, size_t lang_length){
	char* result_tmp;
	char* result_safe = malloc( 3*value_length + lang_length + 3);
	size_t offset = percent_encode(result_safe, value, value_length);
	result_tmp = result_safe + offset;
	result_tmp[0] = '@';
	result_tmp[1] = '@';
	result_tmp += 2;
	memcpy(result_tmp, lang, lang_length);
	result_tmp += lang_length;
	result_tmp[0] = '\0';
	return result_safe;
}

int value_and_lang_to_clipsvalue(Environment *env, const char* value, size_t value_length, const char* lang, size_t lang_length, CLIPSValue *result){
	char* result_safe = value_and_lang_to_string(value, value_length, lang, lang_length);
	result->lexemeValue = CreateString(env, result_safe);
	free(result_safe);
	return 0;
}

int new_blanknode(Environment *env, CLIPSValue* result){
	struct crifiN3ParserData *data = LoadingCRIFIN3ParserData(env);
	unsigned int graph_id = (unsigned int) env;
	char bnodeid[30];
	sprintf(bnodeid, "_:n%x_n%i", graph_id, data->next_blanknode_id++);
	result->lexemeValue = CreateSymbol(env, bnodeid);
	return 0;
}

int blanknode_from_idstring(Environment *env, const char* id, CLIPSValue *result){
	unsigned int graph_id = (unsigned int) env;
	char bnodeid[30 + strlen(id)];
	sprintf(bnodeid, "_:n%xs%s", graph_id, id);
	result->lexemeValue = CreateSymbol(env, bnodeid);
	return 0;
}

int uri_to_clipsvalue(Environment *env, const char* uri, size_t uri_length, CLIPSValue *result){
	char symb[uri_length + 3];
	symb[0]='<';
	memcpy(symb+1, uri, uri_length);
	symb[uri_length+1]='>';
	symb[uri_length+2]='\0';
	result->lexemeValue = CreateSymbol(env, symb);
	return 0;
}
