/** \file n3parser.c
 * 
 */

#include "percent_encode.h"
#include <regex.h>
#include "n3parser.h"
#include "ffi_constants.h"
#include <clips.h>

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

bool regex_initialized = false;
regex_t reg_datatype;
regex_t reg_datatype_single;
regex_t reg_lang;
regex_t reg_lang_single;
regex_t reg_simple;
regex_t reg_simple_single;
regex_t reg_clipsvalue_langString;
regex_t reg_clipsvalue_literal;

#define REGOPTION REG_EXTENDED

void free_regex(){
	if (regex_initialized){
		regex_initialized = false;
		regfree(&reg_datatype);
		regfree(&reg_datatype_single);
		regfree(&reg_lang);
		regfree(&reg_lang_single);
		regfree(&reg_simple);
		regfree(&reg_simple_single);
		regfree(&reg_clipsvalue_langString);
		regfree(&reg_clipsvalue_literal);
	}
}

#define REGEXURIREF "^<("URLSYMBOLS"*)>$"
#define REGEXBLANKNODE "^_:("URLSYMBOLS"+)$"
#define REGEXDATATYPESINGLE "^\'(.*)\'[°^][°^]<("URLSYMBOLS"*)>$"
#define REGEXDATATYPE "^\"(.*)\"[°^][°^]<("URLSYMBOLS"*)>$"
#define REGEXLANG "^\"(([^\"]|(\\\"))*)\"@([a-zA-Z\-]*)$"
#define REGEXLANGSINGLE "^\'(([^\']|(\\\'))*)\'@([a-zA-Z\-]*)$"
#define REGEXSIMPLESINGLE "^\'(.*)\'$"
#define REGEXSIMPLE "^\"(.*)\"$"
#define REGEXCLIPSVALUELANGSTRING "^(.*)@@(.*)$"
#define REGEXCLIPSVALUELITERAL "^(.*)[°^][°^](.*)$"

static int init_regex(){
	int err;
	if (regex_initialized){
		return 0;
	} else {
		err = regcomp(&reg_datatype_single,
				REGEXDATATYPESINGLE,
				//"^\'(.*)\'[°^][°^]<("URLSYMBOLS"*)>$",
				REGOPTION);
		if (err != 0) return err;
		err = regcomp(&reg_datatype,
				REGEXDATATYPE,
				//"^\"(.*)\"[°^][°^]<("URLSYMBOLS"*)>$",
				REGOPTION);
		if (err != 0) return err;
		err = regcomp(&reg_lang,
				REGEXLANG,
				//"^\"(([^\"]|(\\\"))*)\"@([a-zA-Z\-]*)$",
				REG_EXTENDED);
		if (err != 0) return err;
		err = regcomp(&reg_lang_single, 
				REGEXLANGSINGLE,
				//"^\'(([^\']|(\\\'))*)\'@([a-zA-Z\-]*)$",
				REG_EXTENDED);
		if (err != 0) return err;
		err = regcomp(&reg_simple_single,
				REGEXSIMPLESINGLE,
				//"^\'(.*)\'$",
				REG_EXTENDED);
		if (err != 0) return err;
		err = regcomp(&reg_simple,
				REGEXSIMPLE,
				//"^\"(.*)\"$",
				REGOPTION);
		if (err != 0) return err;

		err = regcomp(&reg_clipsvalue_langString,
				REGEXCLIPSVALUELANGSTRING,
				//"^(.*)@@(.*)$",
				REGOPTION);
		if (err != 0) return err;
		err = regcomp(&reg_clipsvalue_literal,
				REGEXCLIPSVALUELITERAL,
				//"^(.*)[°^][°^](.*)$",
				REGOPTION);
		if (err != 0) return err;
		regex_initialized = true;
		return 0;
	}
}
#undef REGOPTION

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
	if (COMPARE_RDF_STRING(datatype, datatype_length)) {
		result[offset] = '\0';
		return 0;
	}
	result_tmp = result + offset;
	if (datatype == NULL || ISURI(datatype, datatype_length, _RDF_string_)){
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
static int value_and_lang_to_n3(char* result, const char* value, size_t value_length, const char* lang, size_t lang_length){
	char* result_tmp;
	//char* result = malloc( value_length + lang_length + 3);
	size_t offset = percent_encode(result, value, value_length);
	result_tmp = result + offset;
	result_tmp[0] = '@';
	result_tmp += 1;
	memcpy(result_tmp, lang, lang_length);
	result_tmp += lang_length;
	result_tmp[0] = '\0';
	return 0;
}

static int value_and_datatype_to_n3(char* result, const char* value, size_t value_length, const char* datatype, size_t datatype_length){
	if (ISURI(datatype, datatype_length, _RDF_langString_)){
		return value_and_lang_to_slotstring(result, value, value_length, "", 0);
	}
	char* result_tmp;
	//char* result;
	size_t offset =0;
	//result = malloc( value_length + datatype_length + sizeof("\"\"^^<>"));
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
	return 0;
}


/**
 * Convert a literal encoded in a fact.
 *
 * For safe usage n3representation has to be of strlen(builtinliteral) + 1
 */
static int builtin_to_n3(char* n3representation, const char* builtinliteral){
	int err;
	const size_t max_matches = 3; //1 + #groups 
	regmatch_t matches[5];
	const char *value, *datatype, *lang, *tmpold;
	size_t value_length, datatype_length, lang_length;

	if (0 != init_regex()){
		printf("Failed to compile regex_datatype\n");
		return 3;
	}
	err = regexec(&reg_clipsvalue_langString, builtinliteral, max_matches, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = builtinliteral + matches[1].rm_so;
		lang_length = matches[2].rm_eo - matches[2].rm_so;
		lang = builtinliteral + matches[2].rm_so;
		return value_and_lang_to_n3(n3representation, value, value_length, datatype, datatype_length);
	} else if (err != REG_NOMATCH){
		printf("Regex expression produced error.0\n");
		return 2;
	}
	err = regexec(&reg_clipsvalue_literal, builtinliteral, max_matches, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = builtinliteral + matches[1].rm_so;
		datatype_length = matches[2].rm_eo - matches[2].rm_so;
		datatype = builtinliteral + matches[2].rm_so;
		return value_and_datatype_to_n3(n3representation, value, value_length, datatype, datatype_length);
	} else if (err != REG_NOMATCH){
		printf("Regex expression produced error.0\n");
		return 2;
	}
	return 1;
}

/**
 * Percent-encoding
 */
static int literal_to_builtin(char *builtinEncoded, N3String node){
	int err;
	const size_t max_matches = 3; //1 + #groups 
	regmatch_t matches[5];
	char *newnode, *tmpnew;
	const char *value, *datatype, *lang, *tmpold;
	size_t value_length, datatype_length, lang_length;

	if (0 != init_regex()){
		printf("Failed to compile regex_datatype\n");
		return 3;
	}
	err = regexec(&reg_datatype, node, max_matches, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		datatype_length = matches[2].rm_eo - matches[2].rm_so;
		datatype = node + matches[2].rm_so;
		return value_and_datatype_to_slotstring(builtinEncoded, value, value_length, datatype, datatype_length);
	} else if (err != REG_NOMATCH){
		printf("Regex expression produced error.0\n");
		return 2;
	}
	err = regexec(&reg_datatype_single, node, max_matches, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		datatype_length = matches[2].rm_eo - matches[2].rm_so;
		datatype = node + matches[2].rm_so;
		return value_and_datatype_to_slotstring(builtinEncoded, value, value_length, datatype, datatype_length);
	} else if (err != REG_NOMATCH){
		printf("Regex expression produced error.1\n");
		return 2;
	}

	err = regexec(&reg_lang, node, 1+4, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		lang_length = matches[4].rm_eo - matches[4].rm_so;
		lang = node + matches[4].rm_so;
		return value_and_lang_to_slotstring(builtinEncoded, value, value_length, lang, lang_length);
	} else if (err != REG_NOMATCH){
		printf("Regex expression produced error.1\n");
		return 2;
	}
	err = regexec(&reg_lang_single, node, 1+4, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		lang_length = matches[4].rm_eo - matches[4].rm_so;
		lang = node + matches[4].rm_so;
		return value_and_lang_to_slotstring(builtinEncoded, value, value_length, lang, lang_length);
	} else if (err != REG_NOMATCH){
		printf("Regex expression produced error.1\n");
		return 2;
	}
	err = regexec(&reg_simple, node, max_matches, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		return value_and_datatype_to_slotstring(builtinEncoded, value, value_length, _RDF_string_, sizeof(_RDF_string_));
	} else if (err != REG_NOMATCH){
		printf("Regex expression produced error.1\n");
		return 2;
	}
	err = regexec(&reg_simple_single, node, max_matches, NULL, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		return value_and_datatype_to_slotstring(builtinEncoded, value, value_length, _RDF_string_, sizeof(_RDF_string_));
	} else if (err != REG_NOMATCH){
		printf("Regex expression produced error.1\n");
		return 2;
	}
	return 1;
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

	if (0 != init_regex()){
		printf("Failed to compile regex_datatype\n");
		return 3;
	}
	err = regexec(&reg_datatype, node, max_matches, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		datatype_length = matches[2].rm_eo - matches[2].rm_so;
		datatype = node + matches[2].rm_so;
		return value_and_datatype_to_clipsvalue(env, value, value_length, datatype, datatype_length, result);
	} else if (err != REG_NOMATCH){
		printf("Regex expression produced error.0\n");
		return 2;
	}
	err = regexec(&reg_datatype_single, node, max_matches, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		datatype_length = matches[2].rm_eo - matches[2].rm_so;
		datatype = node + matches[2].rm_so;
		return value_and_datatype_to_clipsvalue(env, value, value_length, datatype, datatype_length, result);
	} else if (err != REG_NOMATCH){
		printf("Regex expression produced error.1\n");
		return 2;
	}

	err = regexec(&reg_lang, node, 1+4, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		lang_length = matches[4].rm_eo - matches[4].rm_so;
		lang = node + matches[4].rm_so;
		return value_and_lang_to_clipsvalue(env, value, value_length, lang, lang_length, result);
	} else if (err != REG_NOMATCH){
		printf("Regex expression produced error.1\n");
		return 2;
	}
	err = regexec(&reg_lang_single, node, 1+4, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		lang_length = matches[4].rm_eo - matches[4].rm_so;
		lang = node + matches[4].rm_so;
		return value_and_lang_to_clipsvalue(env, value, value_length, lang, lang_length, result);
	} else if (err != REG_NOMATCH){
		printf("Regex expression produced error.1\n");
		return 2;
	}
	err = regexec(&reg_simple, node, max_matches, matches, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		return value_and_datatype_to_clipsvalue(env, value, value_length, _RDF_string_, sizeof(_RDF_string_), result);
	} else if (err != REG_NOMATCH){
		printf("Regex expression produced error.1\n");
		return 2;
	}
	err = regexec(&reg_simple_single, node, max_matches, NULL, 0);
	if (err == 0) {
		value_length = matches[1].rm_eo - matches[1].rm_so;
		value = node + matches[1].rm_so;
		return value_and_datatype_to_clipsvalue(env, value, value_length, _RDF_string_, sizeof(_RDF_string_), result);
	} else if (err != REG_NOMATCH){
		printf("Regex expression produced error.1\n");
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
		printf("Regex expression produced error.0\n");
		return 2;
	}

	err = regexec(&(data->reg_blanknode), node, 5, matches, 0);
	if (err == 0) {
		return blanknode_as_clipsvalue(env, node, target);
	} else if (err != REG_NOMATCH){
		printf("Regex expression produced error.0\n");
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

int add_n3_as_expression_at_slot(
		FactBuilder *theFB, N3String node, const char* slot_name)
{
	//FBPutSlot(theFB, slot_name, n3_to_clipsvalue(node))
	int err;
	//char* builtinEncoded;
	if (theFB == NULL) return 5;
	if (slot_name == NULL) return 4;
	if (node == NULL) return 6;
	if (isURIRef(node)){
		FBPutSlotSymbol(theFB, slot_name, node);
		return 0;
	} else if (isBlankNode(node)) {
		FBPutSlotSymbol(theFB, slot_name, node);
		return 0;
	} else if (isLiteral(node)) {
		char builtinEncoded[5 + 3*strlen(node)+ sizeof(_RDF_string_)];
		err = literal_to_builtin(builtinEncoded, node);
		if (err != 0) return err;
		//if (builtinEncoded == NULL) return 3;
		FBPutSlotString(theFB, slot_name, builtinEncoded);
		//free(builtinEncoded);
		return 0;
	}
	return 2;
}

char *clipsvalue_to_n3(CLIPSValue value){
	if (value.header->type == SYMBOL_TYPE){
		const char *tmp = value.lexemeValue->contents;
		char *term = (char*) malloc((strlen(tmp)+1)*sizeof(char));
		strcpy(term, tmp);
		return term;
	} else if (value.header->type == STRING_TYPE) {
		const char *tmp = value.lexemeValue->contents;
		char *n3representation = malloc(3*strlen(tmp) + sizeof("\"\"\0"));
		int err = builtin_to_n3(n3representation, tmp);
		if (err != 0){
			free(n3representation);
			return NULL;
		} else {
			return n3representation;
		}
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


char* extract_lexical(Environment *env, CLIPSLexeme *lexeme){
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


char* extract_datatype(Environment *env, CLIPSLexeme *lexeme){
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

char* extract_lang(Environment *env, CLIPSLexeme *lexeme){
	if (lexeme == NULL) return NULL;
	size_t length;
	char* retString;
	char* pos = strstr(lexeme->contents, "@@");
	if (pos == NULL){
		retString = malloc(1);
		retString[0] = '\0';
		return retString;
	}
	pos += 2;
	length = strlen(pos);
	retString = malloc(length+1);
	strcpy(retString, pos);
	return retString;
}



/**
 * method given at registration for tidying up timedata after Environment is
 * freed
 */
static void release_crifi_n3parserdata(Environment *env){
	free_crifi_n3parserdata(LoadingCRIFIN3ParserData(env));
}

bool crifi_n3parserdata_register_data(Environment *env){
	if (! AllocateEnvironmentData(env, CRIFI_N3PARSER_DATA_INDEX,
						sizeof(CRIFIN3ParserData),
						release_crifi_n3parserdata))
	{
		Writeln(env, "Internal error 0. "
				"Cant load plugin for n3 parsing..");
		ExitRouter(env, EXIT_FAILURE);
		return false;
	}
	if(!initialize_crifi_n3parserdata(LoadingCRIFIN3ParserData(env))){
		return false;
	}
	return true;
}

bool initialize_crifi_n3parserdata(CRIFIN3ParserData *data){
	int err;
	err = regcomp(&(data->reg_uriref),
			REGEXURIREF,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_blanknode),
			REGEXBLANKNODE,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_datatype),
			REGEXDATATYPE,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_datatype_single),
			REGEXDATATYPESINGLE,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_lang),
			REGEXLANG,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_lang_single),
			REGEXLANGSINGLE,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_simple),
			REGEXSIMPLE,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_simple_single),
			REGEXSIMPLESINGLE,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_clipsvalue_langString),
			REGEXCLIPSVALUELANGSTRING,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_clipsvalue_literal),
			REGEXCLIPSVALUELITERAL,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	return true;
}

void free_crifi_n3parserdata(CRIFIN3ParserData *data){
	regfree(&(data->reg_datatype_single));
	regfree(&(data->reg_uriref));
	regfree(&(data->reg_datatype));
	regfree(&(data->reg_datatype_single));
	regfree(&(data->reg_lang));
	regfree(&(data->reg_lang_single));
	regfree(&(data->reg_simple));
	regfree(&(data->reg_simple_single));
	regfree(&(data->reg_clipsvalue_langString));
	regfree(&(data->reg_clipsvalue_literal));
}



int value_and_datatype_to_clipsvalue(Environment *env, const char* value, size_t value_length, const char* datatype, size_t datatype_length, CLIPSValue *result){
	size_t offset;
	char *result_tmp, *result_safe;
	if (datatype != NULL && ISURI(datatype, datatype_length, _RDF_langString_)){
		return value_and_lang_to_clipsvalue(env, value, value_length, "", 0, result);
	}
	result_safe = malloc( 3*value_length + datatype_length + 3);
	offset = percent_encode(result_safe, value, value_length);
	result_tmp = result_safe + offset;
	if (datatype == NULL || ISURI(datatype, datatype_length, _RDF_string_)){
		result_tmp[0] = '\0';
	} else {
		result_tmp[0] = '^';
		result_tmp[1] = '^';
		result_tmp += 2;
		memcpy(result_tmp, datatype, datatype_length);
		result_tmp[datatype_length] = '\0';
	}
	result->lexemeValue = CreateString(env, result_safe);
	free(result_safe);
	return 0;
}

int value_and_lang_to_clipsvalue(Environment *env, const char* value, size_t value_length, const char* lang, size_t lang_length, CLIPSValue *result){
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
	result->lexemeValue = CreateString(env, result_safe);
	free(result_safe);
	return 0;
}
