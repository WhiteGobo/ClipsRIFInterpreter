/**
 * See example_info_query.c for an example.
 * TODO: gather all internal symbols to assert search and extract statements
 * 	from graph.
 */
#pragma once

#include <ffi_clips_interface.h>
#include <n3parser.h>

#define TRIPLETEMPLATE "TripleTemplate"
#define TRIPLESLOTSUBJECT "subject"
#define TRIPLESLOTPREDICATE "predicate"
#define TRIPLESLOTOBJECT "object"
#define TRIPLESLOTCONTEXT "context"
#define ATOMTEMPLATE "Atom"
#define SUBCLASSTEMPLATE "Subclass"
#define MEMBERTEMPLATE "Member"
#define EQUALTEMPLATE "Equal"
#define ATOMLISTTEMPLATE "AtomList"

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

bool clipsvalue_is_uri(Environment *env, CLIPSValue val);
bool clipsvalue_is_bnode(Environment *env, CLIPSValue val);
bool clipsvalue_is_literal(Environment *env, CLIPSValue val);

char *extract_uri(Environment *env, TypeHeader *head);
char *extract_bnodeid(Environment *env, TypeHeader *head);

char *extract_lexical(Environment *env, TypeHeader *head);
char *extract_datatype(Environment *env, TypeHeader *head);
char *extract_lang(Environment *env, TypeHeader *head);

CrifiAssertTripleError assert_triple(Environment *env, CLIPSValue *subject, CLIPSValue *predicate, CLIPSValue *object);

char* genclipscode_iri(Environment *env, char* iri);
char* genclipscode_lexical(Environment *env, char* value, char* datatype);

#ifdef __cplusplus
} //extern "C"
#endif
