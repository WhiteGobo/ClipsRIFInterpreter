/**
 * See example_info_query.c for an example.
 * TODO: gather all internal symbols to assert search and extract statements
 * 	from graph.
 */
#pragma once

#include <ffi_clips_interface.h>
#include <n3parser.h>
#include "dataspace_constants.h"

typedef enum {
	CRIFI_ASSTR_NO_ERROR = 0,
	CRIFI_ASSTR_SUBJECT,
	CRIFI_ASSTR_PREDICATE,
	CRIFI_ASSTR_OBJECT,
	CRIFI_ASSTR_UNKNOWN
} CrifiAssertTripleError;

#ifdef __cplusplus
extern "C" {
#endif

Fact *get_next_triple(Environment *env, Fact *f);
Fact *get_next_list(Environment *env, Fact *f);
Fact *get_next_member(Environment *env, Fact *f);
Fact *get_next_subclass(Environment *env, Fact *f);

bool clipsvalue_is_uri(Environment *env, CLIPSValue val);
bool clipsvalue_is_bnode(Environment *env, CLIPSValue val);
bool clipsvalue_is_literal(Environment *env, CLIPSValue val);

char *extract_uri(Environment *env, TypeHeader *head);
char *extract_bnodeid(Environment *env, TypeHeader *head);

/**
 * Cast value to xs:string and extract the value.
 */
char *extract_lexical(Environment *env, TypeHeader *head);
char *extract_datatype(Environment *env, TypeHeader *head);
char *extract_lang(Environment *env, TypeHeader *head);

CrifiAssertTripleError assert_triple(Environment *env, CLIPSValue *subject, CLIPSValue *predicate, CLIPSValue *object);
CrifiAssertTripleError assert_member(Environment *env, CLIPSValue *instance, CLIPSValue *class_);
CrifiAssertTripleError assert_subclass(Environment *env, CLIPSValue *sub, CLIPSValue *super);

char* genclipscode_iri(Environment *env, char* iri);
char* genclipscode_lexical(Environment *env, CLIPSValue clipsvalue);
char* genclipscode_local(Environment *env, CLIPSValue context, const char *value);


bool crifi_infoquery_unpack_member(Environment *env, CLIPSValue member, CLIPSValue *instance, CLIPSValue *cls);

/*
int local_blanknode(Environment *env, CLIPSValue* location, CLIPSValue* id, CLIPSValue* result);
*/

#ifdef __cplusplus
} //extern "C"
#endif
