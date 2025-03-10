#pragma once

#include <clips.h>
#include "ffi_constants.h"
#include "ffi_clips_interface.h"

#include <regex.h>

/** CRIFI_TIME_DATA_INDEX
 * index in which clips Environment stores data needed for crifi_time.
 * Can be overwritten if there is an index conflict.
 * Otherwise will be internally handled.
 */
#ifndef CRIFI_N3PARSER_DATA_INDEX
#define CRIFI_N3PARSER_DATA_INDEX USER_ENVIRONMENT_DATA + 2
#endif

typedef struct crifiN3ParserData{
	uint next_blanknode_id;
	regex_t reg_uriref;
	regex_t reg_blanknode;
	regex_t reg_datatype;
	regex_t reg_datatype_single;
	regex_t reg_lang;
	regex_t reg_lang_single;
	regex_t reg_simple;
	regex_t reg_simple_single;
	regex_t reg_clipsvalue_langString;
	regex_t reg_clipsvalue_literal;
} CRIFIN3ParserData;

/** LoadingCRIFIN3ParserData
 */
#define LoadingCRIFIN3ParserData(theEnv) \
	((struct crifiN3ParserData *) GetEnvironmentData(theEnv, CRIFI_N3PARSER_DATA_INDEX))


bool crifi_n3parserdata_register_data(Environment *env);
bool initialize_crifi_n3parserdata(CRIFIN3ParserData *data);
void free_crifi_n3parserdata(CRIFIN3ParserData *data);



///needed size for N3 representation of given clips lexeme, translated via
///percent_decode
#define NEEDEDSIZEN3( lexeme ) strlen( lexeme ) + sizeof("\"\"\0")

///Will save n3 representation of lexeme in temporary char[] var.
#define ASN3(var, lexeme) char var[strlen( lexeme ) + sizeof("\"\"\0")]; percent_decode(n3representation, lexeme, strlen(lexeme));

#define ISPLAINLITERAL(clipsvalue) NULL != strstr(clipsvalue->contents, "@@")
///Find the datatype of a builtin literal
#define FINDDATATYPE(pos, length, clipsvalue)\
	size_t length;\
	char* pos = strstr(clipsvalue->contents, "^^");\
	if (pos!=NULL){\
		pos += 2;\
	} else if (NULL != strstr(clipsvalue->contents, "@@")){\
		pos ="http://www.w3.org/1999/02/22-rdf-syntax-ns#PlainLiteral";\
	} else {\
		pos = "http://www.w3.org/2001/XMLSchema#string";\
	}\
	length = strlen(pos);

#define FINDVALUE(pos, length, clipsvalue)\
	size_t length;\
	char* pos = strstr(clipsvalue->contents, "^^");\
	if(pos == NULL){pos = strstr(clipsvalue->contents, "@@");}\
	if (pos!=NULL){\
		length = pos - clipsvalue->contents;\
		pos = clipsvalue->contents;\
	} else {pos = clipsvalue->contents; length = strlen(pos);}

///Use for temporary literal representations.
#define TEMPORARYINTERNALREPRESENTATION(varname, value, printed_value_length, value_format, datatype) char varname[printed_value_length + sizeof("^^\0") + sizeof(datatype)]; sprintf(varname, value_format , value); sprintf(1+strstr(varname, "\0"), "^^%s", datatype);


#ifdef __cplusplus
extern "C" {
#endif


/**
 * asdf
 */
char *clipsvalue_to_n3(Environment *env, CLIPSValue value);

/**
 * Only returns value of Literal
 */
char *clipslexeme_to_value(CLIPSLexeme *value);


/**
 * apparantly needed for ASN3
 */
int percent_decode(char *dst, const char *src, const size_t len);


size_t percent_encode(char* dst, const char *src, const size_t len);

/**
 * clips userdefined function for percent encoding.
 */
void _clipsudf_percent_encoding(
		Environment *env, UDFContext *udfc, UDFValue *out);


int value_and_lang_to_slotstring(char* result, const char* value, size_t value_length, const char* lang, size_t lang_length);

int value_and_datatype_to_slotstring(char* result, const char* value, size_t value_length, const char* datatype, size_t datatype_length);

/**
 *
 */
char* lexeme_extract_lexical(Environment *env, CLIPSLexeme *lexeme);

char* lexeme_extract_datatype(Environment *env, CLIPSLexeme *lexeme);

char* lexeme_extract_lang(Environment *env, CLIPSLexeme *lexeme);

int n3_as_clipsvalue(Environment *env, N3String node, CLIPSValue *target);

char* value_and_lang_to_string(const char* value, size_t value_length, const char* lang, size_t lang_length);
int value_and_lang_to_clipsvalue(Environment *env, const char* value, size_t value_length, const char* lang, size_t lang_length, CLIPSValue *result);

char* value_and_datatype_to_string(const char* value, size_t value_length, const char* datatype, size_t datatype_length);
int value_and_datatype_to_clipsvalue(Environment *env, const char* value, size_t value_length, const char* datatype, size_t datatype_length, CLIPSValue *result);

int new_blanknode(Environment *env, CLIPSValue *target);
int blanknode_from_idstring(Environment *env, const char* id, CLIPSValue *target);
int uri_to_clipsvalue(Environment *env, const char* uri, size_t uri_length, CLIPSValue *result);

#ifdef __cplusplus
}
#endif
