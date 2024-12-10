#pragma once

#include <clips.h>
#include "ffi_constants.h"
#include "ffi_clips_interface.h"

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


/**
 * tidy up after using regex. Should be used, when closing any graph.
 */
void free_regex();

/**
 * method to add node to fact.
 */
int add_n3_as_expression_at_slot(
		FactBuilder *theFB, N3String node, const char* slot_name);

/**
 * asdf
 */
char *clipsvalue_to_n3(CLIPSValue value);

/**
 * Only returns value of Literal
 */
char *clipslexeme_to_value(CLIPSLexeme *value);


/**
 * apparantly needed for ASN3
 */
int percent_decode(char *dst, const char *src, const size_t len);


/**
 * clips userdefined function for percent encoding.
 */
void _clipsudf_percent_encoding(
		Environment *env, UDFContext *udfc, UDFValue *out);
